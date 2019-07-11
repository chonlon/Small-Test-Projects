#include "modbus.h"
#include <QModbusRtuSerialMaster>
#include <QModbusTcpClient>
#include <QVariant>
#include <QDebug>
#include <QRegularExpression>

CModbus::CModbus(ModbusParam& mrtu, QObject *parent /* = 0 */)
    : QObject(parent)
    , mrtu_(mrtu)
{
    this_thread_ = new QThread();
    moveToThread(this_thread_);

    qRegisterMetaType<SmokeData>();
    qRegisterMetaType<QModbusDevice::Error>();
    qRegisterMetaType<QModbusDevice::State>();
    
    connect(this_thread_, &QThread::started, 
        this, &CModbus::slot_modbus_init);
    connect(this_thread_, &QThread::finished, 
        this, &QObject::deleteLater);
}

CModbus::~CModbus()
{
    if ( modbus_device_) {
        modbus_device_->disconnectDevice();
        modbus_device_->deleteLater();
        modbus_device_ = nullptr;
    }

    if (timer_auto_reconn_) {
        timer_auto_reconn_->stop();
        timer_auto_reconn_->deleteLater();
        timer_auto_reconn_ = nullptr;
    }
}

void CModbus::modbus_start()
{
    if (this_thread_) {
        this_thread_->start();
    }
}

void CModbus::modbus_end()
{
    if (this_thread_) {
        this_thread_->quit();
        this_thread_->deleteLater();
        this_thread_ = nullptr;
    }
}

void CModbus::slot_modbus_init()
{
    timer_auto_reconn_ = new QTimer(this);
    connect(timer_auto_reconn_, SIGNAL(timeout()),
        this, SLOT(slot_modbus_auto_reconn()));

    static QRegularExpression re("COM\\d+");
    if (mrtu_.modbus_type_ == Modbus_RTU) {
        if (!modbus_device_) {
            modbus_device_ = new QModbusRtuSerialMaster(this);
        }
        if (!re.match(mrtu_.port_name_).hasMatch()) {
            qWarning() << QString(tr("Invalid port name: %1")).arg(mrtu_.port_name_);
            return;
        }
        modbus_device_->setConnectionParameter(QModbusDevice::SerialPortNameParameter, mrtu_.port_name_);
        modbus_device_->setConnectionParameter(QModbusDevice::SerialParityParameter, mrtu_.parity_);
        modbus_device_->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, mrtu_.baud_);
        modbus_device_->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, mrtu_.data_bits_);
        modbus_device_->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, mrtu_.stop_bits_);

        server_addr_ = mrtu_.server_addr_;
    }
    else {
        if (!modbus_device_) {
            modbus_device_ = new QModbusTcpClient(this);
        }
        QString surl = QString("%1:%2").arg(mrtu_.server_ip_).arg(mrtu_.server_port_);
        const QUrl url = QUrl::fromUserInput(surl);
        modbus_device_->setConnectionParameter(QModbusDevice::NetworkPortParameter, url.port());
        modbus_device_->setConnectionParameter(QModbusDevice::NetworkAddressParameter, url.host());
    }
    modbus_device_->setTimeout(mrtu_.response_time_);
    modbus_device_->setNumberOfRetries(mrtu_.number_of_retries_);
    is_auto_reconn_ = mrtu_.auto_connect_;

    if (!modbus_device_->connectDevice()) {
        qWarning() << QString(tr("Connect failed: %1")).arg(modbus_device_->errorString());
        return ;
    }
    connect(modbus_device_, SIGNAL(errorOccurred(QModbusDevice::Error)),
        this, SLOT(slot_modbus_error(QModbusDevice::Error)));

    connect(modbus_device_, SIGNAL(stateChanged(QModbusDevice::State)),
        this, SLOT(slot_modbus_state_changed(QModbusDevice::State)));

    is_requesting_ = false;
    check_auto_reconn();

}



void CModbus::check_auto_reconn()
{
    if (timer_auto_reconn_->isActive()) timer_auto_reconn_->stop();

    if (is_auto_reconn_) {
        timer_auto_reconn_->start(5000);
    }
}

void CModbus::data_request_start()
{
    is_requesting_ = true;
    data_request();
}

void CModbus::data_request_stop()
{
    is_requesting_ = false;
}

void CModbus::data_request()
{
    if (!modbus_device_ ||
        !is_requesting_ ||
        QModbusDevice::ConnectedState != modbus_device_->state()) {
        return;
    }

    QModbusDataUnit unit(QModbusDataUnit::HoldingRegisters, 0, 8);

    if (auto *reply = modbus_device_->sendReadRequest(unit, server_addr_)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &CModbus::slot_data_ready);
        }
        else {
            delete reply; // broadcast replies return immediately
        }
    }
}

void CModbus::slot_data_ready()
{
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply) {
        data_request();
        return;
    }
    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();
        if (unit.valueCount() > 3) {
            int i{ 0 };
            SmokeData readResult;
            readResult.addr0_ = unit.value(i++);
            readResult.addr1_ = unit.value(i++);
            readResult.addr2_ = unit.value(i++);
            readResult.addr3_ = unit.value(i++);

            emit signal_data_recv(readResult);
        }
    }
    data_request();
}

void CModbus::slot_modbus_error(QModbusDevice::Error err)
{
    switch (err) {
    case QModbusDevice::ConnectionError:
        qDebug() << QString("ModBus connecting error, check if re-connect");
        check_auto_reconn();
        break;
    default:
        qDebug() << QString("ModBus error:%1").arg(modbus_device_->errorString());
        break;
    }
}

void CModbus::slot_modbus_state_changed(QModbusDevice::State st)
{
    switch (st) {
    case QModbusDevice::ConnectedState:
        qDebug() << QString("ModBus connected");
        //data_request();
        break;
    default:
        qDebug() << QString("ModBus state changed:%1").arg(st);
        break;
    }
}

void CModbus::slot_modbus_auto_reconn()
{
    if (!modbus_device_) return;

    if ((QModbusDevice::UnconnectedState == modbus_device_->state()) ||
        (QModbusDevice::ClosingState == modbus_device_->state()))
    {
        if (!modbus_device_->connectDevice()) {
            qWarning() << "Connect failed: " << modbus_device_->errorString()
                << ". will retry in 5 seconds. - " << __FUNCTION__;
        }
    }
}
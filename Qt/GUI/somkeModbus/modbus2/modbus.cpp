#include "modbus.h"
#include <QModbusRtuSerialMaster>
#include <QModbusTcpClient>
#include <QVariant>
#include <QDebug>
#include <QRegularExpression>

CModbus::CModbus(const ModbusParam& mdparam, QObject *parent /* = 0 */)
    : QThread(parent)
    , modbus_param_(mdparam)
{
    timer_auto_reconn_.moveToThread(this);
    if (mdparam.modbus_type_ == Modbus_RTU) {
        modbus_device_ = new QModbusRtuSerialMaster(this);
    }
    else {
        modbus_device_ = new QModbusTcpClient(this);
    }
    modbus_device_->moveToThread(this);
}

CModbus::~CModbus()
{
    if (timer_auto_reconn_.isActive()) timer_auto_reconn_.stop();
    if (nullptr != modbus_device_) {
        modbus_device_->disconnectDevice();
        delete modbus_device_;
        modbus_device_ = nullptr;
    }
}

void CModbus::run()
{
    qRegisterMetaType<SmokeData>();
    qRegisterMetaType<QModbusDevice::Error>();
    qRegisterMetaType<QModbusDevice::State>();

    begin(modbus_param_);
    this->exec();
}

int CModbus::begin(const ModbusParam& mbparam)
{
    //connect(this, &QThread::finished, this, &QObject::deleteLater);
    connect(&timer_auto_reconn_, &QTimer::timeout,
        this, &CModbus::slot_modbus_auto_reconn);

    static QRegularExpression re("COM\\d+");
    if (mbparam.modbus_type_ == Modbus_RTU) {
        if (!re.match(mbparam.port_name_).hasMatch()) {
            qWarning() << QString(tr("Invalid port name: %1")).arg(mbparam.port_name_);
            return QModbusDevice::ConfigurationError;
        }
        modbus_device_->setConnectionParameter(QModbusDevice::SerialPortNameParameter, mbparam.port_name_);
        modbus_device_->setConnectionParameter(QModbusDevice::SerialParityParameter, mbparam.parity_);
        modbus_device_->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, mbparam.baud_);
        modbus_device_->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, mbparam.data_bits_);
        modbus_device_->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, mbparam.stop_bits_);
        
        server_addr_ = mbparam.server_addr_;
    }
    else {
        QString surl = QString("%1:%2").arg(mbparam.server_ip_).arg(mbparam.server_port_);
        const QUrl url = QUrl::fromUserInput(surl);
        modbus_device_->setConnectionParameter(QModbusDevice::NetworkPortParameter, url.port());
        modbus_device_->setConnectionParameter(QModbusDevice::NetworkAddressParameter, url.host());
    }
    modbus_device_->setTimeout(mbparam.response_time_);
    modbus_device_->setNumberOfRetries(mbparam.number_of_retries_);
    is_auto_reconn_ = mbparam.auto_connect_;

    if (!modbus_device_->connectDevice()) {
        qWarning() << QString(tr("Connect failed: %1")).arg(modbus_device_->errorString());
        return QModbusDevice::ConnectionError;
    }
    connect(modbus_device_, &QModbusClient::errorOccurred,
            this, &CModbus::slot_modbus_error);

    connect(modbus_device_, &QModbusClient::stateChanged,
            this, &CModbus::slot_modbus_state_changed);

    check_auto_reconn();

    return QModbusDevice::NoError;
}

void CModbus::check_auto_reconn()
{
    if (timer_auto_reconn_.isActive()) timer_auto_reconn_.stop();

    if (is_auto_reconn_) {
        timer_auto_reconn_.start(5000);
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

void CModbus::device_destory()
{
    if (timer_auto_reconn_.isActive()) timer_auto_reconn_.stop();
    if (nullptr != modbus_device_) {
        modbus_device_->disconnectDevice();
        delete modbus_device_;
        modbus_device_ = nullptr;
    }
    quit();
    deleteLater();
    //exit(0);
}
void CModbus::data_request()
{
    if (!modbus_device_ || 
        !is_requesting_ ||
        QModbusDevice::ConnectedState != modbus_device_->state() ) {
        return;
    }

    QModbusDataUnit unit(QModbusDataUnit::HoldingRegisters, 0, 8);

    if (auto *reply = modbus_device_->sendReadRequest(unit, server_addr_)) {
        //reply->moveToThread(this);
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &CModbus::slot_data_ready, Qt::QueuedConnection);
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
    QModbusDevice::Error err = reply->error();
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
        data_request();
        break;
    default:
        qDebug() << QString("ModBus state changed:%1").arg(st);
        break;
    }
}

void CModbus::slot_modbus_auto_reconn()
{
    if (!modbus_device_ ) return;

    if ((QModbusDevice::UnconnectedState == modbus_device_->state()) ||
        (QModbusDevice::ClosingState == modbus_device_->state()))
    {
        if (!modbus_device_->connectDevice()) {
            qWarning() << "Connect failed: " << modbus_device_->errorString()
                << ". will retry in 5 seconds. - " << __FUNCTION__;
        }
    }
}
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
    timer_auto_reconn_ = new QTimer(this);

    if (mdparam.modbus_type_ == Modbus_RTU) {
        modbus_device_ = new QModbusRtuSerialMaster(this);
    }
    else {
        modbus_device_ = new QModbusTcpClient(this);
    }
}

CModbus::~CModbus()
{
    if (timer_auto_reconn_) {
        timer_auto_reconn_->stop();
        delete timer_auto_reconn_;
        timer_auto_reconn_ = nullptr;
    }
    if (nullptr != modbus_device_) {
        modbus_device_->disconnectDevice();
        delete modbus_device_;
        modbus_device_ = nullptr;
    }
}

int CModbus::begin()
{
    connect(timer_auto_reconn_, &QTimer::timeout,
        this, &CModbus::slot_modbus_auto_reconn);

    static QRegularExpression re("COM\\d+");
    if (modbus_param_.modbus_type_ == Modbus_RTU) {
        if (!re.match(modbus_param_.port_name_).hasMatch()) {
            qWarning() << QString(tr("Invalid port name: %1")).arg(modbus_param_.port_name_);
            return QModbusDevice::ConfigurationError;
        }
        modbus_device_->setConnectionParameter(QModbusDevice::SerialPortNameParameter, modbus_param_.port_name_);
        modbus_device_->setConnectionParameter(QModbusDevice::SerialParityParameter, modbus_param_.parity_);
        modbus_device_->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, modbus_param_.baud_);
        modbus_device_->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, modbus_param_.data_bits_);
        modbus_device_->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, modbus_param_.stop_bits_);
        
        server_addr_ = modbus_param_.server_addr_;
    }
    else {
        QString surl = QString("%1:%2").arg(modbus_param_.server_ip_).arg(modbus_param_.server_port_);
        const QUrl url = QUrl::fromUserInput(surl);
        modbus_device_->setConnectionParameter(QModbusDevice::NetworkPortParameter, url.port());
        modbus_device_->setConnectionParameter(QModbusDevice::NetworkAddressParameter, url.host());
    }
    modbus_device_->setTimeout(modbus_param_.response_time_);
    modbus_device_->setNumberOfRetries(modbus_param_.number_of_retries_);
    is_auto_reconn_ = modbus_param_.auto_connect_;

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

void CModbus::end()
{
    if (timer_auto_reconn_) {
        timer_auto_reconn_->stop();
        delete timer_auto_reconn_;
        timer_auto_reconn_ = nullptr;
    }

    if (nullptr != modbus_device_) {
        modbus_device_->disconnectDevice();
        delete modbus_device_;
        modbus_device_ = nullptr;
    }
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
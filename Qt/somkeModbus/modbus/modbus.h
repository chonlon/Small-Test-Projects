#pragma once

#include <QObject>
#include <QModbusDataUnit>
#include <QModbusDevice>
#include <QUrl>
#include <QTimer>
#include <QSerialPort>
#include <QDateTime>
#include <QThread>
#include "define.h"

class QModbusClient;
class QModbusReply;

class CModbus : public QObject
{
    Q_OBJECT

public:
    CModbus(const ModbusParam& mrtu, QObject *parent = 0);
    ~CModbus();

    int getConnectStatus();

    Q_SLOT void device_destory();
    Q_SLOT void device_start();

    Q_SLOT void data_request_start();
    Q_SLOT void data_request_stop();
    
signals:
    void signal_data_recv(const SmokeData&);
private:
    Q_SLOT void slot_modbus_error(QModbusDevice::Error err);
    Q_SLOT void slot_modbus_state_changed(QModbusDevice::State st);
    Q_SLOT void slot_modbus_auto_reconn();
    Q_SLOT void slot_data_ready();

    int begin(const ModbusParam& mdparam);

    void data_request();
    void check_auto_reconn();
private:
    QModbusClient *modbus_device_{ nullptr };
    ModbusParam mdparam_;

    QTimer* timer_auto_reconn_{ nullptr };
    bool is_auto_reconn_{ false };
    int server_addr_{ 1 };
    bool is_requesting_{ false };

};



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
    CModbus(ModbusParam& mrtu, QObject *parent = 0);
    ~CModbus();

    Q_SLOT void modbus_start();
    Q_SLOT void modbus_end();

    Q_SLOT void data_request_start();
    Q_SLOT void data_request_stop();
    
signals:
    void signal_data_recv(SmokeData sd);

private:
    Q_SLOT void slot_modbus_error(QModbusDevice::Error err);
    Q_SLOT void slot_modbus_state_changed(QModbusDevice::State st);
    Q_SLOT void slot_modbus_auto_reconn();
    Q_SLOT void slot_data_ready();

    
    void data_request();
    void check_auto_reconn();
private:
    QModbusClient *modbus_device_{ nullptr };

    QTimer* timer_auto_reconn_{ nullptr };
    bool is_auto_reconn_{ false };
    int server_addr_{ 1 };
    bool is_requesting_{ false };

    QThread* this_thread_{ nullptr };

    ModbusParam mrtu_;
};



#pragma once
#include <QSerialPort>
enum ModbusType {
    Modbus_TCP,
    Modbus_RTU
};

typedef struct tagModbusParam {
    ModbusType modbus_type_ = Modbus_RTU;

    //RTU
    QString port_name_ = "COM1";
    int server_addr_ = 1;
    int parity_ = QSerialPort::NoParity;
    int baud_ = QSerialPort::Baud115200;
    int data_bits_ = QSerialPort::Data8;
    int stop_bits_ = QSerialPort::OneStop;

    //TCP
    QString server_ip_ = "127.0.0.1";
    int server_port_ = 502;

    int response_time_ = 300;
    int number_of_retries_ = 1;
    bool auto_connect_ = true;
}ModbusParam;

typedef struct tag_smokeData
{
    int addr0_;
    int addr1_;
    int addr2_;
    int addr3_;
}SmokeData, *pSmokeData;


Q_DECLARE_METATYPE(SmokeData)
#pragma once

#include <QObject>


class DeviceCommunication
{
public:
	enum RequestType:int8_t {HeartBeat, SnapFront, SnapBack};
	virtual RequestType recvMessage(const QString& msg) const = 0;
	virtual QString processMessage(const QString& msg) const = 0;
};
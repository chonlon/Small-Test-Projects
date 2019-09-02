#pragma once
#include  <QtCore/QThread>

class QThreadTest :
	public QThread
{
public:
	QThreadTest();
	~QThreadTest();
protected:
	void run() override;
	void timerEvent(QTimerEvent* event) override;
};


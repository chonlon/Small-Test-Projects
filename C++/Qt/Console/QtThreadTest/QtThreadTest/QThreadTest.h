#pragma once
#include  <QtCore/QThread>
#include <QMutex>

class QThreadTest :
	public QThread
{
public:
	QThreadTest();
	~QThreadTest();

    void foo();
protected:
	void run() override;
	void timerEvent(QTimerEvent* event) override;
private:
    QMutex mutex_;
};


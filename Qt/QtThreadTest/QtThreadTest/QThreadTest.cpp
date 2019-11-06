#include "QThreadTest.h"
#include <QDebug>
#include <chrono>



QThreadTest::QThreadTest()
{
	moveToThread(this);
}


QThreadTest::~QThreadTest()
{
}

void QThreadTest::run()
{
	qDebug() << "outter thread " << QThread::currentThread();
	startTimer(1000, Qt::PreciseTimer);
	exec();
}

void QThreadTest::timerEvent(QTimerEvent* event)
{
	static int i = 0;
	qDebug() << "timer thread" << QThread::currentThread();
	qDebug() << "we are now at " << i;
}

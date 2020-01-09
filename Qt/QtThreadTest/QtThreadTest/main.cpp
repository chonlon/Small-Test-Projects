#include <QtCore/QCoreApplication>

#include "QThreadTest.h"
#include <QTimer>
#include <QDebug>
#include <QMutex>

// 说明除了run函数, 其它所有函数都是在thread被构造的thread中运行.
// moveToThread以后所有函数都在被move后的thread运行, 就是这个类的上下文都移到了那个thread中了.

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	qDebug() << "main thread : " << QThread::currentThread();

	QThreadTest *test=new QThreadTest;

	test->start(QThread::HighPriority);

    test->foo();


    

	return a.exec();
}

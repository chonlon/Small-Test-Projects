#include "z_UnionTest.h"
#include <QtWidgets/QApplication>
#if 0
#include "D:\1_code\SolarCellEx_FinsUdp\src\main\QTcpServerFinal.h"

#endif

#include "D:\2_frogs-master\U-tu-edit\src\tpMain\lpImgViewer.h"
#include "C:\Users\Leaper\source\repos\test\mthread.h"
#include <iostream>
#include <map>
#include <QTimer>
#include <QDebug>
#include <QtConcurrent/QtConcurrent>

void f()
{
	
		qDebug() << "current thread" << QThread::currentThread();
	
}

int main(int argc, char *argv[])
{
QApplication a(argc, argv);
QDelayThread t;
t.StartThread();
//t.start(QThread::HighPriority);

#if 0	
	

	//lpImgViewer v{};
	//v.setImg(QImage{QString{"D:\\2_frogs-master\\U-tu-edit\\runner17\\x64\\images\\baumer+moritex color 250us.bmp"}});
	//v.show();

	auto widget = new QWidget{};
	widget->setVisible(false);
	
	auto wi = new QWidget{};
	wi->show();

	int b = 254;
	qDebug("%x", b);
	qDebug() << QString::number(b, 16);
	QTcpServerFinal server(20002);
	server.StartServer();
	delete widget;
#endif
	qDebug() << "hey here";
	
	auto f1 = QtConcurrent::run([]() {
		for(;;){}
	});
	QObject::connect(&t, &QDelayThread::SigDelayOperate, &f);
	
	QtConcurrent::run([]() {
		for (;;) {}
	});
	QtConcurrent::run([]() {
		for (;;) {}
	});
	QtConcurrent::run([]() {
		for (;;) {}
	});
	z_UnionTest w;
	w.show();
	QObject::connect(&t, &QDelayThread::SigDelayOperate, &w, &z_UnionTest::print, Qt::DirectConnection);
	//for(;;){}
	a.exec();
	
	return 0;
}

#include "z_UnionTest.h"
#include <QTimer>
#include <QDebug>

z_UnionTest::z_UnionTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QTimer* timer = new QTimer{};
	timer->start(100);
	connect(timer, &QTimer::timeout, []() {
		static int i = 0;
		qDebug() << "------------" << ++i;
	});
}

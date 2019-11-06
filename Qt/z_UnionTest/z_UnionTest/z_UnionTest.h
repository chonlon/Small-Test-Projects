#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_z_UnionTest.h"
#include <qthread.h>
#include <QDebug>
class z_UnionTest : public QMainWindow
{
	Q_OBJECT

public:
	z_UnionTest(QWidget *parent = Q_NULLPTR);

	Q_SLOT void print()
	{
			qDebug() << "current thread" << QThread::currentThread();
		
	}

private:
	Ui::z_UnionTestClass ui;
};

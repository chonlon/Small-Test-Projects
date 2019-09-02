#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_z_UnionTest.h"

class z_UnionTest : public QMainWindow
{
	Q_OBJECT

public:
	z_UnionTest(QWidget *parent = Q_NULLPTR);

private:
	Ui::z_UnionTestClass ui;
};

#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include "ui_qwidget_keep_alive.h"

class QWidget_KEEP_ALIVE : public QMainWindow
{
	Q_OBJECT

public:
	QWidget_KEEP_ALIVE(QWidget *parent = Q_NULLPTR);

private:
	Ui::QWidget_KEEP_ALIVEClass ui;
};

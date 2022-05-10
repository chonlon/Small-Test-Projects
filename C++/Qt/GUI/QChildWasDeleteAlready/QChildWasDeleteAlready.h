#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QChildWasDeleteAlready.h"

class QChildWasDeleteAlready : public QMainWindow
{
    Q_OBJECT

public:
    QChildWasDeleteAlready(QWidget *parent = Q_NULLPTR);

private:
    Ui::QChildWasDeleteAlreadyClass ui;
};

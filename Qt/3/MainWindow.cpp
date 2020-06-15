#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_NativeWindow);
    this->setWindowFlag(Qt::CustomizeWindowHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}


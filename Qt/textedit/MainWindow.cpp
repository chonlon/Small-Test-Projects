#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->plainTextEdit->insertPlainText("aaa\nbbb\nccc\n");
}

MainWindow::~MainWindow()
{
    delete ui;
}

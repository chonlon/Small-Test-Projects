#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QWidget>
#include <QGraphicsView>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    auto sence = new QGraphicsScene{};
    QPixmap pixmap("E:\\imgs\\C4-2F-90-F3-25-42GEVLP-OCM-SP050C_2019_06_27_16_26_35_904_416.BMP");
    sence->addPixmap(pixmap);



    auto view = new QGraphicsView{sence};

    m_plabel = new QLabel{view};
    m_plabel->setText(u8"this is title");
    m_plabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    m_plabel->raise();

    view->setToolTip("this is title");

    view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

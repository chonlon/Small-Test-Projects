#include "MainWindow.h"
#include "QFlawFilterWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QFlawFilterWidget win;
    win.show();

    return a.exec();
}

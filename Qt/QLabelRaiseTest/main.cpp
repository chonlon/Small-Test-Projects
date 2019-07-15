#include "MainWindow.h"
#include "FlawSelectWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    FlawSelectWidget win;
    win.show();

    return a.exec();
}

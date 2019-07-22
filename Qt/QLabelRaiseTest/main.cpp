#include "MainWindow.h"
#include "QFlawFilterWidget.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QFlawFilterWidget win;
    win.show();

	a.setStyle(QStyleFactory::create("Fusion"));
    return a.exec();
}

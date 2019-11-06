#include "ConditionSelectWidget.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConditionSelectWidget w;
    w.show();

    //QApplication::setStyle(QStyleFactory::create("Fusion"));

    return a.exec();
}

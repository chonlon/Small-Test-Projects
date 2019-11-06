#include "DefectFilterParamWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DefectFilterParamWidget w;
    w.show();
    return a.exec();
}

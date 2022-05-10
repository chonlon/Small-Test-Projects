#include "QChildWasDeleteAlready.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QChildWasDeleteAlready w;
    w.show();
    return a.exec();
}

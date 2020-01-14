#include "ProprietaryEditor.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QFile file(":/Resources/light.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);
    a.setStyleSheet(stream.readAll());

    ProprietaryEditor w;
    w.show();
    return a.exec();
}

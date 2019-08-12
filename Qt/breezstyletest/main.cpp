#include "MainWindow.h"
#include <QFile>
#include <QTextStream>
#include <QApplication>

int main(int argc, char *argv[])
{    QApplication app(argc, argv);

     // set stylesheet
     QFile file(":/light.qss");
     file.open(QFile::ReadOnly | QFile::Text);
     QTextStream stream(&file);
     app.setStyleSheet(stream.readAll());

    MainWindow w;
    w.show();

    return app.exec();
}

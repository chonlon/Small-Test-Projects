#include "widget_keep_alive.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QWidget_KEEP_ALIVE w;
	w.show();
	return a.exec();
}

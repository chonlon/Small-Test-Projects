#include "z_UnionTest.h"
#include <QtWidgets/QApplication>
#include "D:\1_code\SolarCellEx_FinsUdp\src\main\QTcpServerFinal.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	z_UnionTest w;
	w.show();

	QTcpServerFinal server(20002);
	server.StartServer();

	return a.exec();
}

#include "crystallization.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	crystallization w;
	w.show();
	return a.exec();
}

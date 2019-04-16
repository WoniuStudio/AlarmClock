#include "AlarmClock.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AlarmClock w;
	w.show();
	return a.exec();
}

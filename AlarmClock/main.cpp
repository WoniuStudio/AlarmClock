#include "AlarmClock.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setWindowIcon(QIcon(":/AlarmClock/Resources/clock.png"));

	AlarmClock w;
	w.show();
	return a.exec();
}

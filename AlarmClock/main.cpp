#include "AlarmClock.h"
#include <QtWidgets/QApplication>
#include "AlertTimeDlg.h"

extern bool DelAutoStart();
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setWindowIcon(QIcon(":/AlarmClock/Resources/clock.png"));
	
	//���һ�����ӻ����ڹر�ʱ�����˳�����
	a.setQuitOnLastWindowClosed(false);

	AlarmClock w;
	w.show();

// 	int width = GetSystemMetrics(SM_CXFULLSCREEN);
// 	int height = GetSystemMetrics(SM_CYFULLSCREEN);
// 
// 	AlertTimeDlg alertTimeDlg;
// 	//alertTimeDlg.move(QApplication::desktop()->width() - alertTimeDlg.width(), QApplication::desktop()->height() - alertTimeDlg.height());
// 	alertTimeDlg.move(width - alertTimeDlg.width(), height - alertTimeDlg.height());
// 	alertTimeDlg.show();

// 	AlertTimeDlg alertTimeDlg;
// 	alertTimeDlg.show();

	return a.exec();
}

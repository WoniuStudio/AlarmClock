#include "AlarmClock.h"
#include <QtWidgets/QApplication>
#include "AlertTimeDlg.h"

extern bool IsAutoStart();
extern bool SetAutoStart();
int main(int argc, char *argv[])
{
	bool bRet = SetAutoStart();
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

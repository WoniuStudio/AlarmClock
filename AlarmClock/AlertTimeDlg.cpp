#include "AlertTimeDlg.h"

AlertTimeDlg::AlertTimeDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//去掉?
	Qt::WindowFlags flags = Qt::Dialog; flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);

// 	//启动定时器
// 	startTimer(1000);
}

AlertTimeDlg::~AlertTimeDlg()
{

}


/************************************
@ Brief:		定时器
@ Author:		woniu201
@ Created:		2019/04/18
@ Return:
************************************/
int second = 0;
void AlertTimeDlg::timerEvent(QTimerEvent *event)
{
	second++;
	if (second == 10)
	{
		this->exec();
		second = 0;
	}
}

#include "AlertTimeDlg.h"

AlertTimeDlg::AlertTimeDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//ȥ��?
	Qt::WindowFlags flags = Qt::Dialog; flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);

// 	//������ʱ��
// 	startTimer(1000);
}

AlertTimeDlg::~AlertTimeDlg()
{

}


/************************************
@ Brief:		��ʱ��
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

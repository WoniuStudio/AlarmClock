#include "NowTimeDlg.h"
#include <windows.h>
#include <QTime>

NowTimeDlg::NowTimeDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//去掉?
	Qt::WindowFlags flags = Qt::Dialog; flags |= Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags);
	this->setAttribute(Qt::WA_DeleteOnClose);
	int width = GetSystemMetrics(SM_CXFULLSCREEN);
	int height = GetSystemMetrics(SM_CYFULLSCREEN);
	this->move(width - this->width(), height - this->height());

	this->setWindowTitle("整点报时！");
	
	ui.label->setStyleSheet(QString("border-image:url(:/AlarmClock/Resources/bk.png);background-image:url(:/AlarmClock/Resources/bk.png);color: rgb(170, 0, 0);font: 16pt \"华文中宋\";"));
	
	QString strTime = QTime::currentTime().toString("HH:mm");
	if (QTime::currentTime().hour() < 12)
	{
		ui.label->setText("现在是：上午" + strTime);
	}
	else if (QTime::currentTime().hour() == 12)
	{
		ui.label->setText("现在是：中午" + strTime);
	}
	else if (QTime::currentTime().hour() > 12)
	{
		ui.label->setText("现在是：下午" + strTime);
	}
}

NowTimeDlg::~NowTimeDlg()
{
}


void NowTimeDlg::closeEvent(QCloseEvent *event)
{

}
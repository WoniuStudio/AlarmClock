#include "NowTimeDlg.h"
#include <windows.h>
#include <QTime>

NowTimeDlg::NowTimeDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//ȥ��?
	Qt::WindowFlags flags = Qt::Dialog; flags |= Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags);
	this->setAttribute(Qt::WA_DeleteOnClose);
	int width = GetSystemMetrics(SM_CXFULLSCREEN);
	int height = GetSystemMetrics(SM_CYFULLSCREEN);
	this->move(width - this->width(), height - this->height());

	this->setWindowTitle("���㱨ʱ��");
	
	ui.label->setStyleSheet(QString("border-image:url(:/AlarmClock/Resources/bk.png);background-image:url(:/AlarmClock/Resources/bk.png);color: rgb(170, 0, 0);font: 16pt \"��������\";"));
	
	QString strTime = QTime::currentTime().toString("HH:mm");
	if (QTime::currentTime().hour() < 12)
	{
		ui.label->setText("�����ǣ�����" + strTime);
	}
	else if (QTime::currentTime().hour() == 12)
	{
		ui.label->setText("�����ǣ�����" + strTime);
	}
	else if (QTime::currentTime().hour() > 12)
	{
		ui.label->setText("�����ǣ�����" + strTime);
	}
}

NowTimeDlg::~NowTimeDlg()
{
}


void NowTimeDlg::closeEvent(QCloseEvent *event)
{

}
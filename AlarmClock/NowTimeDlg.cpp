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

	playList = NULL;
	player = NULL;
	speakTime(QTime::currentTime().hour());

	delayDlg = 10;	//10s��رմ���
	num = 1;		
	startTimer(1000);
}

NowTimeDlg::~NowTimeDlg()
{
}

/************************************
@ Brief:		�رմ����¼�
@ Author:		woniu201 
@ Created:		2019/04/29
@ Return:            
************************************/
void NowTimeDlg::closeEvent(QCloseEvent *event)
{

}

/************************************
@ Brief:		������ʱ
@ Author:		woniu201 
@ Created:		2019/04/29
@ Return:            
************************************/
void NowTimeDlg::speakTime(const int hour)
{
	if (player)
	{
		delete player;
		player = NULL;
	}
	if (playList)
	{
		delete playList;
		playList = NULL;
	}
	
	QString strTimePath;

	playList = new QMediaPlaylist;
	playList->addMedia(QUrl("qrc:/AlarmClock/Resources/sound/nowtime.wav"));
	if (hour<=7)
	{
		playList->addMedia(QUrl("qrc:/AlarmClock/Resources/sound/am0.wav"));
		strTimePath = QString::asprintf("qrc:/AlarmClock/Resources/sound/%d.wav", hour);
		playList->addMedia(QUrl(strTimePath));
	}
	else if ((hour>7)&&(hour<=12))
	{
		playList->addMedia(QUrl("qrc:/AlarmClock/Resources/sound/am.wav"));
		strTimePath = QString::asprintf("qrc:/AlarmClock/Resources/sound/%d.wav", hour);
		playList->addMedia(QUrl(strTimePath));
	}
	else if ((hour > 12) && (hour <= 20))
	{
		playList->addMedia(QUrl("qrc:/AlarmClock/Resources/sound/pm.wav"));
		strTimePath = QString::asprintf("qrc:/AlarmClock/Resources/sound/%d.wav", hour-12);
		playList->addMedia(QUrl(strTimePath));
	}
	else if (hour > 20)
	{
		playList->addMedia(QUrl("qrc:/AlarmClock/Resources/sound/em.wav"));
		strTimePath = QString::asprintf("qrc:/AlarmClock/Resources/sound/%d.wav", hour-12);
		playList->addMedia(QUrl(strTimePath));
	}
	playList->addMedia(QUrl("qrc:/AlarmClock/Resources/sound/point.wav"));

	playList->setPlaybackMode(QMediaPlaylist::Sequential);
	player = new QMediaPlayer;
	player->setPlaylist(playList);
	player->play();
}

/************************************
@ Brief:		��ʱ���10S���˳�����
@ Author:		woniu201 
@ Created:		2019/04/29
@ Return:            
************************************/
void NowTimeDlg::timerEvent(QTimerEvent *event)
{
	if (num++ >= delayDlg)
	{
		this->close();
	}
}
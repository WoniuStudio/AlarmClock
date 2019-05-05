#include "AlertTimeDlg.h"

AlertTimeDlg::AlertTimeDlg(QWidget *parent, QString strSound, QString clockTxt)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_sound = strSound;
	m_clockTxt = clockTxt;

	//ȥ��?
	Qt::WindowFlags flags = Qt::Dialog; flags |= Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags);
	//this->setWindowFlags(Qt::WindowStaysOnTopHint);//�����ö�

// 	//������ʱ��
 	startTimer(1000);

	player = NULL;

	player = new QMediaPlayer;
	player->setMedia(QUrl("qrc:/AlarmClock/Resources/sound/sound1.mp3"));
	player->play();

	ui.label->setText(clockTxt);
	this->setAttribute(Qt::WA_DeleteOnClose, 1);
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
bool b = true;
void AlertTimeDlg::timerEvent(QTimerEvent *event)
{

	if (player)
	{
		if (player->state() == QMediaPlayer::StoppedState)
		{
			delete player;
			player = NULL;

			player = new QMediaPlayer;
			player->setMedia(QUrl::fromLocalFile(m_sound));
			player->play();
		}
	}
}

/************************************
@ Brief:		�رմ���
@ Author:		woniu201
@ Created:		2019/04/19
@ Return:
************************************/
void AlertTimeDlg::closeEvent(QCloseEvent *event)
{
	//event->ignore();
	player->stop();
 	emit closeSignal();
	QDialog::accept();
}
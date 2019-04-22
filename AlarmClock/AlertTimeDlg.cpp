#include "AlertTimeDlg.h"

AlertTimeDlg::AlertTimeDlg(QWidget *parent, QString strSound, int clockNum)
	: QDialog(parent)
{
	ui.setupUi(this);

	//ȥ��?
	Qt::WindowFlags flags = Qt::Dialog; flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);

// 	//������ʱ��
 	startTimer(1000);

	player = NULL;

	player = new QMediaPlayer;
	player->setMedia(QUrl::fromLocalFile("./Resources/sound/sound1.mp3"));
	player->play();
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
	if (b)
	{

		if (player)
		{

			if (player->state() == QMediaPlayer::StoppedState)
			{
				qDebug() << "ֹͣ";

				delete player;
				player = NULL;

				player = new QMediaPlayer;
				player->setMedia(QUrl::fromLocalFile("./Resources/sound/sound1.mp3"));
				player->play();
			}

			if (player->state() == QMediaPlayer::PlayingState)
			{
				qDebug() << "������";
			}
		}
	}


}

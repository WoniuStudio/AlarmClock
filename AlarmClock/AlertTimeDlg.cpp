#include "AlertTimeDlg.h"

AlertTimeDlg::AlertTimeDlg(QWidget *parent, QString strSound, int clockNum)
	: QDialog(parent)
{
	ui.setupUi(this);

	//去掉?
	Qt::WindowFlags flags = Qt::Dialog; flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);

// 	//启动定时器
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
@ Brief:		定时器
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
				qDebug() << "停止";

				delete player;
				player = NULL;

				player = new QMediaPlayer;
				player->setMedia(QUrl::fromLocalFile("./Resources/sound/sound1.mp3"));
				player->play();
			}

			if (player->state() == QMediaPlayer::PlayingState)
			{
				qDebug() << "播放中";
			}
		}
	}


}

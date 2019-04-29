#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include "ui_NowTimeDlg.h"
#include <QCloseEvent>
#include <QtMultimedia/QMediaPlayer>
#include <QVideoWidget>
#include <QtMultimedia/QMediaPlaylist>

class NowTimeDlg : public QDialog
{
	Q_OBJECT

public:
	NowTimeDlg(QWidget *parent = Q_NULLPTR);
	~NowTimeDlg();
	void closeEvent(QCloseEvent *event);

	void speakTime(const int hour);
	
	virtual void timerEvent(QTimerEvent *event);

	QMediaPlaylist *playList;
	QMediaPlayer *player;

	int delayDlg;  //窗口延迟时间
	int num;	//计数
private:
	Ui::NowTimeDlg ui;
};

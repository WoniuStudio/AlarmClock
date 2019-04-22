#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include "ui_AlertTimeDlg.h"
#include <QtMultimedia/QMediaPlayer>
#include <QVideoWidget>

class AlertTimeDlg : public QDialog
{
	Q_OBJECT

public:
	AlertTimeDlg(QWidget *parent = Q_NULLPTR, QString strSound = "", int clockNum = 0);
	~AlertTimeDlg();

	virtual void timerEvent(QTimerEvent *event);

public:
	QMediaPlayer* player;
private:
	Ui::AlertTimeDlg ui;
};

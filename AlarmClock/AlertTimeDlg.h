#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include "ui_AlertTimeDlg.h"
#include <QtMultimedia/QMediaPlayer>
#include <QCloseEvent>

class AlertTimeDlg : public QDialog
{
	Q_OBJECT

public:
	AlertTimeDlg(QWidget *parent = Q_NULLPTR, QString strSound = "", QString clockTxt = "");
	~AlertTimeDlg();

	virtual void timerEvent(QTimerEvent *event);
	virtual void closeEvent(QCloseEvent *event);
	
	QString m_sound;
	QString m_clockTxt;
signals:
	void closeSignal();

private:
	Ui::AlertTimeDlg ui;
	QMediaPlayer *player;
};

#pragma once

#include <QDialog>
#include "ui_AlertTimeDlg.h"
#include <QtMultimedia/QMediaPlayer>
#include <QCloseEvent>

class AlertTimeDlg : public QDialog
{
	Q_OBJECT

public:
	AlertTimeDlg(QWidget *parent = Q_NULLPTR);
	~AlertTimeDlg();

	virtual void timerEvent(QTimerEvent *event);
	virtual void closeEvent(QCloseEvent *event);
	
signals:
	void closeSignal();

private:
	Ui::AlertTimeDlg ui;
	QMediaPlayer *player;
};

#pragma once
#pragma execution_character_set("utf-8")

#include <QtGui>
#include <QtWidgets>
#include "ui_AlarmClock.h"
#include <QPushButton>
#include "AlertTimeDlg.h"
#include <QtMultimedia/QMediaPlayer>
#include <QVideoWidget>

class AlarmClock : public QDialog
{
	Q_OBJECT

public:
	AlarmClock(QWidget *parent = Q_NULLPTR);
	virtual void paintEvent(QPaintEvent *event);

	virtual void mouseMoveEvent(QMouseEvent * event);
	virtual void mousePressEvent(QMouseEvent * event);
	virtual void mouseReleaseEvent(QMouseEvent * event);

	//定时器
	virtual void timerEvent(QTimerEvent *event);
	int timerId;

	QPushButton* closeButton;
	QPushButton* minButton;

private:
	QPixmap m_titleImage;

	bool m_dragging; // 是否正在拖动
	QPoint m_startPosition; // 拖动开始前的鼠标位置
	QPoint m_framePosition; // 窗体的原始位置

	QSystemTrayIcon m_systray;
	AlertTimeDlg* alertTimeDlg;

	QMediaPlayer *player;

	bool bRuningClock1;
private slots:
	void OnBtnClose();
	void OnBtnMin();
	void OnExit();
	int  OnSystemTrayClicked(QSystemTrayIcon::ActivationReason reason);
	void OnBtnStartClock1();
	
	void OnListen1();
private:
	Ui::AlarmClockClass ui;
};

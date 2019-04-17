#pragma once
#pragma execution_character_set("utf-8")

#include <QtGui>
#include <QtWidgets>

#include "ui_AlarmClock.h"
#include <QPushButton>

class AlarmClock : public QDialog
{
	Q_OBJECT

public:
	AlarmClock(QWidget *parent = Q_NULLPTR);
	virtual void paintEvent(QPaintEvent *event);

	virtual void mouseMoveEvent(QMouseEvent * event);
	virtual void mousePressEvent(QMouseEvent * event);
	virtual void mouseReleaseEvent(QMouseEvent * event);

	//��ʱ��
	virtual void timerEvent(QTimerEvent *event);
	int timerId;

	QPushButton* closeButton;
	QPushButton* minButton;

private:
	QPixmap m_titleImage;

	bool m_dragging; // �Ƿ������϶�
	QPoint m_startPosition; // �϶���ʼǰ�����λ��
	QPoint m_framePosition; // �����ԭʼλ��

	QSystemTrayIcon m_systray;
private slots:
	void OnBtnClose();
	void OnBtnMin();
	void OnExit();
	int  OnSystemTrayClicked(QSystemTrayIcon::ActivationReason reason);
	void OnBtnStartClock1();

private:
	Ui::AlarmClockClass ui;
};

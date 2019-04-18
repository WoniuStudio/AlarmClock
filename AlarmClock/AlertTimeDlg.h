#pragma once

#include <QDialog>
#include "ui_AlertTimeDlg.h"

class AlertTimeDlg : public QDialog
{
	Q_OBJECT

public:
	AlertTimeDlg(QWidget *parent = Q_NULLPTR);
	~AlertTimeDlg();

	virtual void timerEvent(QTimerEvent *event);

private:
	Ui::AlertTimeDlg ui;
};

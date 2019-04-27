#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include "ui_NowTimeDlg.h"
#include <QCloseEvent>

class NowTimeDlg : public QDialog
{
	Q_OBJECT

public:
	NowTimeDlg(QWidget *parent = Q_NULLPTR);
	~NowTimeDlg();
	void closeEvent(QCloseEvent *event);
private:
	Ui::NowTimeDlg ui;
};

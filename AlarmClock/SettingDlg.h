#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include "ui_SettingDlg.h"

class SettingDlg : public QDialog
{
	Q_OBJECT

public:
	SettingDlg(QWidget *parent = Q_NULLPTR);
	~SettingDlg();
private slots:
	void OnBaseSetting();
	void OnAbout();
private:
	Ui::SettingDlg ui;
};

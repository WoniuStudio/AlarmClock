#pragma once

#include <QDialog>
#include "ui_AboutDlg.h"

class AboutDlg : public QDialog
{
	Q_OBJECT

public:
	AboutDlg(QWidget *parent = Q_NULLPTR);
	~AboutDlg();
	Ui::AboutDlg ui;
private:

};

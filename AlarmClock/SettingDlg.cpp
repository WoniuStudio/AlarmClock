#include "SettingDlg.h"
#include <QDebug>

SettingDlg::SettingDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//ȥ��?
	Qt::WindowFlags flags = Qt::Dialog; flags |= Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags);

	ui.stackedWidget->setCurrentIndex(1);
	ui.label1->setText("���ߣ���ţ201\r\n�汾��1.1.0\r\n�������ڣ�2019/04/24\r\n΢�Ź��ţ���ũcode֮·");
	
	this->setWindowTitle("����");

	connect(ui.btnSetting, &QToolButton::clicked, this, &SettingDlg::OnBaseSetting);
	connect(ui.btnAbout, &QToolButton::clicked, this, &SettingDlg::OnAbout);

	connect(ui.checkBox, &QCheckBox::stateChanged, this, &SettingDlg::OnCheckBox);

	if (IsAutoStart())
	{
		ui.checkBox->setChecked(true);
	}
	else
	{
		ui.checkBox->setChecked(false);
	}
}

SettingDlg::~SettingDlg()
{
}

void SettingDlg::OnBaseSetting()
{
	ui.stackedWidget->setCurrentIndex(0);
}

void SettingDlg::OnAbout()
{
	ui.stackedWidget->setCurrentIndex(1);
}


void SettingDlg::OnCheckBox(int state)
{
	qDebug() << state;
	if (state == 0) //ȡ��ѡ��
	{
		DelAutoStart();
	}
	else if (state == 2) //ѡ��
	{
		SetAutoStart();
	}
}
#include "AboutDlg.h"

AboutDlg::AboutDlg(QWidget *parent)
	: QDialog(parent)
{
	//ȥ��?
	Qt::WindowFlags flags = Qt::Dialog; flags |= Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags);
	ui.setupUi(this);
}

AboutDlg::~AboutDlg()
{
}

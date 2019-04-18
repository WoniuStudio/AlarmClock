#include "AlarmClock.h"
#include <QPainter>
#include "AlertTimeDlg.h"

AlarmClock::AlarmClock(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//����ʾ���������ޱ߿�
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

	setAttribute(Qt::WA_TranslucentBackground);
	m_titleImage.load(":/AlarmClock/Resources/background.jpg");

//ϵͳ����
	//������ʾ����
	m_systray.setToolTip("��ţ����");
	// ��������ͼ��
	m_systray.setIcon(QIcon(":/AlarmClock/Resources/clock.png"));
	//���̲˵���
	QMenu * menu = new QMenu();
	menu->addAction(ui.actionExit);
	m_systray.setContextMenu(menu);
	//��ʾ����
	m_systray.show();

	m_systray.show();
//��ҳ��رհ�ť�����»���ť
	closeButton = new QPushButton(this);
	//closeButton->setIcon(QIcon(":/AlarmClock/Resources/close_normal.png"));
	closeButton->setGeometry(this->rect().right() - 45, 10, 40, 30);
	//closeButton->setFlat(true);
	closeButton->setStyleSheet("QPushButton{background-color:transparent; border-image: url(:/AlarmClock/Resources/close.png);}"
	"QPushButton:hover{background-color:rgb(6,168,240); border-image: url(:/AlarmClock/Resources/close.png);}"
	"QPushButton:pressed{background-color: rgb(6,168,220); border-image: url(:/AlarmClock/Resources/close.png);}");

	minButton = new QPushButton(this);
	minButton->setGeometry(this->rect().right() - 85, 10, 40, 30);
	minButton->setStyleSheet("QPushButton{background-color:transparent; border-image: url(:/AlarmClock/Resources/min.png);}"
		"QPushButton:hover{background-color:rgb(6,168,240); border-image: url(:/AlarmClock/Resources/min.png);}"
		"QPushButton:pressed{background-color: rgb(6,168,220); border-image: url(:/AlarmClock/Resources/min.png);}");

	//labelTime��ʾʱ��
	QString strDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd  hh:mm:ss");
	ui.labelTime->setText(strDateTime);

	//��ʼ��ʱ��
	timerId = startTimer(1000);

	//Tab1
	ui.btnStart1Clock->setStyleSheet("QPushButton{background-color:rgb(6,168,255); color:white; font-size:30px; border-radius:10px;padding:2px 4px;}"
		"QPushButton:hover{background-color: rgb(6,168,240); color:white; border-radius:10px;padding:2px 4px;}"
		"QPushButton:pressed{background-color: rgb(6,168,220);border:none;color:white; border-radius:10px;padding:2px 4px;}");
	
	
	//����Ӧ�¼�
	connect(minButton, SIGNAL(clicked()), this, SLOT(OnBtnMin()));
	connect(closeButton, SIGNAL(clicked()), this, SLOT(OnBtnClose()));
	connect(&m_systray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, SLOT(OnSystemTrayClicked(QSystemTrayIcon::ActivationReason)));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(OnExit()));
	
	connect(ui.btnStart1Clock, SIGNAL(clicked()), this, SLOT(OnBtnStartClock1()));

}


void AlarmClock::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QRect frameRect = rect();
	frameRect.adjust(1, 1, -1, -1);

	//�������ͱ߿�
	painter.setPen(QColor(0x66, 0x66, 0x66));
	painter.setBrush(QColor(0xFF, 0xFF, 0xFF));
	painter.drawRoundRect(frameRect, 2, 2);


	//��������
	QRect titleRect = frameRect;
	titleRect.setBottom(frameRect.top() + 80);

	//��ӱ���������ͼ������Բ��
	QPainterPath path;
	path.addRoundRect(frameRect.adjusted(1, 1, 0, -1), 2, 2);
	path.intersects(titleRect);
	painter.setClipPath(path);

	painter.drawPixmap(titleRect, m_titleImage);
}



/************************************
@ Brief:		��갴����Ӧ����
@ Author:		woniu201
@ Created:		2019/04/16
@ Return:
************************************/
void AlarmClock::mousePressEvent(QMouseEvent *event)
{
	// ֻ��Ӧ���
	if (event->button() == Qt::LeftButton)
	{
		QRect titleRect = rect();
		titleRect.setBottom(titleRect.top() + 80);

		if (titleRect.contains(event->pos()))
		{
			m_dragging = true;
			m_startPosition = event->globalPos();
			m_framePosition = frameGeometry().topLeft();
		}
	}

	QWidget::mousePressEvent(event);
}

/************************************
@ Brief:		����ƶ���Ӧ����
@ Author:		woniu201
@ Created:		2019/04/16
@ Return:
************************************/
void AlarmClock::mouseMoveEvent(QMouseEvent *event)
{
	// ֻ��Ӧ���
	if (event->buttons() & Qt::LeftButton)
	{
		if (m_dragging)
		{
			// delta ���ƫ����, 
			QPoint delta = event->globalPos() - m_startPosition;

			// ��λ�ã�����ԭʼλ��  + ƫ����
			move(m_framePosition + delta);
		}
	}

	QWidget::mouseMoveEvent(event);
}

/************************************
@ Brief:		����ͷ���Ӧ����
@ Author:		woniu201
@ Created:		2019/04/16
@ Return:
************************************/
void AlarmClock::mouseReleaseEvent(QMouseEvent * event)
{
	m_dragging = false;
	QWidget::mouseReleaseEvent(event);
}



/************************************
@ Brief:		��ʱ��
@ Author:		woniu201
@ Created:		2019/04/16
@ Return:
************************************/
void AlarmClock::timerEvent(QTimerEvent *event)
{
	ui.labelTime->setText("");
	QString strDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd  hh:mm:ss");
	ui.labelTime->setText(strDateTime);
}

/************************************
@ Brief:		�ر�������
@ Author:		woniu201 
@ Created: 		2019/04/16
@ Return:		    
************************************/
void AlarmClock::OnBtnClose()
{
	this->hide();
}

/************************************
@ Brief:		��С��������
@ Author:		woniu201 
@ Created: 		2019/04/16
@ Return:		    
************************************/
void AlarmClock::OnBtnMin()
{
	this->showMinimized();
}

/************************************
@ Brief:		����/�ر�����1
@ Author:		woniu201 
@ Created: 		2019/04/16
@ Return:		    
************************************/
bool bRuningClock1 = false;

void AlarmClock::OnBtnStartClock1()
{
	if (bRuningClock1)
	{
		alertTimeDlg->close();
		delete alertTimeDlg;

		bRuningClock1 = false;
		ui.btnStart1Clock->setText("��������");
		ui.btnStart1Clock->setStyleSheet("QPushButton{background-color:rgb(6,168,255); color:white; font-size:30px; border-radius:10px;padding:2px 4px;}"
			"QPushButton:hover{background-color: rgb(6,168,240); color:white; border-radius:10px;padding:2px 4px;}"
			"QPushButton:pressed{background-color: rgb(6,168,220);border:none;color:white; border-radius:10px;padding:2px 4px;}");
		ui.comboBoxHH1->setEnabled(true);
		ui.comboBoxMM1->setEnabled(true);
		ui.comboBoxRing1->setEnabled(true);
		ui.textEdit1->setEnabled(true);
	}
	else
	{

		alertTimeDlg = new AlertTimeDlg(this);
		alertTimeDlg->show();

		bRuningClock1 = true;
		ui.btnStart1Clock->setText("������");
		ui.btnStart1Clock->setStyleSheet("QPushButton{background-color:rgb(6,168,255); color:red; font-size:30px; border-radius:10px;padding:2px 4px;}"
			"QPushButton:hover{background-color: rgb(6,168,240); color:red; border-radius:10px;padding:2px 4px;}"
			"QPushButton:pressed{background-color: rgb(6,168,220);border:none;color:red; border-radius:10px;padding:2px 4px;}");
		ui.comboBoxHH1->setEnabled(false);
		ui.comboBoxMM1->setEnabled(false);
		ui.comboBoxRing1->setEnabled(false);
		ui.textEdit1->setEnabled(false);
	}
}

/************************************
@ Brief:		�����˳���ť
@ Author:		woniu201 
@ Created:		2019/04/17
@ Return:            
************************************/
void AlarmClock::OnExit()
{
	QApplication::exit(0);
}

/************************************
@ Brief:		˫������
@ Author:		woniu201 
@ Created:		2019/04/17
@ Return:            
************************************/
int  AlarmClock::OnSystemTrayClicked(QSystemTrayIcon::ActivationReason reason)
{
	if (reason == QSystemTrayIcon::Trigger
		|| reason == QSystemTrayIcon::DoubleClick)
	{
		// ��ʾ������
		this->showNormal();
	}
	return 0;
}
#include "AlarmClock.h"
#include <QPainter>
#include "AlertTimeDlg.h"
#include <QTime>
#include <QMessageBox>

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
	ui.btnStart2Clock->setStyleSheet("QPushButton{background-color:rgb(6,168,255); color:white; font-size:30px; border-radius:10px;padding:2px 4px;}"
		"QPushButton:hover{background-color: rgb(6,168,240); color:white; border-radius:10px;padding:2px 4px;}"
		"QPushButton:pressed{background-color: rgb(6,168,220);border:none;color:white; border-radius:10px;padding:2px 4px;}");


	//��ʼ������
	player = NULL;
	alertTimeDlg = NULL;
	bRuningClock1 = false;
	bRuningClock2 = false;
	int clock1HH = 0;
	int clock1MM = 0;
	int clock2HH = 0;
	int clock2MM = 0;


	//����Ӧ�¼�
	connect(minButton, SIGNAL(clicked()), this, SLOT(OnBtnMin()));
	connect(closeButton, SIGNAL(clicked()), this, SLOT(OnBtnClose()));
	connect(&m_systray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, SLOT(OnSystemTrayClicked(QSystemTrayIcon::ActivationReason)));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(OnExit()));
	
	connect(ui.btnStart1Clock, &QPushButton::clicked, this, &AlarmClock::OnBtnStartClock1);
	connect(ui.btnStart2Clock, &QPushButton::clicked, this, &AlarmClock::OnBtnStartClock2);

	connect(ui.listenBtn1, &QPushButton::clicked, this, &AlarmClock::OnListen1);

}


void AlarmClock::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QRect frameRect = rect();
	frameRect.adjust(1, 1, -1, -1);

	this->resize(452, 549);

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

	if (bRuningClock1)
	{
		QTime sysTime = QTime::currentTime();
		if ((sysTime.hour()== clock1HH) && (sysTime.minute()== clock1HH))
		{
			if (alertTimeDlg==NULL)
			{
				alertTimeDlg = new AlertTimeDlg(this, "./Resources/sound/sound1.mp3", "����1��ʱ�䵽�ˣ�");

				int width = GetSystemMetrics(SM_CXFULLSCREEN);
				int height = GetSystemMetrics(SM_CYFULLSCREEN);
				alertTimeDlg->move(width - alertTimeDlg->width(), height - alertTimeDlg->height());
				alertTimeDlg->setWindowFlags(Qt::WindowStaysOnTopHint);//�����ö�
				alertTimeDlg->setWindowTitle("������");
				connect(alertTimeDlg, &AlertTimeDlg::closeSignal, this, &AlarmClock::OnCloseAlertTimeDlg1);
				alertTimeDlg->show();
			}

		}

		//���嵹��ʱ
		QTime endTime;
		endTime.setHMS(clock1HH, clock1MM, 0);
		qDebug() << endTime.toString("hh:mm ss");

		QTime startTime = QTime::currentTime();
		int sec = startTime.secsTo(endTime);
		
		int hh = int(sec/3600);
		int mm = int((sec-hh*3600)/60);
		int ss = sec - hh*3600 - mm*60;

		ui.labelCountDown1->setText(QString::asprintf("����ʱ��%02d:%02d %02d", hh, mm, ss));
	}
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
void AlarmClock::OnBtnStartClock1()
{
	if (bRuningClock1)
	{
		bRuningClock1 = false;
		ui.btnStart1Clock->setText("��������");
		ui.btnStart1Clock->setStyleSheet("QPushButton{background-color:rgb(6,168,255); color:white; font-size:30px; border-radius:10px;padding:2px 4px;}"
			"QPushButton:hover{background-color: rgb(6,168,240); color:white; border-radius:10px;padding:2px 4px;}"
			"QPushButton:pressed{background-color: rgb(6,168,220);border:none;color:white; border-radius:10px;padding:2px 4px;}");
		ui.comboBoxHH1->setEnabled(true);
		ui.comboBoxMM1->setEnabled(true);
		ui.comboBoxRing1->setEnabled(true);
		ui.textEdit1->setEnabled(true);
		ui.labelCountDown1->setText("����ʱ��");
	}
	else
	{

// 		alertTimeDlg = new AlertTimeDlg(this);
// 
// 		int width = GetSystemMetrics(SM_CXFULLSCREEN);
// 		int height = GetSystemMetrics(SM_CYFULLSCREEN);
// 		alertTimeDlg->move(width - alertTimeDlg->width(), height - alertTimeDlg->height());
// 		alertTimeDlg->show();
// 		connect(alertTimeDlg, &AlertTimeDlg::closeSignal, this, &AlarmClock::OnCloseAlertTimeDlg1);
// 		alertTimeDlg->setWindowTitle("������");

		clock1HH = ui.comboBoxHH1->currentText().toInt();
		clock1MM = ui.comboBoxMM1->currentText().toInt();

		QTime curTime = QTime::currentTime();
		if ((clock1HH*3600 +clock1MM*60) >= (curTime.hour()*3600+ curTime.minute()*60+curTime.second()))
		{
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
		else
		{
			QMessageBox::about(NULL, "��ʾ", "<font color='red'>����ʱ�����</font>" );
		}
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

/************************************
@ Brief:		����1����
@ Author:		woniu201 
@ Created: 		2019/04/18
@ Return:		    
************************************/
void AlarmClock::OnListen1()
{	//player->setMedia(QUrl::fromLocalFile(":/AlarmClock/Resources/sound/����1.mp3"));
	//player->setMedia(QUrl(":/AlarmClock/Resources/sound/sound1.mp3"));
	//player->setMedia(QMediaContent(QUrl::fromLocalFile("./Resources/sound/sound1.mp3")));
	if (player)
	{
		delete player;
		player = NULL;
	}
	player = new QMediaPlayer;
	player->setMedia(QUrl::fromLocalFile("./Resources/sound/sound1.mp3"));
	player->play();
}


void AlarmClock::OnCloseAlertTimeDlg1()
{
	bRuningClock1 = false;
	ui.btnStart1Clock->setText("��������");
	ui.btnStart1Clock->setStyleSheet("QPushButton{background-color:rgb(6,168,255); color:white; font-size:30px; border-radius:10px;padding:2px 4px;}"
		"QPushButton:hover{background-color: rgb(6,168,240); color:white; border-radius:10px;padding:2px 4px;}"
		"QPushButton:pressed{background-color: rgb(6,168,220);border:none;color:white; border-radius:10px;padding:2px 4px;}");
	ui.comboBoxHH1->setEnabled(true);
	ui.comboBoxMM1->setEnabled(true);
	ui.comboBoxRing1->setEnabled(true);
	ui.textEdit1->setEnabled(true);
	ui.labelCountDown1->setText("����ʱ��");
	alertTimeDlg = NULL;
}

/************************************
@ Brief:		����/�ر�����2
@ Author:		woniu201 
@ Created:		2019/04/23
@ Return:            
************************************/
void AlarmClock::OnBtnStartClock2()
{
	if (bRuningClock2)
	{
		bRuningClock2 = false;
		ui.btnStart2Clock->setText("��������");
		ui.btnStart2Clock->setStyleSheet("QPushButton{background-color:rgb(6,168,255); color:white; font-size:30px; border-radius:10px;padding:2px 4px;}"
			"QPushButton:hover{background-color: rgb(6,168,240); color:white; border-radius:10px;padding:2px 4px;}"
			"QPushButton:pressed{background-color: rgb(6,168,220);border:none;color:white; border-radius:10px;padding:2px 4px;}");
		ui.comboBoxHH2->setEnabled(true);
		ui.comboBoxMM2->setEnabled(true);
		ui.comboBoxRing2->setEnabled(true);
		ui.textEdit2->setEnabled(true);
		ui.labelCountDown2->setText("����ʱ��");
	}
	else
	{
		clock2HH = ui.comboBoxHH2->currentText().toInt();
		clock2MM = ui.comboBoxMM2->currentText().toInt();

		QTime curTime = QTime::currentTime();
		if ((clock2HH * 3600 + clock2MM * 60) >= (curTime.hour() * 3600 + curTime.minute() * 60 + curTime.second()))
		{
			bRuningClock2 = true;
			ui.btnStart2Clock->setText("������");
			ui.btnStart2Clock->setStyleSheet("QPushButton{background-color:rgb(6,168,255); color:red; font-size:30px; border-radius:10px;padding:2px 4px;}"
				"QPushButton:hover{background-color: rgb(6,168,240); color:red; border-radius:10px;padding:2px 4px;}"
				"QPushButton:pressed{background-color: rgb(6,168,220);border:none;color:red; border-radius:10px;padding:2px 4px;}");
			ui.comboBoxHH2->setEnabled(false);
			ui.comboBoxMM2->setEnabled(false);
			ui.comboBoxRing2->setEnabled(false);
			ui.textEdit2->setEnabled(false);
		}
		else
		{
			QMessageBox::about(NULL, "��ʾ", "<font color='red'>����ʱ�����</font>");
		}
	}
}
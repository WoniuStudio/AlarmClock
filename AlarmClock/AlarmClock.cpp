#include "AlarmClock.h"
#include <QPainter>
#include "AlertTimeDlg.h"
#include <QTime>

AlarmClock::AlarmClock(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//不显示标题栏（无边框）
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

	setAttribute(Qt::WA_TranslucentBackground);
	m_titleImage.load(":/AlarmClock/Resources/background.jpg");

//系统托盘
	//设置提示文字
	m_systray.setToolTip("蜗牛闹铃");
	// 设置托盘图标
	m_systray.setIcon(QIcon(":/AlarmClock/Resources/clock.png"));
	//托盘菜单项
	QMenu * menu = new QMenu();
	menu->addAction(ui.actionExit);
	m_systray.setContextMenu(menu);
	//显示托盘
	m_systray.show();

	m_systray.show();
//主页面关闭按钮，最下化按钮
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

	//labelTime显示时间
	QString strDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd  hh:mm:ss");
	ui.labelTime->setText(strDateTime);

	//开始定时器
	timerId = startTimer(1000);

	//Tab1
	ui.btnStart1Clock->setStyleSheet("QPushButton{background-color:rgb(6,168,255); color:white; font-size:30px; border-radius:10px;padding:2px 4px;}"
		"QPushButton:hover{background-color: rgb(6,168,240); color:white; border-radius:10px;padding:2px 4px;}"
		"QPushButton:pressed{background-color: rgb(6,168,220);border:none;color:white; border-radius:10px;padding:2px 4px;}");
	
	//
	player = NULL;
	bRuningClock1 = false;

	//绑定响应事件
	connect(minButton, SIGNAL(clicked()), this, SLOT(OnBtnMin()));
	connect(closeButton, SIGNAL(clicked()), this, SLOT(OnBtnClose()));
	connect(&m_systray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, SLOT(OnSystemTrayClicked(QSystemTrayIcon::ActivationReason)));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(OnExit()));
	
	connect(ui.btnStart1Clock, SIGNAL(clicked()), this, SLOT(OnBtnStartClock1()));
	connect(ui.listenBtn1, SIGNAL(clicked()), this, SLOT(OnListen1()));

}


void AlarmClock::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QRect frameRect = rect();
	frameRect.adjust(1, 1, -1, -1);

	//画背景和边框
	painter.setPen(QColor(0x66, 0x66, 0x66));
	painter.setBrush(QColor(0xFF, 0xFF, 0xFF));
	painter.drawRoundRect(frameRect, 2, 2);


	//画标题栏
	QRect titleRect = frameRect;
	titleRect.setBottom(frameRect.top() + 80);

	//添加标题栏背景图后设置圆角
	QPainterPath path;
	path.addRoundRect(frameRect.adjusted(1, 1, 0, -1), 2, 2);
	path.intersects(titleRect);
	painter.setClipPath(path);

	painter.drawPixmap(titleRect, m_titleImage);
}



/************************************
@ Brief:		鼠标按下响应函数
@ Author:		woniu201
@ Created:		2019/04/16
@ Return:
************************************/
void AlarmClock::mousePressEvent(QMouseEvent *event)
{
	// 只响应左键
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
@ Brief:		鼠标移动响应函数
@ Author:		woniu201
@ Created:		2019/04/16
@ Return:
************************************/
void AlarmClock::mouseMoveEvent(QMouseEvent *event)
{
	// 只响应左键
	if (event->buttons() & Qt::LeftButton)
	{
		if (m_dragging)
		{
			// delta 相对偏移量, 
			QPoint delta = event->globalPos() - m_startPosition;

			// 新位置：窗体原始位置  + 偏移量
			move(m_framePosition + delta);
		}
	}

	QWidget::mouseMoveEvent(event);
}

/************************************
@ Brief:		鼠标释放响应函数
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
@ Brief:		定时器
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
		int hh = ui.comboBoxHH1->currentText().toInt();
		int mm = ui.comboBoxMM1->currentText().toInt();
		QTime sysTime = QTime::currentTime();
		if ((sysTime.hour()==hh) && (sysTime.minute()==mm))
		{
			if (player)
			{
				delete player;
				player = NULL;
			}
			player = new QMediaPlayer;
			player->setMedia(QUrl::fromLocalFile("./Resources/sound/sound1.mp3"));
			player->play();
		}
	}
}

/************************************
@ Brief:		关闭主窗口
@ Author:		woniu201 
@ Created: 		2019/04/16
@ Return:		    
************************************/
void AlarmClock::OnBtnClose()
{
	this->hide();
}

/************************************
@ Brief:		最小化主窗口
@ Author:		woniu201 
@ Created: 		2019/04/16
@ Return:		    
************************************/
void AlarmClock::OnBtnMin()
{
	this->showMinimized();
}

/************************************
@ Brief:		开启/关闭闹铃1
@ Author:		woniu201 
@ Created: 		2019/04/16
@ Return:		    
************************************/
void AlarmClock::OnBtnStartClock1()
{
	if (bRuningClock1)
	{
		alertTimeDlg->close();
		delete alertTimeDlg;

		bRuningClock1 = false;
		ui.btnStart1Clock->setText("开启闹铃");
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
		ui.btnStart1Clock->setText("闹铃中");
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
@ Brief:		托盘退出按钮
@ Author:		woniu201 
@ Created:		2019/04/17
@ Return:            
************************************/
void AlarmClock::OnExit()
{
	QApplication::exit(0);
}

/************************************
@ Brief:		双击托盘
@ Author:		woniu201 
@ Created:		2019/04/17
@ Return:            
************************************/
int  AlarmClock::OnSystemTrayClicked(QSystemTrayIcon::ActivationReason reason)
{
	if (reason == QSystemTrayIcon::Trigger
		|| reason == QSystemTrayIcon::DoubleClick)
	{
		// 显示主窗口
		this->showNormal();
	}
	return 0;
}

/************************************
@ Brief:		闹铃1试听
@ Author:		woniu201 
@ Created: 		2019/04/18
@ Return:		    
************************************/
void AlarmClock::OnListen1()
{	//player->setMedia(QUrl::fromLocalFile(":/AlarmClock/Resources/sound/铃声1.mp3"));
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
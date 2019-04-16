#include "AlarmClock.h"
#include <QPainter>

AlarmClock::AlarmClock(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//不显示标题栏（无边框）
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

	setAttribute(Qt::WA_TranslucentBackground);
	m_titleImage.load(":/AlarmClock/Resources/background.jpg");

	//关闭按钮，最下滑按钮
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
	//绑定按钮
	connect(minButton, SIGNAL(clicked()), this, SLOT(OnBtnMin()));
	connect(ui.btnStart1Clock, SIGNAL(clicked()), this, SLOT(OnBtnStartClock1()));
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
}

/************************************
@ Brief:		关闭主窗口
@ Author:		woniu201 
@ Created: 		2019/04/16
@ Return:		    
************************************/
void AlarmClock::OnBtnClose()
{
	
}

/************************************
@ Brief:		最小化主窗口
@ Author:		woniu201 
@ Created: 		2019/04/16
@ Return:		    
************************************/
void AlarmClock::OnBtnMin()
{
	//this->hide();
	this->showMinimized();
}

/************************************
@ Brief:		开启/关闭闹铃1
@ Author:		woniu201 
@ Created: 		2019/04/16
@ Return:		    
************************************/
bool bRuningClock1 = false;
void AlarmClock::OnBtnStartClock1()
{
	if (bRuningClock1)
	{
		bRuningClock1 = false;
		ui.btnStart1Clock->setText("开启闹铃");
		ui.btnStart1Clock->setStyleSheet("QPushButton{background-color:rgb(6,168,255); color:white; font-size:30px; border-radius:10px;padding:2px 4px;}"
			"QPushButton:hover{background-color: rgb(6,168,240); color:white; border-radius:10px;padding:2px 4px;}"
			"QPushButton:pressed{background-color: rgb(6,168,220);border:none;color:white; border-radius:10px;padding:2px 4px;}");
	}
	else
	{
		bRuningClock1 = true;
		ui.btnStart1Clock->setText("闹铃中");
		ui.btnStart1Clock->setStyleSheet("QPushButton{background-color:rgb(6,168,255); color:red; font-size:30px; border-radius:10px;padding:2px 4px;}"
			"QPushButton:hover{background-color: rgb(6,168,240); color:red; border-radius:10px;padding:2px 4px;}"
			"QPushButton:pressed{background-color: rgb(6,168,220);border:none;color:red; border-radius:10px;padding:2px 4px;}");
	}
}
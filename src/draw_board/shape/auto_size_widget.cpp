#include "auto_size_widget.h"

#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QGridLayout>
#include <QApplication>
#include <QTime>
#include <QDateTime>

int kMargin = 10;

AutoSizeWidget::AutoSizeWidget(bool EnabledShadow,QWidget *parent)
	: QWidget(parent)
{
	// 追踪鼠标
	this->setMouseTracking(true);
	bak_ = new QWidget();
	bak_->setMouseTracking(true);
	bak_->setAttribute(Qt::WA_TranslucentBackground,false);

	setStyleSheet("background-color: #dddddd;");

	if(EnabledShadow)
	{
		QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
		/*shadowEffect->setColor(QColor(0x21, 0x21, 0x21));*/
		shadowEffect->setColor(QColor(0x80, 0x80, 0x80));
		//shadowEffect->setBlurRadius(4); // 阴影的大小
		shadowEffect->setBlurRadius(8); // 阴影的大小
		shadowEffect->setOffset(0, 0);
		bak_->setGraphicsEffect(shadowEffect);

		QGridLayout *lo = new QGridLayout(this);
		lo->addWidget(bak_, 0, 0);
		lo->setContentsMargins(8, 8, 8, 8); // 注意和阴影大小的协调
		mGridLayout = lo;
	}
	else
	{
		QGridLayout *lo = new QGridLayout(this);
		lo->addWidget(bak_, 0, 0);
		lo->setContentsMargins(0, 0, 0, 0);
		mGridLayout = lo;
	}
}

void AutoSizeWidget::mouseReleaseEvent(QMouseEvent *event)
{
	Q_UNUSED(event);
	if (_isleftpressed)
		_isleftpressed = false;
	setCursor(Qt::ArrowCursor);
}
void AutoSizeWidget::mousePressEvent(QMouseEvent *event)
{
	Q_UNUSED(event);
	if (event->button() == Qt::LeftButton)
	{
		this->_isleftpressed = true;
		QPoint temp = event->globalPos();
		_plast = temp;
		_curpos = countFlag(event->pos(), countRow(event->pos()));
	}
}
void AutoSizeWidget::mouseMoveEvent(QMouseEvent *event)
{
	Q_UNUSED(event);
	if (this->isFullScreen()) return;	//窗口铺满全屏，直接返回，不做任何操作
	SetMouseIconWhenMove(event);
	if (_isleftpressed)//是否左击
	{
		QPoint ptemp = event->globalPos();
		ptemp = ptemp - _plast;
		if (_curpos == 22)//移动窗口
		{
			ptemp = ptemp + pos();
			//move(ptemp);
		}
		else
		{
			QRect wid = geometry();
			switch (_curpos)//改变窗口的大小
			{
			case 11:wid.setTopLeft(wid.topLeft() + ptemp); break;//左上角
			case 13:wid.setTopRight(wid.topRight() + ptemp); break;//右上角
			case 31:wid.setBottomLeft(wid.bottomLeft() + ptemp); break;//左下角
			case 33:wid.setBottomRight(wid.bottomRight() + ptemp); break;//右下角
			case 12:wid.setTop(wid.top() + ptemp.y()); break;//中上角
			case 21:wid.setLeft(wid.left() + ptemp.x()); break;//中左角
			case 23:wid.setRight(wid.right() + ptemp.x()); break;//中右角
			case 32:wid.setBottom(wid.bottom() + ptemp.y()); break;//中下角
			}
			setGeometry(wid);
		}
		_plast = event->globalPos();//更新位置
	}
}
AutoSizeWidget::~AutoSizeWidget()
{

}

//获取光标在窗口所在区域的 列  返回行列坐标
int AutoSizeWidget::countFlag(QPoint p, int row)//计算鼠标在哪一列和哪一行
{
	if (p.y() < kMargin)
		return 10 + row;
	else if (p.y() > this->height() - kMargin)
		return 30 + row;
	else
		return 20 + row;
}

//获取光标在窗口所在区域的 行   返回行数
int AutoSizeWidget::countRow(QPoint p)
{
	return (p.x() < kMargin) ? 1 : (p.x() > (this->width() - kMargin) ? 3 : 2);
}

//根据鼠标所在位置改变鼠标指针形状
void AutoSizeWidget::SetCursorType(int flag)
{
	SetCursorType(this,flag);
}

void AutoSizeWidget::SetCursorType(QWidget* w, int flag)
{
	switch (flag)
	{
	case 11:
	case 33:
		w->setCursor(Qt::SizeFDiagCursor);
		break;
	case 13:
	case 31:
		w->setCursor(Qt::SizeBDiagCursor);
		break;
	case 21:
	case 23:
		w->setCursor(Qt::SizeHorCursor);
		break;
	case 12:
	case 32:
		w->setCursor(Qt::SizeVerCursor);
		break;
	case 22:
		SetCursorOnCenter(w);
		break;
	}
}

void AutoSizeWidget::SetCursorOnCenter(QWidget* w)
{
	w->setCursor(Qt::ArrowCursor);
	QApplication::restoreOverrideCursor();//恢复鼠标指针性状
}

void AutoSizeWidget::SetShowShadowEffect(bool show)
{
	if(show)
	{
		//mGridLayout->setContentsMargins(4, 4, 4, 4);

		mGridLayout->setContentsMargins(8, 8, 8, 8);
	}
	else
	{
		mGridLayout->setContentsMargins(0, 0, 0, 0);
	}
}

void AutoSizeWidget::SetMouseIconWhenMove(QMouseEvent* event)
{
	int poss = countFlag(event->pos(), countRow(event->pos()));
	SetCursorType(poss);
}

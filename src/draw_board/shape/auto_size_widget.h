#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QGridLayout>

/**
 * 所有窗口的基类,实现边框可伸缩
 */
class AutoSizeWidget : public QWidget
{
	Q_OBJECT
public:
	AutoSizeWidget(bool EnabledShadow,QWidget *parent = 0);
	~AutoSizeWidget();

	QWidget* GetBack() { return bak_; }

protected:
	void mouseMoveEvent(QMouseEvent *) override;
	void mousePressEvent(QMouseEvent *) override;
	void mouseReleaseEvent(QMouseEvent *) override;

	QWidget* bak_ = nullptr;

	virtual void showEvent(QShowEvent* event) override
	{
		this->setAttribute(Qt::WA_Mapped);//解决不能及时刷新的bug
		QWidget::showEvent(event);
	}
	int countRow(QPoint p);            //获取光标在窗口所在区域的 行   返回行数
	int countFlag(QPoint p, int row);    //获取光标在窗口所在区域的 列  返回行列坐标
	virtual void SetCursorType(int flag);          //根据传入的坐标，设置光标样式
	virtual void SetCursorType(QWidget* w, int flag);
	virtual void SetCursorOnCenter(QWidget* w); 

	void SetShowShadowEffect(bool show);

	void SetMouseIconWhenMove(QMouseEvent* event);

private:
	bool _isleftpressed = false; //判断是否是左键点击
	int _curpos = 0;    //鼠标左键按下时光标所在区域
	QPoint _plast;      //获取鼠标左键按下时光标在全局(屏幕而非窗口)的位置
	QGridLayout* mGridLayout = nullptr;
};

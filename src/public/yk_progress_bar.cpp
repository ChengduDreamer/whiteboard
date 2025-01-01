#include "yk_progress_bar.h"

#include <qstyle.h>

YKProgressBar::YKProgressBar(QWidget* parent) : QSlider(parent){

}

YKProgressBar::~YKProgressBar() {

}

void YKProgressBar::paintEvent(QPaintEvent* event) {
	QSlider::paintEvent(event);

}

void YKProgressBar::Init() {

}


// 实现鼠标点击进度条，滑块能跳转到 鼠标位置
void YKProgressBar::mouseReleaseEvent(QMouseEvent* event) {
	setValue(QStyle::sliderValueFromPosition(this->minimum(), this->maximum(), event->x(), this->width()));
	emit SigPosChanged();
}
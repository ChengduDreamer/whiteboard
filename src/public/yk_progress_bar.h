#pragma once

#include <qwidget.h>
#include <qpainter.h>
#include <qslider.h>
#include <qevent.h>

class YKProgressBar : public QSlider {
	Q_OBJECT
public:
	YKProgressBar(QWidget* parent = nullptr);
	~YKProgressBar();
	virtual void paintEvent(QPaintEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;
	void Init();

signals:
	void SigPosChanged();
};
#pragma once
/*
desc:
仅用于显示图标的按钮
*/

#include <qpushbutton.h>
//#include <qmouseeventtransition.h>
#include <qevent.h>
#include <qpixmap.h>
#include <qpainter.h>
#include <QtSvg/QSvgRenderer>

class YKIconButton : public QPushButton {
	Q_OBJECT
public:
	struct BackgroundInfo {
		QColor m_background_color_normal;
		QColor m_background_color_hover;
		QColor m_background_color_press;
		QColor m_background_color_disable;
		QColor m_background_color_checked;
	};
public:
	YKIconButton(QWidget* parent = nullptr);
	~YKIconButton() = default;
	void Init(QSize size, const QString& normal_img_path, const QString& hover_img_path, const QString& click_img_path);
	void set_pixmap_2(const QString& normal_img_path, const QString& hover_img_path, const QString& click_img_path);
	void show_pixmap_1();
	void show_pixmap_2();
	void SetBackgroundInfo(const BackgroundInfo& bg_info);
	

	virtual void paintEvent(QPaintEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
	virtual void enterEvent(QEnterEvent* event) override;
#else
	virtual void enterEvent(QEvent* event) override;
#endif
	virtual void leaveEvent(QEvent* event) override;

	void SetUseSvg(bool use_svg);
private:
	QString m_normal_img_path_1;
	QString m_hover_img_path_1;
	QString m_press_img_path_1;

	QPixmap m_normal_pixmap_1;
	QPixmap m_hover_pixmap_1;
	QPixmap m_press_img_pixmap_1;

	QString m_normal_img_path_2;
	QString m_hover_img_path_2;
	QString m_press_img_path_2;

	QPixmap m_normal_pixmap_2;
	QPixmap m_hover_pixmap_2;
	QPixmap m_press_img_pixmap_2;
	
	bool m_cursor_in = false;
	bool m_pressed = false;

	bool m_show_pixmap_1 = true;
	bool m_show_pixmap_2 = false;

	BackgroundInfo m_background_info;

private:
	QSvgRenderer m_svg_renderer;
	bool m_use_svg = true;
	bool m_user_bg = false;
};

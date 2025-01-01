#include "yk_icon_button.h"
#include <qdebug.h>

YKIconButton::YKIconButton(QWidget* parent) : QPushButton(parent) {
	setMouseTracking(true);
	setAttribute(Qt::WA_TranslucentBackground, true);
}

void YKIconButton::Init(QSize size, const QString& normal_img_path, const QString& hover_img_path, const QString& click_img_path) {
	setFixedSize(size);

	m_normal_img_path_1 = normal_img_path;
	m_hover_img_path_1 = hover_img_path;
	m_press_img_path_1 = click_img_path;

	m_normal_pixmap_1 = QPixmap(m_normal_img_path_1);
	m_hover_pixmap_1 = QPixmap(m_hover_img_path_1);
	m_press_img_pixmap_1 = QPixmap(m_press_img_path_1);
}


void YKIconButton::paintEvent(QPaintEvent* event) {
	QPainter painter(this);

	if (m_user_bg) {
		painter.save();
	
		painter.setPen(Qt::NoPen);
		if (isChecked()) {
			painter.setBrush(QBrush(m_background_info.m_background_color_checked));
		}
		else {
			// to do distinguish normal hover press
			painter.setBrush(QBrush(m_background_info.m_background_color_normal));
		}
		painter.drawRoundedRect(this->rect(), 0, 0);
		painter.restore();
	}

	if (m_cursor_in) {
		if (m_pressed) {
			if (m_show_pixmap_1) {
				if (m_use_svg) {
					m_svg_renderer.load(m_press_img_path_1);
					m_svg_renderer.render(&painter, QRectF(0, 0, this->width(), this->height()));
				}
				else {
					painter.drawPixmap(0, 0, m_press_img_pixmap_1);
				}
			}
			else {
				if (m_use_svg) {
					m_svg_renderer.load(m_press_img_path_2);
					m_svg_renderer.render(&painter, QRectF(0, 0, this->width(), this->height()));
				}
				else {
					painter.drawPixmap(0, 0, m_press_img_pixmap_2);
				}
			}
		}
		else {
			if (m_show_pixmap_1) {
				if (m_use_svg) {
					m_svg_renderer.load(m_hover_img_path_1);
					m_svg_renderer.render(&painter, QRectF(0, 0, this->width(), this->height()));
				}
				else {
					painter.drawPixmap(0, 0, m_hover_pixmap_1);
				}
				
			}
			else {
				if (m_use_svg) {
					m_svg_renderer.load(m_hover_img_path_2);
					m_svg_renderer.render(&painter, QRectF(0, 0, this->width(), this->height()));
				}
				else {
					painter.drawPixmap(0, 0, m_hover_pixmap_2);
				}
			}
		}
	}
	else {
		if (m_show_pixmap_1) {
			if (m_use_svg) {
				m_svg_renderer.load(m_normal_img_path_1);
				m_svg_renderer.render(&painter, QRectF(0, 0, this->width(), this->height()));
			}
			else {
				painter.drawPixmap(0, 0, m_normal_pixmap_1);
			}
			
		}
		else {
			if (m_use_svg) {
				m_svg_renderer.load(m_normal_img_path_2);
				m_svg_renderer.render(&painter, QRectF(0, 0, this->width(), this->height()));
			}
			else {
				painter.drawPixmap(0, 0, m_normal_pixmap_2);
			}
		}
	}
}

void YKIconButton::set_pixmap_2(const QString& normal_img_path, const QString& hover_img_path, const QString& click_img_path) {
	m_normal_img_path_2 = normal_img_path;
	m_hover_img_path_2 = hover_img_path;
	m_press_img_path_2 = click_img_path;

	m_normal_pixmap_2 = QPixmap(m_normal_img_path_2);
	m_hover_pixmap_2 = QPixmap(m_hover_img_path_2);
	m_press_img_pixmap_2 = QPixmap(m_press_img_path_2);
}

void YKIconButton::show_pixmap_1() {
	m_show_pixmap_1 = true;
	m_show_pixmap_2 = false;
}

void YKIconButton::show_pixmap_2() {
	m_show_pixmap_2 = true;
	m_show_pixmap_1 = false;
}

void YKIconButton::mousePressEvent(QMouseEvent* event) {
	m_pressed = true;
	repaint();
	QPushButton::mousePressEvent(event);
}

void YKIconButton::mouseReleaseEvent(QMouseEvent* event) {
	m_pressed = false;
	repaint();
	QPushButton::mouseReleaseEvent(event);
}

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
void YKIconButton::enterEvent(QEnterEvent* event)
#else
void YKIconButton::enterEvent(QEvent* event)
#endif
{
	m_cursor_in = true;
	repaint();
	QPushButton::enterEvent(event);
}

void YKIconButton::leaveEvent(QEvent* event) {
	m_cursor_in = false;
	repaint();
	QPushButton::leaveEvent(event);
}

void YKIconButton::SetUseSvg(bool use_svg) {
	m_use_svg = use_svg;
}

void YKIconButton::SetBackgroundInfo(const BackgroundInfo& bg_info) {
	m_background_info = bg_info;
	m_user_bg = true;
}

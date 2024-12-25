#include "yk_line_edit.h"

#include <qpen.h>
#include <qbrush.h>
#include <qboxlayout.h>
#include "yk_icon_button.h"

YKLineEdit::YKLineEdit(QWidget* parent) : QLineEdit(parent) {

}

void YKLineEdit::Init(const QSize& size, const QString& placeholderText, BorderInfo border_info, IconInfo icon_info, TextInfo text_info, const QColor& brackground_color) {
	m_border_info = border_info;
	m_icon_info = icon_info;
	m_text_info = text_info;
	m_brackground_color = brackground_color;

	setAttribute(Qt::WA_StyledBackground);
	setMouseTracking(true);
	setFixedSize(size);

	m_hbox_main_layout = new QHBoxLayout();
	setLayout(m_hbox_main_layout);

	if (icon_info.m_have_left_icon) {
		m_btn_left = new YKIconButton(this);
		m_btn_left->Init(icon_info.m_left_size, icon_info.m_left_icon_normal, icon_info.m_left_icon_hover, icon_info.m_left_icon_press);
		m_hbox_main_layout->addSpacing(icon_info.m_padding_left);
		m_hbox_main_layout->addWidget(m_btn_left);
	}

	if (icon_info.m_have_right_icon) {
		m_btn_right = new YKIconButton(this);
		m_btn_right->Init(icon_info.m_right_size, icon_info.m_right_icon_normal, icon_info.m_right_icon_hover, icon_info.m_right_icon_press);
		m_hbox_main_layout->addWidget(m_btn_right, 1, Qt::AlignRight);
		m_hbox_main_layout->addSpacing(icon_info.m_padding_right);
	}
	
	QPalette palette;
	palette.setColor(QPalette::PlaceholderText, QColor(0xaf, 0xb3, 0xbc));
	setPlaceholderText(placeholderText);
	
	QString css_str = QString("QLineEdit {border-width:0;border-style:outset; background-color: #00000000; \
	font-family: Microsoft YaHei; font-size: %1px; padding-left: %2px; color: %3; padding-right: %4px;}").arg(m_text_info.m_font_size).
		arg(m_text_info.m_padding_left).arg(m_text_info.m_font_color).arg(m_text_info.m_padding_right);

	setStyleSheet(css_str);
}


void YKLineEdit::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setWidth(m_border_info.m_border_width);
	if (m_focus_in) { //焦点事件
		pen.setColor(m_border_info.m_focus_color);
	}
	else {
		if (m_cursor_in) {
			pen.setColor(m_border_info.m_hover_color);
		}
		else {
			pen.setColor(m_border_info.m_normal_color);
		}
	}
	painter.setPen(pen);
	painter.setBrush(QBrush(m_brackground_color));
	painter.drawRoundedRect(this->rect(), m_border_info.m_border_radius, m_border_info.m_border_radius);
	QLineEdit::paintEvent(event);
}

void YKLineEdit::leaveEvent(QEvent* event) {
	QLineEdit::leaveEvent(event);
	m_cursor_in = false;
	repaint();
}

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
void YKLineEdit::enterEvent(QEnterEvent* event)
#else
void YKLineEdit::enterEvent(QEvent* event)
#endif
{
	QLineEdit::enterEvent(event);
	m_cursor_in = true;
	repaint();
}

void YKLineEdit::focusInEvent(QFocusEvent* event) {
	QLineEdit::focusInEvent(event);
	m_focus_in = true;
	repaint();
}

void YKLineEdit::focusOutEvent(QFocusEvent* event) {
	QLineEdit::focusOutEvent(event);
	m_focus_in = false;
	repaint();
}


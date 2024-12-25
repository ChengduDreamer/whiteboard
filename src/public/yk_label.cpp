#include "yk_label.h"

#include <qdebug.h>
#include <qbitmap.h>
#include <qfont.h>

YKLabel::YKLabel(QWidget* parent) : QLabel(parent){
	
}

void YKLabel::Init(QSize size, const BorderInfo& border_info, const TextInfo& text_info, const QColor& background_color) {
	setFixedSize(size);
	setAttribute(Qt::WA_StyledBackground);

	m_border_info = border_info;
	m_text_info = text_info;
	m_background_color = background_color;
}

void YKLabel::Init2(const BorderInfo& border_info, const TextInfo& text_info, const QColor& background_color) {
	setAttribute(Qt::WA_StyledBackground);
	m_border_info = border_info;
	m_text_info = text_info;
	m_background_color = background_color;
}

void YKLabel::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing);//��������ݺ󣬻�������������Ӧ���
	painter.setPen(Qt::NoPen); //�����������������Ƴ����ľͻ��кڱ�
	painter.save();

	if (m_border_info.m_width > 0) {
		QPen pen;
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(m_border_info.m_width);
		pen.setColor(m_border_info.m_color);
		painter.setPen(pen);
	}
	
	painter.setBrush(QBrush(m_background_color));
	painter.drawRoundedRect(this->rect(), m_border_info.m_radius, m_border_info.m_radius);
	painter.restore();
	
	QFont font{ "Microsoft YaHei" };
	font.setPixelSize(m_text_info.m_size);
	font.setBold(m_text_info.m_blod);
	QPen font_pen;
	font_pen.setColor(m_text_info.m_color);
	painter.setPen(font_pen);
	painter.setFont(font);
	painter.drawText(m_text_info.m_padding_left, m_text_info.m_padding_top, m_text_info.m_text); // ע�� �����y����  �� ���ֵײ� ���� ��ť�ϱ߿� ����
	m_font = font;
}

QFont YKLabel::GetFont(const TextInfo& text_info) {
	QFont font{ "Microsoft YaHei" };
	font.setPixelSize(text_info.m_size);
	font.setBold(text_info.m_blod);
	return font;
}

void YKLabel::SetText(const QString& text) {
	m_text_info.m_text = text;
	repaint();
}
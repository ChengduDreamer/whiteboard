#pragma once

/*
desc:
用于通用输入框， 可以设置左右两侧的图标，也可以不设置图标
*/

#include <qpushbutton.h>
#include <qlabel.h>
#include <qboxlayout.h>
#include <QWidget>
#include <QLineEdit>
#include <qstring.h>
#include <qsize.h>
#include <qevent.h>
#include <qpainter.h>
#include <qcolor.h>

class QHBoxLayout;
class YKIconButton;

class YKLineEdit : public QLineEdit {
	Q_OBJECT
public:
	// 边框信息
	struct BorderInfo {
		int m_border_radius = 0;
		int m_border_width = 0;
		QColor m_normal_color;
		QColor m_hover_color;
		QColor m_focus_color;
	};

	// 图标信息
	struct IconInfo {
		QSize m_left_size;
		int m_padding_left = 0;
		QString m_left_icon_normal;
		QString m_left_icon_hover;
		QString m_left_icon_press;
		bool m_have_left_icon = false;

		QSize m_right_size;
		int m_padding_right = 0;
		QString m_right_icon_normal;
		QString m_right_icon_hover;
		QString m_right_icon_press;
		bool m_have_right_icon = false;
	};

	// 文字信息
	struct TextInfo {
		int m_font_size = 0;
		QString m_font_color;
		int m_padding_left = 0;
		int m_padding_right = 0;
	};

	YKLineEdit(QWidget* parent = nullptr);
	~YKLineEdit() = default;

	void Init(const QSize& size, const QString& placeholderText, BorderInfo border_info, IconInfo icon_info, TextInfo text_info, const QColor& brackground_color);

	virtual void paintEvent(QPaintEvent* event) override;
	virtual void leaveEvent(QEvent* event) override;
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
	virtual void enterEvent(QEnterEvent* event) override;
#else
	virtual void enterEvent(QEvent* event) override;
#endif

	virtual void focusInEvent(QFocusEvent* event) override;
	virtual void focusOutEvent(QFocusEvent* event) override;

	YKIconButton* m_btn_left = nullptr;
	YKIconButton* m_btn_right = nullptr;
private:
	QHBoxLayout* m_hbox_main_layout = nullptr;
	

	BorderInfo m_border_info;
	IconInfo m_icon_info;
	TextInfo m_text_info;

	bool m_cursor_in = false;

	bool m_focus_in = false;

	QColor m_brackground_color;
};

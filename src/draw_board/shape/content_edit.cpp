#include "content_edit.h"
#include <qtextdocument.h>
#include <qtextboundaryfinder.h>
#include <qdebug.h>
#include <qboxlayout.h>
#include <qsizepolicy.h>
#include <qpixmap.h>
#include "public/yk_icon_button.h"
#include "shape_const_def.h"

TextEditWidget::TextEditWidget(QWidget* parent) : AutoSizeWidget(false, parent) {
    InitView();
    InitSigChannel();
}


TextEditWidget::~TextEditWidget() {
}

void TextEditWidget::InitView() {
    setMouseTracking(true);
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("background-color:#ddeeff;");

    auto main_vlayout = new QVBoxLayout(bak_);
    main_vlayout->setAlignment(Qt::AlignTop);
    main_vlayout->setContentsMargins(0, 0, 0, 0);
    main_vlayout->setSpacing(0);

    title_bar_ = new QWidget();
    title_bar_->setMouseTracking(true);
    title_bar_->setStyleSheet("background-color:#ddeeff;");
    title_bar_->setFixedHeight(kTextEditTitleBarHeight);
    auto title_hlayout = new QHBoxLayout(title_bar_);
    title_hlayout->setAlignment(Qt::AlignTop);
    title_hlayout->setContentsMargins(0, 0, 0, 0);
    title_hlayout->setSpacing(0);

    ok_btn_ = new YKIconButton();
    ok_btn_->Init(QSize(30, 30), ":/draw_board/image/ok_normal.svg", ":/draw_board/image/ok_hover.svg", ":/draw_board/image/ok_press.svg");
    ok_btn_->SetUseSvg(true);

    close_btn_ = new YKIconButton();
    close_btn_->Init(QSize(30, 30), ":/draw_board/image/close_normal.svg", ":/draw_board/image/close_hover.svg", ":/draw_board/image/close_press.svg");
    close_btn_->SetUseSvg(true);
    title_hlayout->addStretch(1);

    title_hlayout->addWidget(ok_btn_);
    title_hlayout->addSpacing(8);
    title_hlayout->addWidget(close_btn_);

    main_vlayout->addWidget(title_bar_);

    auto edit_hlayout = new QHBoxLayout();
    edit_hlayout->setContentsMargins(kTextEditContentMargin, 0, kTextEditContentMargin, kTextEditContentMargin);
    edit_ = new QTextEdit();
    edit_->setStyleSheet("background-color:#ffffff;");
    auto edit_size_policy = edit_->sizePolicy();
    edit_size_policy.setHorizontalPolicy(QSizePolicy::Expanding);
    edit_size_policy.setVerticalPolicy(QSizePolicy::Expanding);
    edit_hlayout->addWidget(edit_);
    main_vlayout->addLayout(edit_hlayout);
}

void TextEditWidget::mouseMoveEvent(QMouseEvent* event) {
    QRect title_rect = title_bar_->geometry();
    title_rect.setY(title_rect.y() + 16);
    if (title_rect.contains(event->pos())) {
        if (pressed_) {
            enter_move_state = true;
        }
    }
    if (enter_move_state) {
        setCursor(Qt::SizeAllCursor);
        move(event->pos() - point_ + pos());
        QWidget::mouseMoveEvent(event);
    }
    else {
        AutoSizeWidget::mouseMoveEvent(event);
    }
}


void TextEditWidget::mouseReleaseEvent(QMouseEvent* event) {
    pressed_ = false;
    enter_move_state = false;
    AutoSizeWidget::mouseReleaseEvent(event);
}

void TextEditWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        pressed_ = true;
        point_ = event->pos();
    }
    AutoSizeWidget::mousePressEvent(event);
}

void TextEditWidget::InitSigChannel() {
    connect(ok_btn_, &QPushButton::clicked, this, [=]() {
        if (edit_->toPlainText().isEmpty()) {
            emit SigCancel();
            return;
        }
        emit SigHtml(edit_->toHtml());
    });

    connect(close_btn_, &QPushButton::clicked, this, [=]() {
        emit SigCancel();
    });
}


void TextEditWidget::SetFocus() {
    setFocus();
    edit_->setFocus();
}

void TextEditWidget::Clear() {
    edit_->clear();
}

void TextEditWidget::SetHtml(const QString& html) {
    edit_->setHtml(html);
}

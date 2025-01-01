#include "draw_board_widget.h"
#include <qboxlayout.h>
#include <qfile.h>
#include <qdebug.h>
#include <qtoolbutton.h>
#include <qbuttongroup.h>
#include "public/yk_icon_button.h"
#include "draw_widget.h"

DrawBoardWidget::DrawBoardWidget(QWidget *parent): QWidget(parent) {
    resize(800, 600);
    InitView();
    InitSigChannel();
}

DrawBoardWidget::~DrawBoardWidget() {
    
}

void DrawBoardWidget::InitView() {
    const int kIconBtnSize = 30;

    setMouseTracking(true);
    setAttribute(Qt::WA_StyledBackground);
    this->setWindowTitle(QStringLiteral("白板"));
 
    auto main_vlayout = new QVBoxLayout(this);
    main_vlayout->setSpacing(0);
    main_vlayout->setAlignment(Qt::AlignTop);
    main_vlayout->setContentsMargins(0, 0, 0, 0);

    auto menu_bar_hlayout = new QHBoxLayout();
    menu_bar_hlayout->setSpacing(12);
    menu_bar_hlayout->setAlignment(Qt::AlignLeft);
    menu_bar_hlayout->setContentsMargins(0, 0, 0, 0);

    QWidget* shape_btn_bk_widget = new QWidget();
    shape_btn_bk_widget->setStyleSheet("border:1px solid #99aaee;");
    auto shape_btn_hlayout = new QHBoxLayout(shape_btn_bk_widget);
    shape_btn_hlayout->setSpacing(12);
    shape_btn_hlayout->setAlignment(Qt::AlignLeft);
    shape_btn_hlayout->setContentsMargins(8, 0, 8, 0);

    btn_group_ = new QButtonGroup();
    ellipase_btn_ = new YKIconButton();
    ellipase_btn_->Init(QSize(kIconBtnSize, kIconBtnSize), ":/draw_board/image/oper_icon/circle_normal.svg", ":/draw_board/image/oper_icon/circle_hover.svg", ":/draw_board/image/oper_icon/circle_press.svg");
    ellipase_btn_->SetUseSvg(true);
   
    rectangle_btn_ = new YKIconButton();
    rectangle_btn_->Init(QSize(kIconBtnSize, kIconBtnSize), ":/draw_board/image/oper_icon/rectangle_normal.svg", ":/draw_board/image/oper_icon/rectangle_hover.svg", ":/draw_board/image/oper_icon/rectangle_press.svg");
    rectangle_btn_->SetUseSvg(true);


    line_btn_ = new YKIconButton();
    line_btn_->Init(QSize(kIconBtnSize, kIconBtnSize), ":/draw_board/image/oper_icon/line_normal.svg", ":/draw_board/image/oper_icon/line_hover.svg", ":/draw_board/image/oper_icon/line_press.svg");
    line_btn_->SetUseSvg(true);

    custom_line_btn_ = new YKIconButton();
    custom_line_btn_->Init(QSize(kIconBtnSize, kIconBtnSize), ":/draw_board/image/oper_icon/draw_pen_normal.svg", ":/draw_board/image/oper_icon/draw_pen_hover.svg", ":/draw_board/image/oper_icon/draw_pen_press.svg");
    custom_line_btn_->SetUseSvg(true);

    text_btn_ = new YKIconButton();
    text_btn_->Init(QSize(kIconBtnSize, kIconBtnSize), ":/draw_board/image/oper_icon/text_edit_normal.svg", ":/draw_board/image/oper_icon/text_edit_hover.svg", ":/draw_board/image/oper_icon/text_edit_press.svg");
    text_btn_->SetUseSvg(true);

    delete_btn_ = new YKIconButton();
    delete_btn_->Init(QSize(kIconBtnSize, kIconBtnSize), ":/draw_board/image/oper_icon/delete_element_normal.svg", ":/draw_board/image/oper_icon/delete_element_hover.svg", ":/draw_board/image/oper_icon/delete_element_press.svg");
    delete_btn_->SetUseSvg(true);

    revoke_btn_ = new YKIconButton();
    revoke_btn_->Init(QSize(kIconBtnSize, kIconBtnSize), ":/draw_board/image/oper_icon/backspace_normal.svg", ":/draw_board/image/oper_icon/backspace_hover.svg", ":/draw_board/image/oper_icon/backspace_press.svg");
    revoke_btn_->SetUseSvg(true);

    btn_group_->addButton(ellipase_btn_);
    btn_group_->addButton(rectangle_btn_);
    btn_group_->addButton(line_btn_);
    btn_group_->addButton(custom_line_btn_);
    btn_group_->addButton(text_btn_);
    btn_group_->addButton(delete_btn_);
    btn_group_->addButton(revoke_btn_);
    btn_group_->setExclusive(true);

    shape_btn_hlayout->addWidget(ellipase_btn_);
    shape_btn_hlayout->addWidget(rectangle_btn_);
    shape_btn_hlayout->addWidget(line_btn_);
    shape_btn_hlayout->addWidget(custom_line_btn_);
    shape_btn_hlayout->addWidget(text_btn_);

    menu_bar_hlayout->addStretch(1);
    menu_bar_hlayout->addWidget(shape_btn_bk_widget);
    menu_bar_hlayout->addStretch(1);
    menu_bar_hlayout->addWidget(delete_btn_);
    menu_bar_hlayout->addWidget(revoke_btn_);
    menu_bar_hlayout->addSpacing(30);

    main_vlayout->addLayout(menu_bar_hlayout);

    draw_widget_ = new DrawWidget(this);
    main_vlayout->addWidget(draw_widget_);
}

void DrawBoardWidget::InitSigChannel() {
    connect(ellipase_btn_, &QToolButton::clicked, this, &DrawBoardWidget::OnEllipseBtnClicked);
    connect(rectangle_btn_, &QToolButton::clicked, this, &DrawBoardWidget::OnRectangleBtnClicked);
    connect(line_btn_, &QToolButton::clicked, this, &DrawBoardWidget::OnLineBtnClicked);
    connect(text_btn_, &QToolButton::clicked, this, &DrawBoardWidget::OnTextBtnClicked);
    connect(delete_btn_, &QToolButton::clicked, this, &DrawBoardWidget::OnDeleteBtnClicked);
    connect(revoke_btn_, &QToolButton::clicked, this, &DrawBoardWidget::OnRevokeBtnClicked);
    connect(custom_line_btn_, &QToolButton::clicked, this, &DrawBoardWidget::OnCustomLineBtnClicked);
}


void DrawBoardWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
}

void DrawBoardWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Delete: {
        if(draw_widget_->cur_select_shape_ ){
            draw_widget_->shapes_.erase(std::remove(draw_widget_->shapes_.begin(), draw_widget_->shapes_.end(), draw_widget_->cur_select_shape_), draw_widget_->shapes_.end());
            draw_widget_->cur_select_shape_ = NULL;
        }
        break;
    }
    case Qt::Key_Escape:
        draw_widget_->SetShapeType(EShapeType::kUnkonwn);
        draw_widget_->cur_select_shape_ = NULL;
        break;
    case Qt::Key_Return:
        break;
    case Qt::Key_F1:
        break;
    }
    QWidget::keyPressEvent(event);
}

void DrawBoardWidget::keyReleaseEvent(QKeyEvent *event) {
    QWidget::keyReleaseEvent(event);
}

void DrawBoardWidget::OnRectangleBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kReckangle);
    rectangle_btn_->setStyleSheet(tool_btn_style_);
}

void DrawBoardWidget::OnEllipseBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kEllipse);
    ellipase_btn_->setStyleSheet(tool_btn_style_);
}

void DrawBoardWidget::OnLineBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kLine);
    line_btn_->setStyleSheet(tool_btn_style_);
}

void DrawBoardWidget::OnTextBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kText);
    text_btn_->setStyleSheet(tool_btn_style_);
}

void DrawBoardWidget::OnDeleteBtnClicked() {
    if (draw_widget_->cur_select_shape_) {
        draw_widget_->shapes_.erase(std::remove(draw_widget_->shapes_.begin(), draw_widget_->shapes_.end(), draw_widget_->cur_select_shape_), draw_widget_->shapes_.end());
        draw_widget_->cur_select_shape_ = NULL;
    }
}

void DrawBoardWidget::OnRevokeBtnClicked() {
    draw_widget_->Revoke();
}

void DrawBoardWidget::OnCustomLineBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kCustomLine);
}
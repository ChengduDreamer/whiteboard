#include "draw_board_widget.h"
#include <qboxlayout.h>
#include <qfile.h>
#include <qdebug.h>
#include <qtoolbutton.h>
#include <qbuttongroup.h>
#include "draw_widget.h"

DrawBoardWidget::DrawBoardWidget(QWidget *parent): QWidget(parent) {

    resize(800, 600);

    InitView();
    InitSigChannel();
}

DrawBoardWidget::~DrawBoardWidget() {
    
}

void DrawBoardWidget::InitView() {
    int ICON_SIZE = 64;

    setMouseTracking(true);
    setAttribute(Qt::WA_StyledBackground);
    this->setWindowTitle(QStringLiteral("画图板"));
    this->setWindowIcon(QIcon(QString(":/Icon.png")));
    tool_btn_style_ = R"(QToolButton {background-color:#00BFFF;padding:0px;margin:2px;border:none;font-family:'YouYuan';font-size:14px;color:#222222;}
        QToolButton:hover{background-color:#1E90FF;}
        QToolButton:checked {background-color:#1E90FF;border:2px solid #9932CC;padding:0px;margin:2px;font-family:'YouYuan';font-size:14px;color:#222222;})";

    auto main_vlayout = new QVBoxLayout(this);
    main_vlayout->setSpacing(0);
    main_vlayout->setAlignment(Qt::AlignTop);
    main_vlayout->setContentsMargins(0, 0, 0, 0);

    auto operation_hlayout = new QHBoxLayout();
    operation_hlayout->setSpacing(0);
    operation_hlayout->setAlignment(Qt::AlignLeft);
    operation_hlayout->setContentsMargins(0, 0, 0, 0);

    btn_group_ = new QButtonGroup();
    ellipase_btn_ = new QToolButton(this);
    ellipase_btn_->setText("椭圆");
    ellipase_btn_->setIcon(QIcon(QString(":/Ellipase.png")));
    ellipase_btn_->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    ellipase_btn_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ellipase_btn_->setStyleSheet(tool_btn_style_);

    rectangle_btn_ = new QToolButton(this);
    rectangle_btn_->setText("矩形");
    rectangle_btn_->setIcon(QIcon(QString(":/Rectangle.png")));
    rectangle_btn_->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    rectangle_btn_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    rectangle_btn_->setStyleSheet(tool_btn_style_);

    
    line_btn_ = new QToolButton(this);
    line_btn_->setText("直线");
    line_btn_->setIcon(QIcon(QString(":/Line.png")));
    line_btn_->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    line_btn_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    line_btn_->setStyleSheet(tool_btn_style_);

    custom_line_btn_ = new QToolButton(this);
    custom_line_btn_->setText("画笔");
    custom_line_btn_->setIcon(QIcon(QString(":/Line.png")));
    custom_line_btn_->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    custom_line_btn_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    custom_line_btn_->setStyleSheet(tool_btn_style_);


    text_btn_ = new QToolButton(this);
    text_btn_->setText("文字");
    text_btn_->setIcon(QIcon(QString(":/Text.png")));
    text_btn_->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    text_btn_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    text_btn_->setStyleSheet(tool_btn_style_);

    select_btn_ = new QToolButton(this);
    select_btn_->setText("选择");
    select_btn_->setObjectName(QString("RotateBtn"));
    select_btn_->setIcon(QIcon(QString(":/Select.png")));
    select_btn_->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    select_btn_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    revoke_btn_ = new QToolButton(this);
    revoke_btn_->setText("撤销");
    revoke_btn_->setObjectName(QString("RotateBtn"));
    revoke_btn_->setIcon(QIcon(QString(":/Select.png")));
    revoke_btn_->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    revoke_btn_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    btn_group_->addButton(ellipase_btn_);
    btn_group_->addButton(rectangle_btn_);
    //btn_group_->addButton(triangle_btn_);
    btn_group_->addButton(line_btn_);
    btn_group_->addButton(custom_line_btn_);
    btn_group_->addButton(text_btn_);
    //btn_group_->addButton(erasure_btn_);
    btn_group_->addButton(select_btn_);
    btn_group_->addButton(revoke_btn_);
    btn_group_->setExclusive(true);

    operation_hlayout->addWidget(ellipase_btn_);
    operation_hlayout->addWidget(rectangle_btn_);
    //operation_hlayout->addWidget(triangle_btn_);
    operation_hlayout->addWidget(line_btn_);
    operation_hlayout->addWidget(custom_line_btn_);
    operation_hlayout->addWidget(text_btn_);
    //operation_hlayout->addWidget(erasure_btn_);
    operation_hlayout->addWidget(select_btn_);
    operation_hlayout->addWidget(revoke_btn_);

    main_vlayout->addLayout(operation_hlayout);

    draw_widget_ = new DrawWidget(this);

    main_vlayout->addWidget(draw_widget_);
}

void DrawBoardWidget::InitSigChannel() {
    connect(ellipase_btn_, &QToolButton::clicked, this, &DrawBoardWidget::OnEllipseBtnClicked);
    connect(rectangle_btn_, &QToolButton::clicked, this, &DrawBoardWidget::OnRectangleBtnClicked);
    connect(line_btn_, &QToolButton::clicked, this, &DrawBoardWidget::OnLineBtnClicked);
    connect(text_btn_, &QToolButton::clicked, this, &DrawBoardWidget::OnTextBtnClicked);
    connect(select_btn_, &QToolButton::clicked, this, &DrawBoardWidget::OnSelectBtnClicked);
    connect(revoke_btn_, &QToolButton::clicked, this, &DrawBoardWidget::OnRevokeBtnClicked);
    connect(custom_line_btn_, &QToolButton::clicked, this, &DrawBoardWidget::OnCustomLineBtnClicked);
}


void DrawBoardWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
}

void DrawBoardWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Delete:
    {
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
    draw_widget_->SetShapeType(EShapeType::kReckangle);// 设置当前选中的图像类型
    rectangle_btn_->setStyleSheet(tool_btn_style_);// 设置现在选中的类型，进行按钮的颜色标记
    draw_widget_->select_btn_clicked_ = false;// 这个按钮只有在需要选择面板中的图像元素的时候才进行设置true
}

void DrawBoardWidget::OnEllipseBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kEllipse);
    ellipase_btn_->setStyleSheet(tool_btn_style_);
    draw_widget_->select_btn_clicked_ = false;
}

void DrawBoardWidget::OnLineBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kLine);
    line_btn_->setStyleSheet(tool_btn_style_);
    draw_widget_->select_btn_clicked_ = false;
}

void DrawBoardWidget::OnTextBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kText);
    text_btn_->setStyleSheet(tool_btn_style_);
    draw_widget_->select_btn_clicked_ = false;
}

void DrawBoardWidget::OnSelectBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kUnkonwn);
    draw_widget_->select_btn_clicked_ = true;
}

void DrawBoardWidget::OnRevokeBtnClicked() {
    draw_widget_->Revoke();
}

void DrawBoardWidget::OnCustomLineBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kCustomLine);
    draw_widget_->select_btn_clicked_ = false;
}
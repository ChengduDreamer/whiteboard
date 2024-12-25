#include "CDrawBoardWidget.h"
#include <qboxlayout.h>
#include <qfile.h>
#include <qdebug.h>
#include <qtoolbutton.h>
#include <qbuttongroup.h>

CDrawBoardWidget::CDrawBoardWidget(QWidget *parent): QWidget(parent) {

    resize(800, 600);

    InitView();
    InitSigChannel();
}

CDrawBoardWidget::~CDrawBoardWidget() {
    
}

void CDrawBoardWidget::InitView() {
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

    /*triangle_btn_ = new QToolButton(this);
    triangle_btn_->setText("三角形");
    triangle_btn_->setIcon(QIcon(QString(":/Triangle.png")));
    triangle_btn_->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    triangle_btn_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    triangle_btn_->setStyleSheet(tool_btn_style_);*/

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

   /* erasure_btn_ = new QToolButton(this);
    erasure_btn_->setText("擦除");
    erasure_btn_->setObjectName(QString("RotateBtn"));
    erasure_btn_->setIcon(QIcon(QString(":/Erasure.png")));
    erasure_btn_->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    erasure_btn_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);*/

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

void CDrawBoardWidget::InitSigChannel() {
    connect(ellipase_btn_, &QToolButton::clicked, this, &CDrawBoardWidget::OnEllipseBtnClicked);
    connect(rectangle_btn_, &QToolButton::clicked, this, &CDrawBoardWidget::OnRectangleBtnClicked);
    //connect(triangle_btn_, &QToolButton::clicked, this, &CDrawBoardWidget::OnTriangleBtnClicked);
    connect(line_btn_, &QToolButton::clicked, this, &CDrawBoardWidget::OnLineBtnClicked);
    connect(text_btn_, &QToolButton::clicked, this, &CDrawBoardWidget::OnTextBtnClicked);
    //connect(erasure_btn_, &QToolButton::clicked, this, &CDrawBoardWidget::OnErasureBtnClicked);
    connect(select_btn_, &QToolButton::clicked, this, &CDrawBoardWidget::OnSelectBtnClicked);
    connect(revoke_btn_, &QToolButton::clicked, this, &CDrawBoardWidget::OnRevokeBtnClicked);

    connect(custom_line_btn_, &QToolButton::clicked, this, &CDrawBoardWidget::OnCustomLineBtnClicked);
}


void CDrawBoardWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
}

void CDrawBoardWidget::keyPressEvent(QKeyEvent *event)
{

    //    https://www.cnblogs.com/linuxAndMcu/p/11023299.html#:~:text=%2F%2F%20%E9%94%AE%E7%9B%98%E6%8C%89%E4%B8%8B%E4%BA%8B%E4%BB%B6%20void%20Widget%3A%3AkeyPressEvent%28QKeyEvent%20%2A%20event%29%20%7B%20%2F%2F,%3C%3C%20%22release%3A%20%22%20%3C%3C%20%22up%22%20%3B%20%7D%20%7D
    // 普通键
    switch (event->key())
    {
    // Delete
    case Qt::Key_Delete:
    {
        if(draw_widget_->cur_selected_shape_index_ != -1){ // to do 判断 shapes_ 数量
            draw_widget_->shapes_.erase(draw_widget_->shapes_.begin() + draw_widget_->cur_selected_shape_index_);
         //   draw_widget_->m_pSystemData->RemoveShapePointMap(draw_widget_->cur_selected_shape_index_);
            draw_widget_->cur_select_shape_ = NULL; // 边框也去除
        }
        break;
    }
        // ESC键
    case Qt::Key_Escape:
        qDebug() <<"ESC";
        draw_widget_->SetShapeType(EShapeType::kUnkonwn);
        break;
        // 回车键
    case Qt::Key_Return:
        qDebug() <<"Enter";
        break;
        // F1键
    case Qt::Key_F1:
        qDebug() <<"F1";
        break;
    }
    QWidget::keyPressEvent(event);
}

void CDrawBoardWidget::keyReleaseEvent(QKeyEvent *event) {
    QWidget::keyReleaseEvent(event);
}

void CDrawBoardWidget::OnRectangleBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kReckangle);// 设置当前选中的图像类型
    rectangle_btn_->setStyleSheet(tool_btn_style_);// 设置现在选中的类型，进行按钮的颜色标记
    draw_widget_->select_btn_clicked_ = false;// 这个按钮只有在需要选择面板中的图像元素的时候才进行设置true
}

void CDrawBoardWidget::OnEllipseBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kEllipse);
    ellipase_btn_->setStyleSheet(tool_btn_style_);
    draw_widget_->select_btn_clicked_ = false;
}

//void CDrawBoardWidget::OnTriangleBtnClicked() {
//    draw_widget_->SetShapeType(EShapeType::Shape_Triangle);
//    triangle_btn_->setStyleSheet(tool_btn_style_);
//    draw_widget_->select_btn_clicked_ = false;
//}

void CDrawBoardWidget::OnLineBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kLine);
    line_btn_->setStyleSheet(tool_btn_style_);
    draw_widget_->select_btn_clicked_ = false;
}

void CDrawBoardWidget::OnTextBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kText);
    text_btn_->setStyleSheet(tool_btn_style_);
    draw_widget_->select_btn_clicked_ = false;
}

//void CDrawBoardWidget::OnErasureBtnClicked() {
//    draw_widget_->SetShapeType(EShapeType::Erasure);
//    draw_widget_->select_btn_clicked_ = false;
//    qDebug()<<QString(int(draw_widget_->GetShapeType()));
//}

void CDrawBoardWidget::OnSelectBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kUnkonwn);
    draw_widget_->select_btn_clicked_ = true;
}

void CDrawBoardWidget::OnRevokeBtnClicked() {

    draw_widget_->Revoke();
}

void CDrawBoardWidget::OnCustomLineBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kCustomLine);
   // line_btn_->setStyleSheet(tool_btn_style_);
    draw_widget_->select_btn_clicked_ = false;
}
#include "draw_widget.h"
#include <qsizepolicy.h>
#include "shape/content_edit.h"
#include "shape/custom_line_shape.h"
#include "shape/line_shape.h"
#include "shape/ellipse_shape.h"
#include "shape/rectangle_shape.h"
#include "shape/text_shape.h"
#include "shape/auto_size_widget.h"
#include "shape/shape_const_def.h"

DrawWidget::DrawWidget(QWidget *parent):QOpenGLWidget(parent) {
    InitView();
    InitSigChannel();
}

DrawWidget::~DrawWidget() {

}

void DrawWidget::paintEvent(QPaintEvent *event) {
    QOpenGLWidget::paintEvent(event); 
    QPainter painter(this);
    painter.setBrush(white_brush_);
    painter.drawRect(rect());// 整个窗体的矩形
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    
    // 设置画笔
    painter.setPen(black_pen_);
   // painter.setFont(text_font_);
    painter.setBrush(null_brush_);

    for (auto& shape : shapes_) {
        shape->DrawShape(painter);
    }

    // 这里是对当前选择的图元选项进行绘画
    if (EMouseState::kDrawShape == mouse_state_) {
        switch (draw_shape_type_) {
        case EShapeType::kReckangle: {
            static RectangleShape rect_shape;
            rect_shape.UpdateData(clicked_point_, move_point_);
            rect_shape.DrawShape(painter);
            break;
        }
        case EShapeType::kEllipse: {
            static EllipseShape ell;
            ell.UpdateData(clicked_point_, move_point_);
            ell.DrawShape(painter);
            break;
        }
        case EShapeType::kLine: {
            painter.drawLine(clicked_point_, move_point_);
            break;
        }
        case EShapeType::kText: {
            break;
        }
        case EShapeType::kCustomLine: {
            static CustomLineShape custom_line;
            custom_line.SetPointsData(points_data_);
            custom_line.DrawShape(painter);
            break;
        }
        default:
            break;
        }
    }

    // 对选中的图形 绘制边框
    if(cur_select_shape_){
        if (cur_select_shape_ != editing_text_shape_) {
            cur_select_shape_->PaintFrame(painter);
        }
    }

    update();
}

void DrawWidget::resizeEvent(QResizeEvent *event) {
    QOpenGLWidget::resizeEvent(event);
}

void DrawWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() != Qt::MouseButton::LeftButton) {
        QOpenGLWidget::mousePressEvent(event);
        return;
    }
    points_data_.clear();
    mouse_left_btn_pressed_ = true; 
    clicked_point_ = event->pos();
    move_point_ = event->pos();
    // 鼠标摁下时候 判断 是拖拽 还是 绘制
    for (auto& shape : shapes_) {
        if (shape->EnterSelectRange(clicked_point_)) {
            mouse_state_ = EMouseState::kMoveShape;
            cur_select_shape_ = shape;
            break;
        }
    }
    if (mouse_state_ != EMouseState::kMoveShape) {
        cur_select_shape_ = nullptr;
        if (EShapeType::kUnkonwn != draw_shape_type_) {
            mouse_state_ = EMouseState::kDrawShape;
        }
    }       
    QOpenGLWidget::mousePressEvent(event);
}

// 双击时候 判断鼠标坐标如果在文字图形范围内，就让该文字图元进入编辑状态
void DrawWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() != Qt::MouseButton::LeftButton) {
        QOpenGLWidget::mouseDoubleClickEvent(event);
    }
    QPoint point = event->pos();
    std::shared_ptr<BaseShape> can_select_shape = nullptr;
    for (auto& shape : shapes_) {
        if (shape->EnterSelectRange(point)) {
            can_select_shape = shape;
            break;
        }
    }
    if (can_select_shape) {
        if (EShapeType::kText == can_select_shape->GetShapeType()) {
            editing_text_shape_ = std::dynamic_pointer_cast<TextShape>(can_select_shape);
            editing_text_shape_->SetHiden(true);
            text_edit_->SetHtml(editing_text_shape_->GetHtml());
            text_edit_->show();
            auto point = editing_text_shape_->start_point_;
            point.setX(point.x() - kTextEditContentMargin);
            point.setY(point.y() - kTextEditTitleBarHeight);
            text_edit_->move(point.toPoint());
        }
    }
    QOpenGLWidget::mouseDoubleClickEvent(event);
}

void DrawWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() != Qt::MouseButton::LeftButton) {
        QOpenGLWidget::mouseReleaseEvent(event);
        return;
    }

    mouse_left_btn_pressed_ = false;
    //cur_select_shape_ = nullptr;
    move_point_ = event->pos();

    if (EMouseState::kDrawShape == mouse_state_) {
        switch (draw_shape_type_) {
        case EShapeType::kReckangle: {
            int min_x = clicked_point_.x() < move_point_.x() ? clicked_point_.x() : move_point_.x();
            int min_y = clicked_point_.y() < move_point_.y() ? clicked_point_.y() : move_point_.y();
            QPoint dif = move_point_ - clicked_point_;
            std::shared_ptr<RectangleShape> rect = RectangleShape::Make(double(min_x), double(min_y), qAbs(double(dif.x())), qAbs(double(dif.y())));
            shapes_.emplace_back(rect);
            break;
        }
        case EShapeType::kEllipse: {
            int min_x = clicked_point_.x() < move_point_.x() ? clicked_point_.x() : move_point_.x();
            int min_y = clicked_point_.y() < move_point_.y() ? clicked_point_.y() : move_point_.y();
            QPoint dif = move_point_ - clicked_point_;
            std::shared_ptr<EllipseShape> elli = EllipseShape::Make(double(min_x), double(min_y), qAbs(double(dif.x())), qAbs(double(dif.y())));
            shapes_.emplace_back(elli);
            break;
        }
        case EShapeType::kLine: {
            std::shared_ptr<LineShape> line = LineShape::Make(clicked_point_, move_point_);
            shapes_.emplace_back(line);
            break;
        }
        case EShapeType::kText: {
            text_point_ = move_point_;
            text_edit_->Clear();
            text_edit_->show();
            text_edit_->move(text_point_);
            text_edit_->SetFocus();
            break;
        }
        case EShapeType::kCustomLine: {
            if (points_data_.size() >= 2) {
                std::shared_ptr<CustomLineShape> cli = CustomLineShape::Make(points_data_);
                shapes_.emplace_back(cli);
                break;
            }
        }
        default:
            break;
        }
    }
    mouse_state_ = EMouseState::kGeneral;
    points_data_.clear();
    update();
    QOpenGLWidget::mouseReleaseEvent(event);
}

void DrawWidget::Revoke() {
    if (!shapes_.empty()) {
        shapes_.pop_back();
    }
    update();
}


void DrawWidget::mouseMoveEvent(QMouseEvent *event) {
    QPoint point = event->pos();
    bool can_selecte = false;
    for (auto& shape: shapes_) {
        if (shape->EnterSelectRange(point)) {
            can_selecte = true; 
            break;
        }
    }

    switch (mouse_state_)
    {
    case DrawWidget::EMouseState::kGeneral:
        if (can_selecte) {
            setCursor(Qt::OpenHandCursor);
        }
        else {
            if (EShapeType::kUnkonwn == draw_shape_type_) {
                setCursor(Qt::ArrowCursor);
            }
            else {
                setCursor(Qt::CrossCursor);
            }
        }
        break;
    case DrawWidget::EMouseState::kMoveShape:
        setCursor(Qt::OpenHandCursor);
        if (cur_select_shape_) {
            cur_select_shape_->MoveShape(move_point_, event->pos());
            update();
        }
        break;
    case DrawWidget::EMouseState::kDrawShape:
        setCursor(Qt::CrossCursor);
        break;
    default:
        setCursor(Qt::ArrowCursor);
        break;
    }

    move_point_ = event->pos();

    if(mouse_left_btn_pressed_) {
        if (EShapeType::kCustomLine == draw_shape_type_) {
            points_data_.append(event->pos());
        }
    }

    QOpenGLWidget::mouseMoveEvent(event);
}


void DrawWidget::InitSigChannel() {
    connect(text_edit_, &TextEditWidget::SigHtml, this, [=](QString html) {
        if(editing_text_shape_) {  // 如果是正在编辑的，就修改编辑的textshape
            editing_text_shape_->SetHtml(html);
            editing_text_shape_->SetHiden(false);
            editing_text_shape_->SetStartPoint(QPoint(text_edit_->pos().x() + kTextEditContentMargin, text_edit_->pos().y() + kTextEditTitleBarHeight));
            editing_text_shape_ = nullptr;
        }
        else {
            std::shared_ptr<TextShape> text_shape = TextShape::Make(QPoint(text_edit_->pos().x() + kTextEditContentMargin, text_edit_->pos().y() + kTextEditTitleBarHeight), html, this);
            shapes_.emplace_back(text_shape);
        }
        text_edit_->hide();
    });

    connect(text_edit_, &TextEditWidget::SigCancel, this, [=]() {
        text_edit_->Clear();
        text_edit_->hide();
        if (editing_text_shape_) {  // 如果是正在编辑的，就再显示回来
            editing_text_shape_->SetHiden(false);
            editing_text_shape_->SetStartPoint(QPoint{ text_edit_->pos().x() + kTextEditContentMargin, text_edit_->pos().y() + kTextEditTitleBarHeight });
            editing_text_shape_ = nullptr;
        }
    });
}

void DrawWidget::InitView() {
    setMouseTracking(true);
    auto sizepolicy = this->sizePolicy();
    sizepolicy.setHorizontalPolicy(QSizePolicy::Expanding);
    sizepolicy.setVerticalPolicy(QSizePolicy::Expanding);
    setSizePolicy(sizepolicy);

    mouse_left_btn_pressed_ = false;
    draw_shape_type_ = EShapeType::kUnkonwn;

    black_pen_.setColor(QColor(0, 0, 0));
    black_pen_.setWidth(2);
    text_font_.setFamily(QStringLiteral("Microsoft YaHei"));
    text_font_.setPixelSize(20);
    white_brush_.setColor(QColor(255, 255, 255));
    white_brush_.setStyle(Qt::BrushStyle::SolidPattern);
    null_brush_.setStyle(Qt::BrushStyle::NoBrush);

    text_edit_ = new TextEditWidget(this);
    text_edit_->hide();
    text_edit_->setFont(text_font_);

    this->setMouseTracking(true);

    resize(800, 600);
}


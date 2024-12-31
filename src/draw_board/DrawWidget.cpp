#include "DrawWidget.h"
#include <qsizepolicy.h>
#include "shape/auto_size_widget.h"
#include "shape/shape_const_def.h"

DrawWidget::DrawWidget(QWidget *parent):QOpenGLWidget(parent) {
    InitView();
    InitSigChannel();
}

DrawWidget::~DrawWidget()
{

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

    // 这里是对当前按下的按钮选项进行绘画
    /*if(mouse_left_btn_clicked_ || (m_DemensionBtnClicked && this->DemensionsPoint.size() == 3)){*/
    if (EMouseState::kDrawShape == mouse_state_) {
        if (/*EMouseState::kMoveShape != mouse_state_*/ 1) {
            switch (shape_type_) {
            case EShapeType::kReckangle: {
                static RectangleShape rect_shape;
                rect_shape.UpdateData(clicked_point_, move_point_);
                rect_shape.DrawShape(painter);

                mouse_state_ = EMouseState::kDrawShape;

                break;
            }
            case EShapeType::kEllipse: {
                static EllipseShape ell;
                ell.UpdateData(clicked_point_, move_point_);
                ell.DrawShape(painter);

                mouse_state_ = EMouseState::kDrawShape;

                break;
            }
            case EShapeType::kLine: {
                painter.drawLine(clicked_point_, move_point_);

                mouse_state_ = EMouseState::kDrawShape;
                break;
            }
            case EShapeType::kText: {
                break;
            }
            case EShapeType::kCustomLine: {
                static CustomLineShape custom_line;
                custom_line.SetPointsData(points_data_);
                custom_line.DrawShape(painter);

                mouse_state_ = EMouseState::kDrawShape;
                break;
            }
            default:
                break;
            }
        
        }
    }

    // 对选中的图形 绘制边框
    if(cur_select_shape_){
        cur_select_shape_->PaintFrame(painter);
    }

    update();
}

void DrawWidget::resizeEvent(QResizeEvent *event)
{
    QOpenGLWidget::resizeEvent(event);
}

void DrawWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton){
        // to do clear point_data
        points_data_.clear();

        mouse_left_btn_pressed_ = true; // 鼠标左键按下
        //if(this->m_CapturePoint){ // 如果鼠标捕获了点，就直接以捕获点为绘制的点
        //    clicked_point_ = *(this->m_CapturePoint);
        //
        //}else {
        //    clicked_point_ = event->pos();// 设置按下的位置
        //}
        clicked_point_ = event->pos();

        // 鼠标摁下时候 判断 是拖拽 还是 绘制
        //std::shared_ptr<BaseShape> can_select_shape = nullptr;
        for (auto& shape : shapes_) {
            if (shape->EnterSelectRange(clicked_point_)) {
                mouse_state_ = EMouseState::kMoveShape;
                //can_select_shape = shape;
                cur_select_shape_ = shape;
                break;
            }
        }
        if (mouse_state_ != EMouseState::kMoveShape) {
            if (EShapeType::kUnkonwn != shape_type_) {
                mouse_state_ = EMouseState::kDrawShape;
            }
        }
        move_point_ = event->pos(); // 单击时，对移动位置进行初始化
       
    }
    QOpenGLWidget::mousePressEvent(event);
}


void DrawWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton){
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
                //text_edit_->Clear();
                qDebug() << "html : " << editing_text_shape_->GetHtml();
                text_edit_->SetHtml(editing_text_shape_->GetHtml());
                text_edit_->show();
                auto point = editing_text_shape_->start_point_;
                point.setX(point.x() - kTextEditContentMargin);
                point.setY(point.y() - kTextEditTitleBarHeight);
                text_edit_->move(point.toPoint());
            }
        }
    }

    QOpenGLWidget::mouseDoubleClickEvent(event);
}

void DrawWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton){
        mouse_left_btn_pressed_ = false;
        cur_select_shape_ = nullptr; 
        
        move_point_ = event->pos();
        if (EMouseState::kDrawShape == mouse_state_) {
            switch (shape_type_) {
            case EShapeType::kReckangle: {
                int min_x = clicked_point_.x() < move_point_.x() ? clicked_point_.x() : move_point_.x();
                int min_y = clicked_point_.y() < move_point_.y() ? clicked_point_.y() : move_point_.y();
                QPoint dis = move_point_ - clicked_point_;
                std::shared_ptr<RectangleShape> rect = RectangleShape::Make(double(min_x), double(min_y), qAbs(double(dis.x())), qAbs(double(dis.y())));
                shapes_.emplace_back(rect);
                break;
            }
            case EShapeType::kEllipse: {
                int min_x = clicked_point_.x() < move_point_.x() ? clicked_point_.x() : move_point_.x();
                int min_y = clicked_point_.y() < move_point_.y() ? clicked_point_.y() : move_point_.y();
                QPoint dis = move_point_ - clicked_point_;
                std::shared_ptr<EllipseShape> elli = EllipseShape::Make(double(min_x), double(min_y), qAbs(double(dis.x())), qAbs(double(dis.y())));
                shapes_.emplace_back(elli);
                break;
            }
            case EShapeType::kLine: {
                //std::shared_ptr<LineShape> line = std::make_shared<LineShape>(double(clicked_point_.x()), double(clicked_point_.y()), double(move_point_.x()), double(move_point_.y()));
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
                    points_data_.clear();
                    break;
                }
            }
            default:
                break;
            }
        
        }
        mouse_state_ = EMouseState::kGeneral;
    }
    update();
    QOpenGLWidget::mouseReleaseEvent(event);
}

void DrawWidget::Revoke() {
    if (!shapes_.empty()) {
        shapes_.pop_back();
    }
    update();
}

// 本窗口鼠标移动事件
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
            if (EShapeType::kUnkonwn == shape_type_) {
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
            //shape_type_ = EShapeType::kUnkonwn;
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

    /*if (can_selecte) {
        setCursor(Qt::OpenHandCursor);
    }
    else {
        if (EShapeType::kUnkonwn == shape_type_) {
            setCursor(Qt::ArrowCursor);
        }
        else {
            setCursor(Qt::CrossCursor);
        }
    }*/

    //if (mouse_left_btn_pressed_) {
    //    if (cur_select_shape_) {
    //        cur_select_shape_->MoveShape(move_point_, event->pos());
    //        //shape_type_ = EShapeType::kUnkonwn;
    //        update();
    //    }
    //}


    // 移动选中的对象
   // if(cur_select_shape_ && mouse_left_btn_pressed_){
   //     cur_select_shape_->MoveShape(move_point_, event->pos());
   //     update();
   // }
    move_point_ = event->pos();

    if(mouse_left_btn_pressed_) {
        
        update();
        if (EShapeType::kCustomLine == shape_type_) {
            points_data_.append(event->pos());
        }
    }

    QOpenGLWidget::mouseMoveEvent(event);
}


void DrawWidget::InitSigChannel() {
    connect(text_edit_, &TextEditWidget::SigHtml, this, [=](QString html) {
        qDebug() << "text_edit_ x = " << double(text_edit_->pos().x()) + 4 << ", y = " << double(text_edit_->pos().y() + 30);
        if(editing_text_shape_) {  // 如果是正在编辑的，就修改编辑的textshape
            editing_text_shape_->SetHtml(html);
            editing_text_shape_->SetHiden(false);
            editing_text_shape_->SetStartPoint(QPoint(text_edit_->pos().x() + kTextEditContentMargin, text_edit_->pos().y() + kTextEditTitleBarHeight));
            editing_text_shape_ = nullptr;
        }
        else {

            std::shared_ptr<TextShape> text_shape = TextShape::Make(QPoint(text_edit_->pos().x() + kTextEditContentMargin, text_edit_->pos().y() + kTextEditTitleBarHeight), html, this);


            //std::shared_ptr<TextShape> text_shape = std::make_shared<TextShape>(double(text_edit_->pos().x()) + kTextEditContentMargin, double(text_edit_->pos().y() + kTextEditTitleBarHeight), html, this);
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

    //m_pSystemData = SystemData::GetSystemData();

    mouse_left_btn_pressed_ = false;
    shape_type_ = EShapeType::kUnkonwn;

    black_pen_.setColor(QColor(0, 0, 0));
    text_font_.setFamily(QStringLiteral("Microsoft YaHei"));
    text_font_.setPixelSize(20);
    white_brush_.setColor(QColor(255, 255, 255));
    white_brush_.setStyle(Qt::BrushStyle::SolidPattern);
   
    null_brush_.setStyle(Qt::BrushStyle::NoBrush);
    //m_ErasureBrush = white_brush_;//画笔
    //m_ErasurePen = QPen(white_brush_,10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    //    //    m_ErasurePen = QPen(QBrush(QColor(255,0,0)),10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    //    DemensionsPoint.resize(3);// 确定存储三个点，没有的话就自动赋值就好了

    //content_edit_.setParent(this);
    //content_edit_.hide();
    //content_edit_.setFont(text_font_);
    //m_RotateType = ERotateType::Rotate_0;// 默认0度


    text_edit_ = new TextEditWidget(this);
    text_edit_->hide();
    text_edit_->setFont(text_font_);


    this->setMouseTracking(true);// 设置为不按下鼠标键触发moveEvent，对moveevent起作用

    //QObject::connect(&content_edit_,SIGNAL(Signal_GetContent(QString)),this,SLOT(fn_Recv_ContentEdit_GetContent(QString)),Qt::ConnectionType::DirectConnection);

    //m_StatusEdit.setGeometry(0,this->height() + 20,this->width(),20);
    //m_StatusEdit.setStyleSheet("QLineEdit{background-color:transparent}""QLineEdit{border-width:0;border-style:outset}");
    //connect(&m_StatusEdit,SIGNAL(textChanged(QString)),this,SLOT(fn_Change_StatusEdit_Visual(QString)),Qt::ConnectionType::DirectConnection);//有文本显示边框和背景颜色

    /*TextEditWidget* ew = new TextEditWidget(this);

    ew->move(200, 200);

    ew->resize(200, 200);*/


    // AutoSizeWidget* aw = new AutoSizeWidget(false, this);
    //
    // aw->move(100, 100);
    //
    // aw->resize(200, 200);

    resize(800, 600);

    
}


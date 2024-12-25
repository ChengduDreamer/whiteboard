#include "DrawWidget.h"
#include <qsizepolicy.h>
#include "shape/auto_size_widget.h"

DrawWidget::DrawWidget(QWidget *parent):QOpenGLWidget(parent)
{
    setMouseTracking(true);
    auto sizepolicy = this->sizePolicy();
    sizepolicy.setHorizontalPolicy(QSizePolicy::Expanding);
    sizepolicy.setVerticalPolicy(QSizePolicy::Expanding);
    setSizePolicy(sizepolicy);

    //m_pSystemData = SystemData::GetSystemData();

    mouse_left_btn_clicked_ = false;
    shape_type_ = EShapeType::kUnkonwn;

    //m_StatusEdit.setParent(this);
    black_pen_.setColor(QColor(0,0,0));
    text_font_.setFamily(QStringLiteral("Microsoft YaHei"));
    text_font_.setPixelSize(20);
    white_brush_.setColor(QColor(255,255,255));
    white_brush_.setStyle(Qt::BrushStyle::SolidPattern);
    /*m_BackgroundBrush.setColor(QColor(0 ,255, 0));
    m_BackgroundBrush.setStyle(Qt::BrushStyle::SolidPattern);*/
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

    connect(text_edit_, &TextEditWidget::SigHtml, this, [=](QString html) {
        

       // qDebug() << "text_edit_ x = " << text_point_.x() << ", y = " << text_point_.y();

        qDebug() << "text_edit_ x = " << double(text_edit_->pos().x()) + 4 << ", y = " << double(text_edit_->pos().y() + 30);

        
       std::shared_ptr<TextShape> text_shape = std::make_shared<TextShape>(double(text_edit_->pos().x()) + 4, double(text_edit_->pos().y() + 30), html, this);
       
       shapes_.emplace_back(text_shape);
       
       text_edit_->hide();
    });
}

DrawWidget::~DrawWidget()
{

}

void DrawWidget::paintEvent(QPaintEvent *event)
{
    QOpenGLWidget::paintEvent(event);    // 先调用再渲染

    QPainter painter(this);
    painter.setBrush(white_brush_);
    painter.drawRect(rect());// 整个窗体的矩形
    painter.setRenderHint(QPainter::Antialiasing);// 平滑曲线 防止图形走样
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);// 绘制结果 = 绘制输入，目的绘制区域原来的像素被完全覆盖。https://blog.csdn.net/yejin_tianming/article/details/105113668

    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::Antialiasing);

    // 设置画笔
    painter.setPen(black_pen_);
   // painter.setFont(text_font_);
    painter.setBrush(null_brush_);

    // 这里是对去全局进行绘画
    //int iSize = m_pSystemData->m_ShapeVec.size();
    //
    //// 画完容器里所有的图
    //for(int i =0;i<iSize;++i ){
    //    m_pSystemData->m_ShapeVec.at(i)->drawShape(painter);
    //    //        case EShapeType::kUnkonwn:
    //}

    for (auto& shape : shapes_) {
        shape->DrawShape(painter);
    }

    // 这里是对当前按下的按钮选项进行绘画
    /*if(mouse_left_btn_clicked_ || (m_DemensionBtnClicked && this->DemensionsPoint.size() == 3)){*/
    if (mouse_left_btn_clicked_) {
        switch (shape_type_) {
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
            /*text_point_ = clicked_point_;
            content_edit_.show();
            content_edit_.setGeometry(text_point_.x(), text_point_.y(), 200, 100);
            painter.drawText(QPoint(text_point_.x(), text_point_.y()), content_edit_.toPlainText());*/
            break;
        }
        case EShapeType::kCustomLine: {
            static CustomLineShape custom_line;
            custom_line.points_data_ = points_data_;
            custom_line.DrawShape(painter);
            break;
        }
        default:
            break;
        }

    }


    // 对尺寸进行标记

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
        mouse_left_btn_clicked_ = true; // 鼠标左键按下
        //if(this->m_CapturePoint){ // 如果鼠标捕获了点，就直接以捕获点为绘制的点
        //    clicked_point_ = *(this->m_CapturePoint);
        //
        //}else {
        //    clicked_point_ = event->pos();// 设置按下的位置
        //}
        clicked_point_ = event->pos();
        // 旋转需要执行的操作
        //if(this->m_RotateBtnClicked){
        //    QStringList rotateArgList = this->m_StatusEdit.text().split(":");
        //    //            for(auto st : rotateArgList){
        //    //                qDebug() << st;
        //    //            }
        //    //            qDebug() << rotateArgList.length();
        //    QString rotateArg = rotateArgList.at(rotateArgList.length()-1);
        //    bool isDigit = false;
        //    double arg = 90;
        //    double temp = rotateArg.toDouble(&isDigit);
        //    if(isDigit){
        //        arg = temp;
        //        //                qDebug() << QString("this arg")<< QString("%1").arg(arg);
        //    }
        //    //this->m_StartingClickPoint = &clicked_point_;
        //    this->cur_select_shape_->rotate(clicked_point_,arg);
        //    this->m_RotateBtnClicked = false;
        //    this->m_StatusEdit.clear();
        //}

        // 这里是对鼠标标注的操作
        //if(this->m_DemensionBtnClicked){
        //    //            qDebug() << QString("this->DemensionsPoint.size() press in:") <<  this->DemensionsPoint.size();
        //    this->DemensionsPoint.push_back(clicked_point_);
        //    if(this->DemensionsPoint.size() == 1){
        //        this->m_StatusEdit.setText("Select the second point of the object");
        //    }
        //    else if(this->DemensionsPoint.size() == 2){
        //        this->m_StatusEdit.setText("Please select a location for demensions");
        //    }else if(this->DemensionsPoint.size() == 4){
        //        this->DemensionsPoint.pop_back();
        //        this->DemensionsPoint.resize(3);
        //        this->m_StatusEdit.clear();
        //    }
        //    //            qDebug() << QString("this->DemensionsPoint.size() press out:") <<  this->DemensionsPoint.size();
        //}
       /* if(!this->m_DemensionBtnClicked && !DemensionsPoint.empty()){
            this->m_StatusEdit.clear();
        }*/

        move_point_ = event->pos(); // 单击时，对移动位置进行初始化
        cur_select_shape_  = NULL; // 每次单击，首先清空之前选中的对象
        //if(select_btn_clicked_){ // 如果选择按钮按下，需要判断是否选择对象，如果选择进行标记,选择图像进行旋转和移动
        //    int iSize = m_pSystemData->m_ShapeVec.size();
        //    for(int i =0;i<iSize;++i ){
        //        if(cur_select_shape_){ // 判断是否已经有了选中的图形
        //            break;
        //        }
        //        if(this->double_clicked_){ // 如果进行了双击，第二次不要操作，否则文字选中会有边框
        //            this->double_clicked_ = false;
        //            this->cur_select_shape_ = NULL;
        //            break;
        //        }
        //        //                qDebug()<<i;
        //        BaseShape * pShape= m_pSystemData->m_ShapeVec.at(i);
        //        if(pShape->HasSelected(clicked_point_)){ // 如果点击了当前的图形，进行赋值
        //            cur_select_shape_ = pShape;
        //            this->cur_selected_shape_index_ = i;
        //        }
        //    }
        //}

       /* if(this->m_DemensionBtnClicked == true && shape_type_ != EShapeType::Shape_Demensions ){
            this->m_DemensionBtnClicked = false;
            this->DemensionsPoint.clear();
        }*/
    }
    QOpenGLWidget::mousePressEvent(event);
}


void DrawWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    //if(event->button() == Qt::MouseButton::LeftButton){
    //    if(cur_select_shape_ && cur_select_shape_->GetShapeType() == EShapeType::kText){
    //        this->double_clicked_ = true; // 确定当前是双击，防止单击继续操作
    //        TextShape* text_shape = dynamic_cast<TextShape*>(cur_select_shape_); // 获取当前选中的文字框的信息
    //        text_point_ = QPoint(text_shape->GetStartPosX(), text_shape->GetStartPosY());
    //        content_edit_.show();
    //        cur_select_shape_ = NULL;
    //        update();
    //        //            qDebug()<<"update";
    //        content_edit_.setGeometry(text_point_.x()-3,text_point_.y()-22.5,200,30);
    //        content_edit_.setPlainText(text_shape->GetContent());
    //    }
    //}

    QOpenGLWidget::mouseDoubleClickEvent(event);
}

void DrawWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton){
        mouse_left_btn_clicked_ = false;
        move_point_ = event->pos();
        if(this->cur_selected_shape_index_ == -1){
            text_point_ = event->pos();
        }

        switch (shape_type_) {
        case EShapeType::kReckangle: {
            int min_x = clicked_point_.x() < move_point_.x()?clicked_point_.x():move_point_.x();
            int min_y = clicked_point_.y() < move_point_.y()?clicked_point_.y():move_point_.y();
            QPoint dis = move_point_ - clicked_point_;
            std::shared_ptr<RectangleShape> rect = std::make_shared<RectangleShape>(double(min_x), double(min_y), qAbs(double(dis.x())), qAbs(double(dis.y())));
            shapes_.emplace_back(rect);
            break;
        }
        case EShapeType::kEllipse: {
            int min_x = clicked_point_.x() < move_point_.x()?clicked_point_.x():move_point_.x();
            int min_y = clicked_point_.y() < move_point_.y()?clicked_point_.y():move_point_.y();
            QPoint dis = move_point_ - clicked_point_;
            std::shared_ptr<EllipseShape> elli = std::make_shared<EllipseShape>(double(min_x), double(min_y), qAbs(double(dis.x())), qAbs(double(dis.y())));
            shapes_.emplace_back(elli);
            break;
        }
        case EShapeType::kLine: {
            std::shared_ptr<LineShape> line = std::make_shared<LineShape>(double(clicked_point_.x()), double(clicked_point_.y()), double(move_point_.x()), double(move_point_.y()));   
            shapes_.emplace_back(line);
            break;
        }
        case EShapeType::kText: {  //to do 这里需要看下
            text_point_ = move_point_;
           /* content_edit_.clear();
            content_edit_.show();
            content_edit_.setGeometry(text_point_.x(), text_point_.y(), 200, 100);
            content_edit_.setFocus();*/

            text_edit_->show();
            text_edit_->move(text_point_);
            text_edit_->setFocus();


            break;
        }
        case EShapeType::kCustomLine: {
            if (points_data_.size() >= 10) {
                std::shared_ptr<CustomLineShape> cli = std::make_shared<CustomLineShape>();
                cli->points_data_ = points_data_;
                shapes_.emplace_back(cli);
                points_data_.clear();
                break;
            }
        }
        default:
            break;
        }
    }
    update();
    QOpenGLWidget::mouseReleaseEvent(event);
}

void DrawWidget::Revoke() {
    shapes_.pop_back();
    update();
}

// 本窗口鼠标移动事件
void DrawWidget::mouseMoveEvent(QMouseEvent *event)
{
    // 鼠标进行实时捕获，判断是否是在某个点的范围内
    QPoint point = event->pos();
   // this->mouseOnOnePoint(point);
    //if(this->m_CapturePoint){
    //    //        qDebug()<<"已经在点中了";
    //    this->setCursor(Qt::CrossCursor);
    //}else{
    //    this->setCursor(Qt::ArrowCursor);  //范围之外变回原来形状  https://blog.csdn.net/technologyleader/article/details/82981718
    //}
    //this->m_CapturePoint = nullptr;

    // ]


    for (auto& shape: shapes_) {
    
        //qDebug() << "EnterSelectRange :" <<  shape->EnterSelectRange(point);
    }



    // 移动选中的对象
    if(cur_select_shape_ && mouse_left_btn_clicked_){
        cur_select_shape_->MoveShape(move_point_, event->pos());
        update();
    }
    move_point_ = event->pos();

    if(mouse_left_btn_clicked_) {
        move_point_ = event->pos();
        update();

        if (EShapeType::kCustomLine == shape_type_) {
            points_data_.append(event->pos());
        }
    }

    QOpenGLWidget::mouseMoveEvent(event);
}


// 文本编辑事件
void DrawWidget::fn_Recv_ContentEdit_GetContent(const QString& content) {

    if (content.isEmpty()) {
        return;
    }

    //if (this->cur_selected_shape_index_ != -1) {
    //    TextData* pText = new TextData(double(text_point_.x()), double(text_point_.y()), qstrContent);
    //    m_pSystemData->m_ShapeVec[this->cur_selected_shape_index_] = pText;
    //    //            qDebug()<<"m_pSystemData->m_ShapeVec[this->cur_selected_shape_index_] = pText;";
    //}
    //else {
    //    //            qDebug()<<" m_pSystemData->m_ShapeVec.push_back(pText);";
    //    TextData* pText = new TextData(double(text_point_.x()) + 3, double(text_point_.y() + 22.5), qstrContent);
    //    //            m_pSystemData->m_ShapeVec.pop_back();
    //    m_pSystemData->m_ShapeVec.push_back(pText);
    //}

   // std::shared_ptr<TextShape> text_shape = std::make_shared<TextShape>(double(text_point_.x()) + 3, double(text_point_.y() + 22.5), content, this);
   // 
   // shapes_.emplace_back(text_shape);
   // 
   // qDebug() << "recv content";
   // 
   // if (content.indexOf("\n") != -1) //数据中有\n，插入\r; 怎么应对一个以上的换行?
   // {
   //     qDebug() << "content have \n";
   // }
   //
   //
   //
   // update();
   // this->cur_selected_shape_index_ = -1;
}


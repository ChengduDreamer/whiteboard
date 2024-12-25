#include "ellipse_shape.h"

EllipseShape::EllipseShape() {
    shape_type_ = EShapeType::kEllipse;
    start_pos_x_ = 0.0;
    start_pos_y_ = 0.0;
    radius_w_ = 0.0;
    radius_h_ = 0.0;
}

EllipseShape::EllipseShape(QPoint& click_point, QPoint& move_point) {
    int min_x = click_point.x() < move_point.x()?click_point.x():move_point.x();
    int min_y = click_point.y() < move_point.y()?click_point.y():move_point.y();
    QPoint dis = move_point - click_point;
    shape_type_ = EShapeType::kEllipse;
    start_pos_x_ = double(min_x);
    start_pos_y_ = double(min_y);
    radius_w_ = qAbs(double(dis.x()));
    radius_h_ = qAbs(double(dis.y()));
}
/*
* 接口说明： 公共接口，有参构造函数
* 参数说明： 【in】    start_pos_x 起点横坐标
*          【in】    start_pos_y 起点横坐标
*          【in】    radius_w 横向半径长度
*          【in】    radius_h 纵向半径长度
* 返回值说明： 无
*/
EllipseShape::EllipseShape(const double& start_pos_x, const double& start_pos_y, const double& radius_w, const double& radius_h) {
    shape_type_ = EShapeType::kEllipse;
    start_pos_x_ = start_pos_x;
    start_pos_y_ = start_pos_y;
    radius_w_ = radius_w;
    radius_h_ = radius_h;
}

EllipseShape::~EllipseShape() {

}

void EllipseShape::UpdateData(QPoint& click_point, QPoint& move_point) {

    //qDebug() << "EllipseShape move_point = " << move_point;

    int min_x = click_point.x() < move_point.x() ? click_point.x() : move_point.x();
    int min_y = click_point.y() < move_point.y() ? click_point.y() : move_point.y();
    QPoint dis = move_point - click_point;
    start_pos_x_ = double(min_x);
    start_pos_y_ = double(min_y);
    radius_w_ = qAbs(double(dis.x()));
    radius_h_ = qAbs(double(dis.y()));
}

//bool EllipseShape::HasSelected(const QPoint& pos)
//{
//    this->selected_ = false;
//    if((pos.x() >=this->GetStartPosX()) && (pos.x() <= this->GetStartPosX()+this->radius_w_) && (pos.y()>= this->GetStartPosY()) && (pos.y() <= this->GetStartPosY()+this->radius_h_) ){
//        this->selected_ = true;
//    }
//    return this->selected_ ;
//}

bool EllipseShape::HasSelected(const QPoint& pos)
{
    this->selected_ = false;
    if ((pos.x() >= this->GetStartPosX()) && (pos.x() <= this->GetStartPosX() + this->radius_w_) && (pos.y() >= this->GetStartPosY()) && (pos.y() <= this->GetStartPosY() + this->radius_h_)) {
        this->selected_ = true;
    }
    return this->selected_;

    // to do 判断一个点是否在椭圆内， 然后再判断 是否在另一个椭圆外，就可以判断出来，   矩形亦如此
}

bool EllipseShape::EnterSelectRange(const QPoint& point) {
    const int kRangeSize = 30;
    QRectF outside_rectf{ start_pos_x_ - kRangeSize, start_pos_y_ - kRangeSize,  radius_w_  + 2 * kRangeSize, radius_h_  + 2 * kRangeSize };
    if (!PointInEllipse(outside_rectf, point)) {
        return false;    
    }
    if (radius_w_ <= 2 * kRangeSize || radius_h_ <= 2 * kRangeSize) {
        return true;
    }
    QRectF inside_rectf{ start_pos_x_ + kRangeSize, start_pos_y_ + kRangeSize,  radius_w_ - 2 * kRangeSize, radius_h_ - 2 * kRangeSize };
    if (PointInEllipse(inside_rectf, point)) {
        return false;
    }
    return true;
}

bool EllipseShape::PointInEllipse(const QRectF& ellipse_rect, const QPointF& point) {
    // 获取椭圆的中心点
    double h = ellipse_rect.center().x();
    double k = ellipse_rect.center().y();

    // 计算水平半轴长度 (a) 和垂直半轴长度 (b)
    double a = ellipse_rect.width() / 2.0;
    double b = ellipse_rect.height() / 2.0;

    // 获取点的坐标
    double x = point.x();
    double y = point.y();

    // 椭圆方程计算
    double equation = std::pow(x - h, 2) / std::pow(a, 2) + std::pow(y - k, 2) / std::pow(b, 2);

    // 如果方程值 ≤ 1，点在椭圆内
    return equation <= 1.0;
}



void EllipseShape::DrawShape(QPainter &painter) {
    painter.drawEllipse(QRectF(this->GetStartPosX(),this->GetStartPosY(),this->GetRadiusW(),this->GetRediusH()));
}

void EllipseShape::MoveShape(const QPoint& cur_point, const QPoint& next_point) {
    QPoint dis = next_point - cur_point;
    this->SetStartPosX(this->start_pos_x_ + dis.x());
    this->SetStartPosY(this->start_pos_y_ + dis.y());
}

void EllipseShape::PaintFrame(QPainter &painter) {
    painter.save();
    QPen frame_pen(Qt::blue, 1 ,Qt::DashDotLine, Qt::RoundCap);
    painter.setPen(frame_pen);
    painter.drawRect(this->start_pos_x_-5,this->start_pos_y_-5,this->radius_w_+10,this->radius_h_+10);
    painter.restore();
}

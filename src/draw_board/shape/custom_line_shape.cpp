#include "custom_line_shape.h"

CustomLineShape::CustomLineShape()
{
    shape_type_ = EShapeType::kCustomLine;
    this->start_pos_x_ = 0.0;
    this->start_pos_y_ = 0.0;
    this->end_pos_x_ = 0.0;
    this->end_pos_y_ = 0.0;
}

CustomLineShape::~CustomLineShape() {

}

bool CustomLineShape::HasSelected(const QPoint& pos)
{
    //判断点是否在直线上
    //LineArgument LP = getLinePara(this->GetStartPosX(), this->GetStartPosY(), this->GetEndPosX(), this->GetEndPosY());
    //this->selected_ = false;
    //if (pos.x() > this->GetStartPosX() && pos.x() < this->GetEndPosX()) {
    //    if (((LP.A * pos.x() + LP.B * (pos.y() + 5) + LP.C < 0) && (LP.A * pos.x() + LP.B * (pos.y() - 5) + LP.C > 0)) || ((LP.A * pos.x() + LP.B * (pos.y() + 5) + LP.C > 0) && (LP.A * pos.x() + LP.B * (pos.y() - 5) + LP.C < 0))) {
    //        this->selected_ = true;
    //    }
    //}
    return this->selected_;
}

bool CustomLineShape::EnterSelectRange(const QPoint& point) {
    const double kThreshold = 30;
    int step_length = (int)( points_data_.size() * 1.0f / 10);
    if (step_length < 1) {
        step_length = 1;
    }
    int temp = 0;
    for (int i = 0; i < points_data_.size(); i = i + step_length) {
        double distance = PointToLineSegmentDistance(points_data_[temp], points_data_[i], point);
        if (distance <= kThreshold) {
            return true; // 如果点到任意一条线段的距离小于阈值，则认为在附近
        }
        temp = i;
    }
    return false;
}


void CustomLineShape::DrawShape(QPainter& painter)
{
    //painter.drawLine(this->GetStartPosX(), this->GetStartPosY(), this->GetEndPosX(), this->GetEndPosY());
    painter.save();
    //painter.translate(start_point_);
    painter.drawPolyline(points_data_);
    painter.restore();
}

// 更新数据
void CustomLineShape::MoveShape(const QPoint& curPoint, const QPoint& nextPoint) {


    start_point_ = nextPoint;
    
    QPoint dis = nextPoint - curPoint;

    for (auto& p : points_data_) {
        p += dis;
    }
    return;
    this->SetStartPosX(this->GetStartPosX() + dis.x());
    this->SetStartPosY(this->GetStartPosY() + dis.y());
    this->SetEndPosX(this->GetEndPosX() + dis.x());
    this->SetEndPosY(this->GetEndPosY() + dis.y());
    this->start_point_.setX(this->GetStartPosX());
    this->start_point_.setY(this->GetStartPosY());
    this->end_point_.setX(this->GetEndPosX());
    this->end_point_.setY(this->GetEndPosY());

    this->center_point_.setX((this->start_point_.x() + this->end_point_.x()) / 2);
    this->center_point_.setY((this->start_point_.y() + this->end_point_.y()) / 2);
}

void CustomLineShape::PaintFrame(QPainter& painter) {
   // painter.save(); // 保存画笔
   // QPen frame_pen(Qt::blue, 1, Qt::DashDotLine, Qt::RoundCap);
   // painter.setPen(frame_pen);
   // painter.drawLine(start_point_.x(), start_point_.y() + 5, start_point_.x(), start_point_.y() - 5);
   // painter.drawLine(start_point_.x(), start_point_.y() - 5, end_point_.x(), end_point_.y() - 5);
   // painter.drawLine(end_point_.x(), end_point_.y() - 5, end_point_.x(), end_point_.y() + 5);
   // painter.drawLine(end_point_.x(), end_point_.y() + 5, start_point_.x(), start_point_.y() + 5);
   // painter.restore(); // 恢复画笔
}

//void CustomLineShape::rotate(QPoint& BasePoint, double arg = 90)
//{
//    this->rotatePoint(BasePoint, this->start_point_, arg);
//    this->rotatePoint(BasePoint, this->end_point_, arg);
//    this->start_pos_x_ = this->start_point_.x();
//    this->start_pos_y_ = this->start_point_.y();
//    this->end_pos_x_ = this->end_point_.x();
//    this->end_pos_y_ = this->end_point_.y();
//}

#include "custom_line_shape.h"


std::shared_ptr<CustomLineShape> CustomLineShape::Make(const QVector<QPoint>& points_data) {
    return std::make_shared<CustomLineShape>(points_data);
}

CustomLineShape::CustomLineShape() {
    shape_type_ = EShapeType::kCustomLine;
    /*this->start_pos_x_ = 0.0;
    this->start_pos_y_ = 0.0;
    this->end_pos_x_ = 0.0;
    this->end_pos_y_ = 0.0;*/
}

CustomLineShape::CustomLineShape(const QVector<QPoint>& points_data) :points_data_(points_data) {

}

CustomLineShape::~CustomLineShape() {

}

//bool CustomLineShape::HasSelected(const QPoint& pos)
//{
//    //判断点是否在直线上
//    //LineArgument LP = getLinePara(this->GetStartPosX(), this->GetStartPosY(), this->GetEndPosX(), this->GetEndPosY());
//    //this->selected_ = false;
//    //if (pos.x() > this->GetStartPosX() && pos.x() < this->GetEndPosX()) {
//    //    if (((LP.A * pos.x() + LP.B * (pos.y() + 5) + LP.C < 0) && (LP.A * pos.x() + LP.B * (pos.y() - 5) + LP.C > 0)) || ((LP.A * pos.x() + LP.B * (pos.y() + 5) + LP.C > 0) && (LP.A * pos.x() + LP.B * (pos.y() - 5) + LP.C < 0))) {
//    //        this->selected_ = true;
//    //    }
//    //}
//    return this->selected_;
//}

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


void CustomLineShape::DrawShape(QPainter& painter) {
    painter.save();
    painter.drawPolyline(points_data_);
    painter.restore();
}

void CustomLineShape::MoveShape(const QPoint& curPoint, const QPoint& nextPoint) {
    if (points_data_.empty()) {
        return;
    }
    int min_x = points_data_[0].x();
    int min_y = points_data_[0].y();
    int max_x = min_x;
    int max_y = min_y;
    QPoint dif = nextPoint - curPoint;
    for (auto& p : points_data_) {
        p += dif;
        if (p.x() < min_x) {
            min_x = p.x();
        }
        if (p.x() > max_x) {
            max_x = p.x();
        }
        if (p.y() < min_y) {
            min_y = p.y();
        }
        if (p.y() > max_y) { 
            max_y = p.y(); 
        }
    }
    rectf_ = QRectF(min_x, min_y, max_x - min_x, max_y - min_y);
}

void CustomLineShape::PaintFrame(QPainter& painter) {
    painter.save();
    QPen frame_pen(Qt::blue, 1, Qt::DashDotLine, Qt::RoundCap);
    painter.setPen(frame_pen);
    painter.drawRect(rectf_);
    painter.restore();
}

void CustomLineShape::SetPointsData(const QVector<QPoint>& points_data) {
    points_data_ = points_data;
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

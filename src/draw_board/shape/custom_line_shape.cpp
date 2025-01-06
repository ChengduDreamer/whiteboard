#include "custom_line_shape.h"
#include "shape_const_def.h"

std::shared_ptr<CustomLineShape> CustomLineShape::Make(const QVector<QPoint>& points_data) {
    return std::make_shared<CustomLineShape>(points_data);
}

CustomLineShape::CustomLineShape() {
    shape_type_ = EShapeType::kCustomLine;
}

CustomLineShape::CustomLineShape(const QVector<QPoint>& points_data) :points_data_(points_data) {

}

CustomLineShape::~CustomLineShape() {

}

bool CustomLineShape::EnterSelectRange(const QPoint& point) {
    int step_length = (int)( points_data_.size() * 1.0f / 10);
    if (step_length < 1) {
        step_length = 1;
    }
    int temp = 0;
    for (int i = 0; i < points_data_.size(); i = i + step_length) {
        double distance = PointToLineSegmentDistance(points_data_[temp], points_data_[i], point);
        if (distance <= kShapeNearRangeSize) {
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
    rect_ = QRect(min_x - kShapeFrameMargin, min_y - kShapeFrameMargin, max_x - min_x + 2 * kShapeFrameMargin, max_y - min_y + 2 * kShapeFrameMargin);
}

void CustomLineShape::PaintFrame(QPainter& painter) {
    painter.save();
    SetFrameStyle(painter);
    painter.drawRect(rect_);
    painter.restore();
}

void CustomLineShape::SetPointsData(const QVector<QPoint>& points_data) {
    points_data_ = points_data;
}
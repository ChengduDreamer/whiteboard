#include "rectangle_shape.h"
#include "shape_const_def.h"

std::shared_ptr<RectangleShape> RectangleShape::Make(const double& pos_x, const double& pos_y, const double& width, const double& height) {
    return std::make_shared<RectangleShape>(pos_x, pos_y, width, height);
}

RectangleShape::RectangleShape() {
    shape_type_ = EShapeType::kReckangle;
    this->height_ = 0.0;
    this->width_ = 0.0;
}

RectangleShape::RectangleShape(const double &dPosX, const double &dPosY, const double &dWidth, const double& dHeight) {
    shape_type_ = EShapeType::kReckangle;
    start_point_.setX(dPosX);
    start_point_.setY(dPosY);
    height_ = dHeight;
    width_ = dWidth;
}

RectangleShape::~RectangleShape() {

}

void RectangleShape::UpdateData(const QPointF& click_point, const QPointF& move_point) {
    int min_x = click_point.x() < move_point.x() ? click_point.x() : move_point.x();
    int min_y = click_point.y() < move_point.y() ? click_point.y() : move_point.y();
    QPointF dif = move_point - click_point;
    start_point_.setX(min_x);
    start_point_.setY(min_y);
    width_ = qAbs(double(dif.x()));
    height_ = qAbs(double(dif.y()));
}

bool RectangleShape::EnterSelectRange(const QPoint& point) {
    QRectF outside_rectf{ start_point_.x() - kShapeNearRangeSize, start_point_.y() - kShapeNearRangeSize,  width_ + 2 * kShapeNearRangeSize, height_ + 2 * kShapeNearRangeSize };
    if (!PointInRectangle(outside_rectf, point)) {
        return false;
    }
    if (width_ <= 2 * kShapeNearRangeSize || height_ <= 2 * kShapeNearRangeSize) {
        return true;
    }
    QRectF inside_rectf{ start_point_.x() + kShapeNearRangeSize, start_point_.y() + kShapeNearRangeSize,  width_ - 2 * kShapeNearRangeSize, height_ - 2 * kShapeNearRangeSize };
    if (PointInRectangle(inside_rectf, point)) {
        return false;
    }
    return true;
}

bool RectangleShape::PointInRectangle(const QRectF& rect, const QPointF& point) {
    return rect.contains(point);
}

void RectangleShape::DrawShape(QPainter &painter)
{
    painter.drawRect(QRectF(start_point_.x(), start_point_.y(), width_, height_));
}

void RectangleShape::MoveShape(const QPoint &curPoint, const QPoint &nextPoint) {
    QPoint dif = nextPoint - curPoint;
    start_point_ = start_point_ + dif;
}

void RectangleShape::PaintFrame(QPainter &painter) {
    painter.save(); 
    SetFrameStyle(painter);
    painter.drawRect(start_point_.x() - kShapeFrameMargin, start_point_.y() - kShapeFrameMargin, width_ + 2 * kShapeFrameMargin, height_ + 2 * kShapeFrameMargin);
    painter.restore();
}

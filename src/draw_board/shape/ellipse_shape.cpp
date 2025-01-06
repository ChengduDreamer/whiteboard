#include "ellipse_shape.h"
#include "shape_const_def.h"

std::shared_ptr<EllipseShape> EllipseShape::Make(const double& start_pos_x, const double& start_pos_y, const double& w, const double& h) {
    return std::make_shared<EllipseShape>(start_pos_x, start_pos_y, w, h);
}

EllipseShape::EllipseShape() {
    shape_type_ = EShapeType::kEllipse;
    width_ = 0.0;
    height_ = 0.0;
}

EllipseShape::EllipseShape(const double& start_pos_x, const double& start_pos_y, const double& radius_w, const double& radius_h) {
    shape_type_ = EShapeType::kEllipse;
    width_ = radius_w;
    height_ = radius_h;

    start_point_.setX(start_pos_x);
    start_point_.setY(start_pos_y);
}

EllipseShape::~EllipseShape() {

}

void EllipseShape::UpdateData(QPoint& click_point, QPoint& move_point) {
    int min_x = click_point.x() < move_point.x() ? click_point.x() : move_point.x();
    int min_y = click_point.y() < move_point.y() ? click_point.y() : move_point.y();
    QPoint dif = move_point - click_point;
    start_point_.setX(min_x);
    start_point_.setY(min_y);
    width_ = qAbs(double(dif.x()));
    height_ = qAbs(double(dif.y()));
}

bool EllipseShape::EnterSelectRange(const QPoint& point) {
    QRectF outside_rectf{ start_point_.x() - kShapeNearRangeSize, start_point_.y() - kShapeNearRangeSize,  width_ + 2 * kShapeNearRangeSize, height_ + 2 * kShapeNearRangeSize };
    if (!PointInEllipse(outside_rectf, point)) {
        return false;
    }
    if (width_ <= 2 * kShapeNearRangeSize || height_ <= 2 * kShapeNearRangeSize) {
        return true;
    }
    QRectF inside_rectf{ start_point_.x() + kShapeNearRangeSize, start_point_.y() + kShapeNearRangeSize,  width_ - 2 * kShapeNearRangeSize, height_ - 2 * kShapeNearRangeSize };
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

void EllipseShape::DrawShape(QPainter& painter) {
    painter.drawEllipse(QRectF(start_point_.x(), start_point_.y(), width_, height_));
}

void EllipseShape::MoveShape(const QPoint& cur_point, const QPoint& next_point) {
    QPoint dif = next_point - cur_point;
    start_point_ = start_point_ + dif;
}

void EllipseShape::PaintFrame(QPainter& painter) {
    painter.save();
    SetFrameStyle(painter);
    painter.drawRect(start_point_.x() - kShapeFrameMargin, start_point_.y() - kShapeFrameMargin, width_ + 2 * kShapeFrameMargin, height_ + 2 * kShapeFrameMargin);
    painter.restore();
}
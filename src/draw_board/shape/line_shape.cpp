#include "line_shape.h"
#include <qline.h>
#include "shape_const_def.h"


std::shared_ptr<LineShape> LineShape::Make(const QPointF& click_point, const QPointF& move_point) {
    return std::make_shared<LineShape>(click_point, move_point);
}

LineShape::LineShape(const QPointF& click_point, const QPointF& move_point) {
    shape_type_ = EShapeType::kLine;
    start_point_ = click_point;
    end_point_ = move_point;
}

LineShape::~LineShape() {

}


bool LineShape::EnterSelectRange(const QPoint& point) {
    return IsPointNearLineSegment(start_point_, end_point_, point, kShapeNearRangeSize);
}

void LineShape::DrawShape(QPainter &painter) {
    painter.save();
    painter.drawLine(start_point_, end_point_);
    painter.restore();
}

// 更新数据
void LineShape::MoveShape(const QPoint &curPoint, const QPoint &nextPoint) {
    QPointF dif = nextPoint - curPoint;
    start_point_ = start_point_ + dif;
    end_point_ = end_point_ + dif;
}


void LineShape::PaintFrame(QPainter& painter) {
    // to do + kShapeFrameMargin + width
    painter.save(); 
    SetFrameStyle(painter);
    painter.drawLine(start_point_.x(), start_point_.y() + kShapeFrameMargin, start_point_.x(), start_point_.y() - kShapeFrameMargin);
    painter.drawLine(start_point_.x(), start_point_.y() - kShapeFrameMargin, end_point_.x(), end_point_.y() - kShapeFrameMargin);
    painter.drawLine(end_point_.x(), end_point_.y() - kShapeFrameMargin, end_point_.x(), end_point_.y() + kShapeFrameMargin);
    painter.drawLine(end_point_.x(), end_point_.y() + kShapeFrameMargin, start_point_.x(), start_point_.y() + kShapeFrameMargin);
    painter.restore();
}


// 获取直线参数  求直线的方程 y = kx +b
LineArgument LineShape::GetLinePara(const double& x1, const double& y1, const double& x2, const double& y2) {
    LineArgument LP;
    LP.A = y2 - y1;
    LP.B = x1 - x2;
    LP.C = x2 * y1 - x1 * y2;
    return LP;
}
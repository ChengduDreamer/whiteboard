#include "rectangle_shape.h"


std::shared_ptr<RectangleShape> RectangleShape::Make(const double& pos_x, const double& pos_y, const double& width, const double& height) {
    return std::make_shared<RectangleShape>(pos_x, pos_y, width, height);
}

RectangleShape::RectangleShape()
{
    shape_type_ = EShapeType::kReckangle;
   /* this->start_pos_x_ = 0.0;
    this->start_pos_y_ = 0.0;*/
    this->height_ = 0.0;
    this->width_ = 0.0;
}



//RectangleShape::RectangleShape(QPoint& click_point, QPoint& move_point)
//{
//    int min_x = click_point.x() < move_point.x()?click_point.x():move_point.x();
//    int min_y = click_point.y() < move_point.y()?click_point.y():move_point.y();
//    QPoint dis = move_point - click_point;
//
//    shape_type_ = EShapeType::kReckangle;
//    this->start_pos_x_ = double(min_x);
//    this->start_pos_y_ = double(min_y);
//    this->width_ = qAbs(double(dis.x()));
//    this->height_ = qAbs(double(dis.y()));
//
//}

RectangleShape::RectangleShape(const double &dPosX, const double &dPosY, const double &dWidth, const double& dHeight) {
    shape_type_ = EShapeType::kReckangle;
  /*  this->start_pos_x_ = dPosX;
    this->start_pos_y_ = dPosY;*/

    start_point_.setX(dPosX);

    start_point_.setY(dPosY);

    this->height_ = dHeight;
    this->width_ = dWidth;
}

RectangleShape::~RectangleShape()
{

}

void RectangleShape::UpdateData(const QPointF& click_point, const QPointF& move_point) {
    int min_x = click_point.x() < move_point.x() ? click_point.x() : move_point.x();
    int min_y = click_point.y() < move_point.y() ? click_point.y() : move_point.y();
    QPointF dif = move_point - click_point;
   /* this->start_pos_x_ = double(min_x);
    this->start_pos_y_ = double(min_y);*/

    start_point_.setX(min_x);
    start_point_.setY(min_y);

    width_ = qAbs(double(dif.x()));
    height_ = qAbs(double(dif.y()));
}

//bool RectangleShape::HasSelected(const QPoint &pos)
//{
//    this->selected_ = false;
//    if(pos.x() >=this->GetStartPosX() && pos.x() <= this->GetStartPosX()+this->width_ && pos.y()>= this->GetStartPosY() && pos.y() <= this->GetStartPosY()+this->height_ ){
//        this->selected_ = true;
//    }
//    return this->selected_;
//}

bool RectangleShape::EnterSelectRange(const QPoint& point) {
    const int kRangeSize = 30;
    QRectF outside_rectf{ start_point_.x() - kRangeSize, start_point_.y() - kRangeSize,  width_ + 2 * kRangeSize, height_ + 2 * kRangeSize };
    if (!PointInRectangle(outside_rectf, point)) {
        return false;
    }
    if (width_ <= 2 * kRangeSize || height_ <= 2 * kRangeSize) {
        return true;
    }
    QRectF inside_rectf{ start_point_.x() + kRangeSize, start_point_.y() + kRangeSize,  width_ - 2 * kRangeSize, height_ - 2 * kRangeSize };
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

void RectangleShape::MoveShape(const QPoint &curPoint, const QPoint &nextPoint)
{
    QPoint dif = nextPoint - curPoint;
  /*  this->SetStartPosX(this->start_pos_x_ + dis.x());
    this->SetStartPosY(this->start_pos_y_ + dis.y());*/

    start_point_ = start_point_ + dif;
}

void RectangleShape::PaintFrame(QPainter &painter) {
    painter.save(); // 保存画笔
    QPen frame_pen(Qt::blue, 1 ,Qt::DashDotLine, Qt::RoundCap);
    painter.setPen(frame_pen);
    painter.drawRect(start_point_.x() - 5, start_point_.y() - 5, width_ + 10, height_ + 10);
    painter.restore(); // 恢复画笔
}

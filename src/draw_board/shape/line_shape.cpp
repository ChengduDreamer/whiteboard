#include "line_shape.h"
#include <qline.h>
LineShape::LineShape() {
    shape_type_ = EShapeType::kLine;
    this->start_pos_x_ = 0.0;
    this->start_pos_y_ = 0.0;
    this->end_pos_x_ = 0.0;
    this->end_pos_y_ = 0.0;
}

LineShape::LineShape(QPoint &click_point, QPoint &move_point)
{
    shape_type_ = EShapeType::kLine;
    this->start_pos_x_ = double(click_point.x());
    this->start_pos_y_ = double(click_point.y());
    this->end_pos_x_ = double(move_point.x());
    this->end_pos_y_ = double(move_point.y());

    this->start_point_.setX(start_pos_x_);
    this->start_point_.setY(start_pos_y_);
    this->end_point_.setX(end_pos_x_);
    this->end_point_.setY(end_pos_y_);

    this->center_point_.setX((this->start_point_.x()+this->end_point_.x())/2);
    this->center_point_.setY((this->start_point_.y()+this->end_point_.y())/2);
}

LineShape::~LineShape()
{

}

LineShape::LineShape(const double &start_pos_x, const double &start_pos_y, const double &end_pos_x, const double& end_pos_y)
{
    shape_type_ = EShapeType::kLine;
    this->start_pos_x_ = start_pos_x;
    this->start_pos_y_ = start_pos_y;
    this->end_pos_x_ = end_pos_x;
    this->end_pos_y_ = end_pos_y;

    this->start_point_.setX(start_pos_x);
    this->start_point_.setY(start_pos_y);
    this->end_point_.setX(end_pos_x);
    this->end_point_.setY(end_pos_y);

    this->center_point_.setX((this->start_point_.x()+this->end_point_.x())/2);
    this->center_point_.setY((this->start_point_.y()+this->end_point_.y())/2);
}

//bool LineShape::HasSelected(const QPoint &pos)
//{
//    //判断点是否在直线上
//    LineArgument LP = GetLinePara(this->GetStartPosX(),this->GetStartPosY(),this->GetEndPosX(),this->GetEndPosY());
//    this->selected_ = false;
//    if(pos.x() > this->GetStartPosX() && pos.x() < this->GetEndPosX()){
//        if(((LP.A*pos.x()+LP.B*(pos.y() + 5)+LP.C < 0) && (LP.A*pos.x()+LP.B*(pos.y()-5)+LP.C > 0)) || ((LP.A*pos.x()+LP.B*(pos.y() + 5)+LP.C > 0) && (LP.A*pos.x()+LP.B*(pos.y()-5)+LP.C < 0))  ){
//            this->selected_ = true;
//        }
//    }
//    return this->selected_;
//}



bool LineShape::EnterSelectRange(const QPoint& point) {
    const double kThreshold = 30;
    QLineF line{this->start_pos_x_, this->start_pos_y_, this->end_pos_x_, this->end_pos_y_};

    QPointF start_point{ this->start_pos_x_, this->start_pos_y_ };

    QPointF end_point{ this->end_pos_x_, this->end_pos_y_ };

    return IsPointNearLineSegment(start_point, end_point, point, kThreshold);
}

void LineShape::DrawShape(QPainter &painter)
{
    painter.drawLine(this->GetStartPosX(),this->GetStartPosY(),this->GetEndPosX(),this->GetEndPosY());
}

// 更新数据
void LineShape::MoveShape(const QPoint &curPoint, const QPoint &nextPoint)
{
    QPoint dis = nextPoint - curPoint;
    this->SetStartPosX(this->GetStartPosX()+dis.x());
    this->SetStartPosY(this->GetStartPosY()+dis.y());
    this->SetEndPosX(this->GetEndPosX()+dis.x());
    this->SetEndPosY(this->GetEndPosY()+dis.y());
    this->start_point_.setX(this->GetStartPosX());
    this->start_point_.setY(this->GetStartPosY());
    this->end_point_.setX(this->GetEndPosX());
    this->end_point_.setY(this->GetEndPosY());

    this->center_point_.setX((this->start_point_.x()+this->end_point_.x())/2);
    this->center_point_.setY((this->start_point_.y()+this->end_point_.y())/2);
}


void LineShape::PaintFrame(QPainter& painter)
{
    painter.save(); // 保存画笔
    QPen frame_pen(Qt::blue, 1 ,Qt::DashDotLine, Qt::RoundCap);
    painter.setPen(frame_pen);
    painter.drawLine(start_point_.x(), start_point_.y()+5, start_point_.x(), start_point_.y()-5);
    painter.drawLine(start_point_.x(), start_point_.y()-5, end_point_.x(), end_point_.y()-5);
    painter.drawLine(end_point_.x(), end_point_.y()-5, end_point_.x(), end_point_.y()+5);
    painter.drawLine(end_point_.x(), end_point_.y()+5, start_point_.x(), start_point_.y()+5);

    painter.restore(); // 恢复画笔
}

//void LineShape::rotate(QPoint &BasePoint, double arg = 90)
//{
//    this->rotatePoint(BasePoint,this->start_point_,arg);
//    this->rotatePoint(BasePoint,this->end_point_,arg);
//    this->start_pos_x_ = this->start_point_.x();
//    this->start_pos_y_ = this->start_point_.y();
//    this->end_pos_x_ = this->end_point_.x();
//    this->end_pos_y_ = this->end_point_.y();
//}

//已知直线上的两点P1(X1,Y1) P2(X2,Y2)， P1 P2两点不重合。则直线的一般式方程AX+BY+C=0中，A B C分别等于：
//struct LineArgument{
//    double A; // A = Y2 - Y1
//    double B; // B = X1 - X2
//    double C; // C = X2*Y1 - X1*Y2
//};
// 获取直线参数  求直线的方程 y = kx +b
LineArgument LineShape::GetLinePara(const double& x1, const double& y1, const double& x2, const double& y2)
{
    LineArgument LP;
    LP.A = y2 - y1;
    LP.B = x1 - x2;
    LP.C = x2 * y1 - x1 * y2;
    return LP;
}
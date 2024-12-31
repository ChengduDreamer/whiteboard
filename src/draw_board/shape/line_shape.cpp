#include "line_shape.h"
#include <qline.h>


std::shared_ptr<LineShape> LineShape::Make(const QPointF& click_point, const QPointF& move_point) {
    return std::make_shared<LineShape>(click_point, move_point);
}

LineShape::LineShape(const QPointF& click_point, const QPointF& move_point) {
    shape_type_ = EShapeType::kLine;

   /* this->start_pos_x_ = double(click_point.x());
    this->start_pos_y_ = double(click_point.y());
    this->end_pos_x_ = double(move_point.x());
    this->end_pos_y_ = double(move_point.y());

    this->start_point_.setX(start_pos_x_);
    this->start_point_.setY(start_pos_y_);
    this->end_point_.setX(end_pos_x_);
    this->end_point_.setY(end_pos_y_);*/


    start_point_ = click_point;

    end_point_ = move_point;



    /*this->center_point_.setX((this->start_point_.x()+this->end_point_.x())/2);
    this->center_point_.setY((this->start_point_.y()+this->end_point_.y())/2);*/
}

LineShape::~LineShape()
{

}

//LineShape::LineShape(const double &start_pos_x, const double &start_pos_y, const double &end_pos_x, const double& end_pos_y)
//{
//    shape_type_ = EShapeType::kLine;
//    this->start_pos_x_ = start_pos_x;
//    this->start_pos_y_ = start_pos_y;
//    this->end_pos_x_ = end_pos_x;
//    this->end_pos_y_ = end_pos_y;
//
//    this->start_point_.setX(start_pos_x);
//    this->start_point_.setY(start_pos_y);
//    this->end_point_.setX(end_pos_x);
//    this->end_point_.setY(end_pos_y);
//
//    this->center_point_.setX((this->start_point_.x()+this->end_point_.x())/2);
//    this->center_point_.setY((this->start_point_.y()+this->end_point_.y())/2);
//}

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
   /* QLineF line{ start_point_.x(), start_point_.y(), end_point_.x(), end_point_.y()};

    QPointF start_point{ this->start_pos_x_, this->start_pos_y_ };

    QPointF end_point{ this->end_pos_x_, this->end_pos_y_ };*/

    return IsPointNearLineSegment(start_point_, end_point_, point, kThreshold);
}

void LineShape::DrawShape(QPainter &painter)
{
    painter.save();
    painter.drawLine(start_point_, end_point_);
    painter.restore();
}

// 更新数据
void LineShape::MoveShape(const QPoint &curPoint, const QPoint &nextPoint)
{
    QPointF dif = nextPoint - curPoint;
    /*this->SetStartPosX(this->GetStartPosX()+dis.x());
    this->SetStartPosY(this->GetStartPosY()+dis.y());
    this->SetEndPosX(this->GetEndPosX()+dis.x());
    this->SetEndPosY(this->GetEndPosY()+dis.y());
    this->start_point_.setX(this->GetStartPosX());
    this->start_point_.setY(this->GetStartPosY());
    this->end_point_.setX(this->GetEndPosX());
    this->end_point_.setY(this->GetEndPosY());*/

    start_point_ = start_point_ + dif;

    end_point_ = end_point_ + dif;

  
   // center_point_ = (start_point_ + end_point_) / 2;

  /*  this->center_point_.setX((this->start_point_.x()+this->end_point_.x())/2);
    this->center_point_.setY((this->start_point_.y()+this->end_point_.y())/2);*/
}


void LineShape::PaintFrame(QPainter& painter) {
    painter.save(); 
    QPen frame_pen(Qt::blue, 1 ,Qt::DashDotLine, Qt::RoundCap);
    painter.setPen(frame_pen);
    painter.drawLine(start_point_.x(), start_point_.y()+5, start_point_.x(), start_point_.y()-5);
    painter.drawLine(start_point_.x(), start_point_.y()-5, end_point_.x(), end_point_.y()-5);
    painter.drawLine(end_point_.x(), end_point_.y()-5, end_point_.x(), end_point_.y()+5);
    painter.drawLine(end_point_.x(), end_point_.y()+5, start_point_.x(), start_point_.y()+5);
    painter.restore();
}


// 获取直线参数  求直线的方程 y = kx +b
LineArgument LineShape::GetLinePara(const double& x1, const double& y1, const double& x2, const double& y2)
{
    LineArgument LP;
    LP.A = y2 - y1;
    LP.B = x1 - x2;
    LP.C = x2 * y1 - x1 * y2;
    return LP;
}
#pragma once
#include <QPainter>
#include <QPainterPath>
#include <cmath>
#include <QDebug>
#include <QPoint>

enum class EShapeType {
    kUnkonwn,     // 未知形状
    kReckangle,   // 矩形
    kEllipse,     // 椭圆
    kLine,        // 线条
    kText,        // 文本
    kCustomLine,  //画笔画线
};


class BaseShape
{
public:
    BaseShape();
    virtual ~BaseShape();

    void SetShapeType(const EShapeType& shapetype) { 
        shape_type_= shapetype;
    }

    EShapeType GetShapeType() const {
        return shape_type_;
    }

    void SetStartPoint(const QPointF& start_point) {
        start_point_ = start_point;
    }

    void SetEndPoint(const QPointF& end_point) {
        end_point_ = end_point;
    }

    QPointF GetStartPoint() const {
        return start_point_;
    }

    QPointF GetEndPoint() const {
        return end_point_;
    }

    // 判断是否进入选择区域范围
    virtual bool EnterSelectRange(const QPoint& point) {
        return false;
    }
    
    void SetFrameStyle(QPainter&);

    // 画图函数
    virtual void DrawShape(QPainter&){}

    // 移动图形
    virtual void MoveShape(const QPoint&,const QPoint&){}

    // 画边框
    virtual void PaintFrame(QPainter&) {} 

     // 计算两点之间的欧几里得距离
    double DistanceBetweenPoints(const QPointF& p1, const QPointF& p2);

    // 计算点到线段的最短距离
    double PointToLineSegmentDistance(const QPointF& start, const QPointF& end, const QPointF& point);

    bool IsPointNearLineSegment(const QPointF& start, const QPointF& end, const QPointF& point, double threshold);
public:
    QPointF start_point_;   //起始点
    QPointF end_point_;     //最新点
protected:
    EShapeType shape_type_ = EShapeType::kUnkonwn;

};


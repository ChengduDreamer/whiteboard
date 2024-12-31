#pragma once
#include "base_shape.h"
#include <QPolygonF>
#include <QVector>
#include <QPainterPath>
#include <QDebug>
#include <QTransform>
#include <QPoint>

//已知直线上的两点P1(X1,Y1) P2(X2,Y2)， P1 P2两点不重合。则直线的一般式方程AX+BY+C=0中，A B C分别等于：
struct LineArgument {
    double A; // A = Y2 - Y1
    double B; // B = X1 - X2
    double C; // C = X2*Y1 - X1*Y2
};

class LineShape : public BaseShape
{
public:
    static std::shared_ptr<LineShape> Make(const QPointF& click_point, const QPointF& move_point);
    LineShape(const QPointF& click_point, const QPointF& move_point);
    ~LineShape();
    void DrawShape(QPainter &painter) override;
    void MoveShape(const QPoint &p1,const QPoint &p2) override;
    void PaintFrame(QPainter& p) override;

    bool EnterSelectRange(const QPoint& point) override;
    LineArgument GetLinePara(const double& x1, const double& y1, const double& x2, const double& y2);
};


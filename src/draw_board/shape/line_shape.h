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
    LineShape();
    LineShape(QPoint &click_point, QPoint &move_point);
    ~LineShape();
    LineShape(const double& start_pos_x, const double& start_pos_y, const double& end_pos_x, const double& end_pos_y);

    inline void SetStartPosX(const double& pos_x) {
        start_pos_x_ = pos_x;
    }

    inline void SetStartPosY(const double& pos_y) {
        start_pos_y_ = pos_y;
    }

    inline void SetEndPosX(const double &dWidth) {
        end_pos_x_ = dWidth;
    }

    inline void SetEndPosY(const double &dHeight) {
        end_pos_y_ = dHeight;
    }

    inline const double &GetStartPosX() const {
        return start_pos_x_;
    }

    inline const double &GetStartPosY() const {
        return start_pos_y_;
    }

    inline const double &GetEndPosX() const {
        return end_pos_x_;
    }

    inline const double &GetEndPosY() const {
        return end_pos_y_;
    }

    bool HasSelected(const QPoint &pos) override;
    void DrawShape(QPainter &painter) override;
    void MoveShape(const QPoint &p1,const QPoint &p2) override;
    void PaintFrame(QPainter& p) override;

    //void rotate(QPoint &BasePoint,double arg) override;


    bool EnterSelectRange(const QPoint& point) override;

    LineArgument GetLinePara(const double& x1, const double& y1, const double& x2, const double& y2);


   

private:
    double start_pos_x_ = 0;          // 起点横坐标
    double start_pos_y_ = 0;          // 起点纵坐标&
    double end_pos_x_ = 0;            // 终点横坐标
    double end_pos_y_ = 0;            // 终点纵坐标
    //QVector<QPoint> vectorPath;   // 路径容器
    bool selected_ = false;;          // 是否选中
};


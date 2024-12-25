#pragma once
#include "base_shape.h"
#include <QDebug>

class EllipseShape : public BaseShape
{
public:
    EllipseShape();
    EllipseShape(QPoint& click_point, QPoint& move_point);
    EllipseShape(const double& start_pos_x, const double& start_pos_y, const double& radius_w, const double& radius_h);
    ~EllipseShape();

    void UpdateData(QPoint& click_point, QPoint& move_point);

    inline void SetStartPosX(const double& start_pos_x) {
        start_pos_x_ = start_pos_x;
    }

    inline void SetStartPosY(const double &start_pos_y) {
        start_pos_y_ = start_pos_y;
    }

    inline void SetRadiusW(const double &radius_w) {
        radius_w_ = radius_w;
    }

    inline void SetRediusH(const double &radius_h) {
        radius_h_ = radius_h;
    }

    inline const double GetStartPosX() const { 
        return start_pos_x_;
    }

    inline const double GetStartPosY() const { 
        return start_pos_y_;
    }

    inline const double GetRadiusW() const { 
        return radius_w_;
    }

    inline const double GetRediusH() const { 
        return radius_h_;
    }

    bool HasSelected(const QPoint &pos) override; 
    void DrawShape(QPainter &painter) override;
    void MoveShape(const QPoint &curPoint, const QPoint &nextPoint) override;
    void PaintFrame(QPainter& painter) override;

    bool EnterSelectRange(const QPoint& point) override;

    bool PointInEllipse(const QRectF& ellipse_rect, const QPointF& point);

private:
    double start_pos_x_ = 0; // 起点横坐标
    double start_pos_y_ = 0; // 起点纵坐标
    double radius_w_ = 0;    // 横向半径长度
    double radius_h_ = 0;    // 纵向半径长度
    bool selected_ = false;
};


#pragma once
#include "base_shape.h"
#include <QDebug>

class EllipseShape : public BaseShape {
public:
    static std::shared_ptr<EllipseShape> Make(const double& start_pos_x, const double& start_pos_y, const double& w, const double& h);
    EllipseShape();
    EllipseShape(const double& start_pos_x, const double& start_pos_y, const double& w, const double& h);
    ~EllipseShape();

    void UpdateData(QPoint& click_point, QPoint& move_point);
    void DrawShape(QPainter &painter) override;
    void MoveShape(const QPoint &curPoint, const QPoint &nextPoint) override;
    void PaintFrame(QPainter& painter) override;

    bool EnterSelectRange(const QPoint& point) override;
    bool PointInEllipse(const QRectF& ellipse_rect, const QPointF& point);
private:
    double width_ = 0;
    double height_ = 0;
};


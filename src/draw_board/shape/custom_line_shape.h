#pragma once
#include "base_shape.h"
#include <QPolygonF>
#include <QVector>
#include <QPainterPath>
#include <QDebug>
#include <QTransform>
#include <QPoint>
#include <vector>

class CustomLineShape : public BaseShape
{
public:
    static std::shared_ptr<CustomLineShape> Make(const QVector<QPoint>& points_data);
    CustomLineShape();
    CustomLineShape(const QVector<QPoint>& points_data);
    ~CustomLineShape();

    void DrawShape(QPainter& painter) override;
    void MoveShape(const QPoint& p1, const QPoint& p2) override;
    void PaintFrame(QPainter& p) override;
    bool EnterSelectRange(const QPoint& point) override;
    void SetPointsData(const QVector<QPoint>& points_data);
private:
    // 存储画笔画的点
    QVector<QPoint> points_data_;

    // 所有点的外接矩形
    QRect rect_;  
};
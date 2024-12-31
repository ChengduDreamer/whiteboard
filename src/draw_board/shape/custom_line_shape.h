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

    //inline void SetStartPosX(const double& pos_x) { 
    //    start_pos_x_ = pos_x; 
    //}
    //
    //inline void SetStartPosY(const double& pos_y) { 
    //    start_pos_y_ = pos_y; 
    //}
    //
    //inline void SetEndPosX(const double& width) { 
    //    end_pos_x_ = width; 
    //}
    //
    //inline void SetEndPosY(const double& height) { 
    //    end_pos_y_ = height; 
    //}
    //
    //inline const double& GetStartPosX() const { 
    //    return start_pos_x_; 
    //}
    //
    //inline const double& GetStartPosY() const { 
    //    return start_pos_y_; 
    //}
    //
    //inline const double& GetEndPosX() const {
    //    return end_pos_x_; 
    //}
    //
    //inline const double& GetEndPosY() const { 
    //    return end_pos_y_; 
    //}

    //bool HasSelected(const QPoint& pos) override; 
    void DrawShape(QPainter& painter) override;
    void MoveShape(const QPoint& p1, const QPoint& p2) override;
    void PaintFrame(QPainter& p) override;
    //void rotate(QPoint& BasePoint, double arg) override;


    bool EnterSelectRange(const QPoint& point) override;

    
    void SetPointsData(const QVector<QPoint>& points_data);

private:
    // 存储画笔画的点
    QVector<QPoint> points_data_;
    QRectF rectf_;  // 所有点的外接矩形
   /* QPoint start_point_;*/

    //double start_pos_x_ = 0;   // 起点横坐标
    //double start_pos_y_ = 0;   // 起点纵坐标&
    //double end_pos_x_ = 0;     // 终点横坐标
    //double end_pos_y_ = 0;     // 终点纵坐标
    //QVector<QPoint> vectorPath;// 路径容器
    //bool selected_ = false;    // 是否选中
};
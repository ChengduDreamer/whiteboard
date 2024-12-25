#include "base_shape.h"

BaseShape::BaseShape()
{
    shape_type_ = EShapeType::kUnkonwn;
}

//void BaseShape::rotatePoint(QPoint &BasePoint,QPoint &point, double arg = 0.0)
//{
//    double sina = sin(arg*PI);
//    double cosa = cos(arg*PI);
//    int px = point.x();
//    int py = point.y();
//    point.setX( BasePoint.x()+(px-BasePoint.x())*cosa-(py-BasePoint.y())*sina + 0.5);
//    point.setY( BasePoint.y()+(px-BasePoint.x())*sina+(py-BasePoint.y())*cosa + 0.5);
//}
//
//void BaseShape::rotate(QPoint &BasePoint, double arg = 0.0)
//{
//    qDebug()<<"rotate BaseShape";
//}

BaseShape::~BaseShape()
{

}

// 计算两点之间的欧几里得距离
double BaseShape::DistanceBetweenPoints(const QPointF& p1, const QPointF& p2) {
    return std::sqrt(std::pow(p2.x() - p1.x(), 2) + std::pow(p2.y() - p1.y(), 2));
}

// 计算点到线段的最短距离
double BaseShape::PointToLineSegmentDistance(const QPointF& start, const QPointF& end, const QPointF& point) {
    // 线段长度的平方
    double lineLengthSquared = std::pow(end.x() - start.x(), 2) + std::pow(end.y() - start.y(), 2);

    // 如果线段是一个点（长度为0）
    if (lineLengthSquared == 0.0) {
        return DistanceBetweenPoints(start, point);
    }

    // 计算点到线段的投影比例 t
    double t = ((point.x() - start.x()) * (end.x() - start.x()) +
        (point.y() - start.y()) * (end.y() - start.y())) / lineLengthSquared;

    // 限制 t 的范围在 [0, 1] 之间
    t = std::max(0.0, std::min(1.0, t));

    // 计算投影点的坐标
    QPointF projection(start.x() + t * (end.x() - start.x()),
        start.y() + t * (end.y() - start.y()));

    // 返回点到投影点的距离
    return DistanceBetweenPoints(point, projection);
}

bool BaseShape::IsPointNearLineSegment(const QPointF& start, const QPointF& end, const QPointF& point, double threshold) {
    double distance = PointToLineSegmentDistance(start, end, point);
    return distance <= threshold;
}


//已知直线上的两点P1(X1,Y1) P2(X2,Y2)， P1 P2两点不重合。则直线的一般式方程AX+BY+C=0中，A B C分别等于：
//struct LineArgument{
//    double A; // A = Y2 - Y1
//    double B; // B = X1 - X2
//    double C; // C = X2*Y1 - X1*Y2
//};
// 获取直线参数  求直线的方程 y = kx +b
//LineArgument getLinePara(const double& x1,const double& y1,const double& x2,const double& y2)
//{
//    LineArgument LP;
//    LP.A = y2 - y1;
//    LP.B = x1 - x2;
//    LP.C = x2*y1 - x1*y2;
//    return LP;
//}

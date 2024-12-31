#include "base_shape.h"
#include <QPoint>

class RectangleShape : public BaseShape
{
public:
    static std::shared_ptr<RectangleShape> Make(const double& pos_x, const double& pos_y, const double& width, const double& height);
    RectangleShape();
    RectangleShape(const double& pos_x, const double& pos_y, const double& width, const double& height);
    ~RectangleShape();

    void UpdateData(const QPointF& click_point, const QPointF& move_point);
    void DrawShape(QPainter &painter) override;
    void MoveShape(const QPoint &p1,const QPoint &p2) override;
    void PaintFrame(QPainter& p) override; 
    bool EnterSelectRange(const QPoint& point) override;
    bool PointInRectangle(const QRectF& rect, const QPointF& point);
private:  
    double width_ = 0;
    double height_ = 0;
};



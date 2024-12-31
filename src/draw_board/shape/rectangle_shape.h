#include "base_shape.h"
#include <QPoint>

class RectangleShape : public BaseShape
{
public:
    static std::shared_ptr<RectangleShape> Make(const double& pos_x, const double& pos_y, const double& width, const double& height);

    RectangleShape();
    //RectangleShape(QPoint& click_point, QPoint& move_point);
    RectangleShape(const double& pos_x, const double& pos_y, const double& width, const double& height);
    ~RectangleShape();

    void UpdateData(const QPointF& click_point, const QPointF& move_point);

   /* inline void SetStartPosX(const double& pos_x) {
        start_pos_x_ = pos_x;
    }

    inline void SetStartPosY(const double& pos_y) {
        start_pos_y_ = pos_y;
    }

    inline void SetWidth(const double& width) {
        width_ = width;
    }

    inline void SetHeight(const double& height) {
        height_ = height;
    }

    inline const double &GetStartPosX() const {
        return start_pos_x_;
    }

    inline const double &GetStartPosY() const {
        return start_pos_y_;
    }

    inline const double &GetWidth() const {
        return width_;
    }

    inline const double &GetHeight() const {
        return height_;
    }*/

    // 判断选中的点是否在矩形上
  //  bool HasSelected(const QPoint &pos) override; 
    void DrawShape(QPainter &painter) override;
    void MoveShape(const QPoint &p1,const QPoint &p2) override;
    // 画边框
    void PaintFrame(QPainter& p) override; 

    bool EnterSelectRange(const QPoint& point) override;

    bool PointInRectangle(const QRectF& rect, const QPointF& point);

private:
  /*  double start_pos_x_ = 0;
    double start_pos_y_ = 0;*/
    double width_ = 0;
    double height_ = 0;
    //bool selected_ = false;       // 是否选中

};



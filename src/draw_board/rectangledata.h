#ifndef RECTANGLEDATA_H
#define RECTANGLEDATA_H
#include "shape/shapedata.h"

class RectangleData:public ShapeData
{
public:
    RectangleData();
    RectangleData(QPoint &clickPoint, QPoint &movePoint);
    RectangleData(const double &dPosX,const double &dPosY,const double &dWidth,const double dHeight);

    inline void SetStartPosX(const double &dPosX) {m_dStartPosX = dPosX;}
    inline void SetStartPosY(const double &dPosY) {m_dStartPosY = dPosY;}
    inline void SetWidth(const double &dWidth) {m_dWidth = dWidth;}
    inline void SetHeight(const double &dHeight) {m_dHeight = dHeight;}
    inline const double &GetStartPosX() const {return m_dStartPosX;}
    inline const double &GetStartPosY() const {return m_dStartPosY;}
    inline const double &GetWidth() const {return m_dWidth;}
    inline const double &GetHeight() const {return m_dHeight;}
    ~RectangleData();

    bool hasSelected(const QPoint &pos) override;
private:
    double m_dStartPosX;
    double m_dStartPosY;
    double m_dWidth;
    double m_dHeight;

};

#endif // RECTANGLEDATA_H

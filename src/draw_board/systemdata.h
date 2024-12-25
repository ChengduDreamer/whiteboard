#ifndef SYSTEMDATA_H
#define SYSTEMDATA_H

#include "MACRO.h"
#include <QVector>
#include "shape/shapedata.h"
#include "rectangledata.h"
#include "DrawWidget.h"
#include "shape/ellipsedata.h"
//#include "shape/triangeledata.h"
#include "shape/linedata.h"
#include "shape/textdata.h"
//#include "shape/erasuredata.h"
#include "shape/contentedit.h"
//#include "shape/demensionsdata.h"
#include <QSharedPointer>
#include <QMultiHash>
#include <QPoint>
#include <QPoint>

static uint qHash(const QPoint& key, uint seed) { //必须实现，此时会报错说没有声明QPoint的Key类型，https://www.cnblogs.com/qianqiannian/p/9585741.html
    int val = static_cast<int>(key.x());
    return qHash<int>(val, seed);
}

class DrawWidget;      // 声明绘画窗口
class CDrawBoardWidget;//主窗体

class SystemData
{
    friend class DrawWidget;
    friend class CDrawBoardWidget;// 友元没有传递性，所有必须要加上

public:
    static SystemData * GetSystemData();
    /*ShapeData * CreateShapeItem(EShapeType &type, QPoint &clickedPoint,QPoint &movePoint,QVector<QPoint> &Vec,ContentEdit &contentEdit,QVector<QPoint> &DemensionsVec);*/
    ShapeData* CreateShapeItem(EShapeType& type, QPoint& clickedPoint, QPoint& movePoint, QVector<QPoint>& Vec, ContentEdit& contentEdit);

    //inline void SetShapePointMap(const QPoint &point) {this->m_ShapePointMap.insert(point,this->m_ShapeVec.size()-1);}
    //inline void RemoveShapePointMap(const int &objIndex) {
    //    //        https://www.cnblogs.com/sky20080101/articles/8875861.html
    //    foreach(const QPoint &point ,m_ShapePointMap.keys()){
    //        if(m_ShapePointMap.value(point) == objIndex){
    //            m_ShapePointMap.remove(point);
    //        }
    //    }
    //}
private:
    SystemData();
    ~SystemData();

private:
    static SystemData g_SystemData; //类的静态成员
    QVector<ShapeData *> m_ShapeVec; // 图形对象地址容器
    //QMultiHash<QPoint,int> m_ShapePointMap;// 存储对象的顶点和对象
};

#endif // SYSTEMDATA_H

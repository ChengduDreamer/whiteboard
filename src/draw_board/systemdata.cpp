#include "systemdata.h"

SystemData SystemData::g_SystemData;

SystemData *SystemData::GetSystemData()
{
    return &g_SystemData;
}

ShapeData * SystemData::CreateShapeItem(EShapeType &type, QPoint &clickedPoint,QPoint &movePoint,QVector<QPoint> &Vec,ContentEdit &contentEdit){
    ShapeData * temp = new ShapeData;
    switch (type) {
    case EShapeType::kReckangle:
    {
        temp =new RectangleData(clickedPoint,movePoint);
        break;
    }
    case EShapeType::kEllipse:
    {
        temp =new EllipseData(clickedPoint,movePoint);
        break;
    }
    case EShapeType::kLine:
    {
        temp =new LineData(clickedPoint,movePoint);
        break;
    }
    case EShapeType::kText:
    {
        temp =new TextData(clickedPoint,contentEdit);
        break;
    }
   /* case EShapeType::Shape_Demensions:
    {
        if(DemensionsVec.size() == 3){
            temp = new DemensionsData(DemensionsVec);
        }
        break;
    }*/
    default:
        break;
    }
    //    QSharedPointer<ShapeData> item(temp);
    //    delete temp;
    //    return item;// 不想出现警告可以使用智能指针来替代，这样就比较安全，不会出现内存泄露
    return temp;
}

//class Singleton
//{
//private:
//    static Singleton* instance;
//    Singleton(){
//    }
//public:
//    static Singleton* GetInstace()
//    {
//        if (NULL == instance)
//        {
//            instance = new Singleton();
//        }
//        return instance;
//    }
//};

SystemData::SystemData()
{

}

SystemData::~SystemData()
{

    qDeleteAll(m_ShapeVec);
    m_ShapeVec.clear();
    m_ShapeVec.shrink_to_fit();
}

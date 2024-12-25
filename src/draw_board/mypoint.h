#ifndef MYPOINT_H
#define MYPOINT_H

#include <QPoint>

class MyPoint:public QPoint
{
public:
    MyPoint();
    ~MyPoint();
    inline bool operator<(const MyPoint &mypoint){
        if(this->x() != mypoint.x()){
            return this->x() < mypoint.x();
        }
        return this->y() < mypoint.y();
    }
};

#endif // MYPOINT_H

//https://blog.csdn.net/Rejective/article/details/108797525
//    inline bool operator<(const Employee &e1, const Employee &e2)
//    {
//        if (e1.name() != e2.name())
//            return e1.name() < e2.name();
//        return e1.dateOfBirth() < e2.dateOfBirth();
//    }

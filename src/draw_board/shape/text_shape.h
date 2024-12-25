#pragma once
#include <QString>
#include <QDebug>
#include <QFont>
#include <QObject>
#include <qtextdocument.h>
#include "base_shape.h"
#include "content_edit.h"

class TextShape : public BaseShape
{
public:
    TextShape(const double& start_pos_x, const double& start_pos_y, const QString& content, QWidget* parent);
    ~TextShape();

   /* inline void SetStartPosX(const double& pos_x) {
        start_pos_x_ = pos_x;
    }

    inline void SetStartPosY(const double& pos_y) {
        start_pos_y_ = pos_y;
    }

    inline const double GetStartPosX() const {
        return start_pos_x_;
    }

    inline const double GetStartPosY() const {
        return start_pos_y_;
    }*/
    

    bool HasSelected(const QPoint &pos) override; 
    void DrawShape(QPainter &painter) override;
    void MoveShape(const QPoint &curPoint, const QPoint &nextPoint) override;
    void PaintFrame(QPainter& painter) override;

    bool EnterSelectRange(const QPoint& point) override;

    bool PointInRectangle(const QRectF& rect, const QPointF& point);

    QString GetHtml();

    void SetHiden(bool hiden);

    void SetHtml(const QString& html);

    QString html_content_;

    QTextDocument text_document_;

private:
  

    bool selected_ = false;

    QWidget* parent_ = nullptr;

    QRectF rectf_;

    bool hiden_ = false;
};


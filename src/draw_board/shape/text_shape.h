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
    TextShape();
    TextShape(QPoint& click_point, ContentEdit& content_edit);
    TextShape(const double& start_pos_x, const double& start_pos_y, const QString& content, QWidget* parent);
    ~TextShape();

    inline void SetStartPosX(const double& pos_x) {
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
    }
    
    inline const QString GetContent() const {
        return content_;
    }

    inline const int GetWordCount() const {
        return word_count_;
    }

    bool HasSelected(const QPoint &pos) override; 
    void DrawShape(QPainter &painter) override;
    void MoveShape(const QPoint &curPoint, const QPoint &nextPoint) override;
    void PaintFrame(QPainter& painter) override;

    bool EnterSelectRange(const QPoint& point) override;

    QString html_content_;

    QTextDocument text_document_;

private:
    double start_pos_x_ = 0.0;
    double start_pos_y_ = 0.0;
    QString content_;
    int word_count_ = 0;
    bool selected_ = false;

    QWidget* parent_ = nullptr;

    QRectF rectf_;
};


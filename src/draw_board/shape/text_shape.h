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
    static std::shared_ptr<TextShape> Make(const QPointF& start_pos, const QString& content, QWidget* parent);
    TextShape(const QPointF& start_pos, const QString& content, QWidget* parent);
    ~TextShape();
    void DrawShape(QPainter &painter) override;
    void MoveShape(const QPoint &curPoint, const QPoint &nextPoint) override;
    void PaintFrame(QPainter& painter) override;
    bool EnterSelectRange(const QPoint& point) override;
    bool PointInRectangle(const QRectF& rect, const QPointF& point);
    QString GetHtml();
    void SetHiden(bool hiden);
    void SetHtml(const QString& html);
private:
    QWidget* parent_ = nullptr;
    QRectF rectf_;
    bool hiden_ = false;
    QString html_content_;
    QTextDocument text_document_;
};


#include "text_shape.h"

//TextShape::TextShape(const double& start_pos_x, const double& start_pos_y, const QString& content, QWidget* parent) {
//
//    qDebug() << "TextShape start_pos_x : " << start_pos_x << ", start_pos_y : " << start_pos_y;
//
//    shape_type_ = EShapeType::kText;
//
//    html_content_ = content;
//
//    parent_ = parent;
//
//    text_document_.setParent(parent_);  // 这一步重要，因为 drawContents 可以基于 parent 的坐标
//
//    start_point_.setX(start_pos_x);
//    start_point_.setY(start_pos_y);
//}


std::shared_ptr<TextShape> TextShape::Make(const QPointF& start_pos, const QString& content, QWidget* parent) {
    return std::make_shared<TextShape>(start_pos, content, parent);
}

TextShape::TextShape(const QPointF& start_pos, const QString& content, QWidget* parent) {
    //qDebug() << "TextShape start_pos_x : " << start_pos_x << ", start_pos_y : " << start_pos_y;
    shape_type_ = EShapeType::kText;
    html_content_ = content;
    parent_ = parent;
    text_document_.setParent(parent_);  // 这一步重要，因为 drawContents 可以基于 parent 的坐标
    start_point_ = start_pos;
}

TextShape::~TextShape() {

}

//bool TextShape::HasSelected(const QPoint &pos) {
//   
//    return this->selected_;
//}

bool TextShape::EnterSelectRange(const QPoint& point) {
    const int kRangeSize = 30;
    QRectF outside_rectf{ start_point_.x()*1.0 - kRangeSize, start_point_.y()*1.0 - kRangeSize,  rectf_.width() + 2 * kRangeSize, rectf_.height() + 2 * kRangeSize };
    return PointInRectangle(outside_rectf, point);
}

bool TextShape::PointInRectangle(const QRectF& rect, const QPointF& point) {
    return rect.contains(point);
}

void TextShape::DrawShape(QPainter &painter) {
    if (hiden_) {
        return;
    }

    text_document_.setHtml(this->html_content_);
    QSizeF doc_size = text_document_.size();
    rectf_ = QRectF{ start_point_.x(), start_point_.y(), doc_size.width(), doc_size.height() };
    painter.save();
    painter.translate(start_point_.x(), start_point_.y());   // 重要 painter.drawRect(start_pos_x_, start_pos_y_, doc_size.width(), doc_size.height());  可以绘制到 start_pos_x_ ， start_pos_y_ 处，
                                                             // 但是 drawContents 需要将painter 先进行位移
    text_document_.drawContents(&painter, QRectF(0, 0, doc_size.width(), doc_size.height()));  // 重要,要想 
    painter.restore();
}

void TextShape::MoveShape(const QPoint &curPoint, const QPoint &nextPoint) {
    QPoint dif = nextPoint - curPoint;
  /*  start_point_.setX(start_point_.x() + dis.x());
    start_point_.setY(start_point_.y() + dis.y());*/

    start_point_ = start_point_ + dif;
}

void TextShape::PaintFrame(QPainter &painter) {
    painter.save(); 
    QPen frame_pen(Qt::blue, 1 ,Qt::DashDotLine, Qt::RoundCap);
    painter.setPen(frame_pen);
    const int kRangeSize = 5;
    QRectF outside_rectf{ start_point_.x() * 1.0 - kRangeSize, start_point_.y() * 1.0 - kRangeSize,  rectf_.width() + 2 * kRangeSize, rectf_.height() + 2 * kRangeSize };
    painter.drawRect(outside_rectf);
    painter.restore();
}

QString TextShape::GetHtml() {
    return html_content_;
}

void TextShape::SetHiden(bool hiden) {
    hiden_ = hiden;
}

void TextShape::SetHtml(const QString& html) {
    html_content_ = html;
}
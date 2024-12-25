#include "text_shape.h"

TextShape::TextShape(const double& start_pos_x, const double& start_pos_y, const QString& content, QWidget* parent) {

    qDebug() << "TextShape start_pos_x : " << start_pos_x << ", start_pos_y : " << start_pos_y;

    shape_type_ = EShapeType::kText;
    start_pos_x_ = start_pos_x;
    start_pos_y_ = start_pos_y;
    content_ = content;
    word_count_ = content_.size();


    html_content_ = content;

    parent_ = parent;

    text_document_.setParent(parent_);  // 这一步重要，因为 drawContents 可以基于 parent 的坐标
}

TextShape::~TextShape() {

}
bool TextShape::HasSelected(const QPoint &pos) {
    this->selected_ = false;
    if(this->GetStartPosX() < pos.x() && this->GetStartPosX() + this->word_count_* 20 > pos.x()
            && this->GetStartPosY()-30 < pos.y() && this->GetStartPosY() > pos.y() ){
        this->selected_ = true;
    }
    return this->selected_;
}

bool TextShape::EnterSelectRange(const QPoint& point) {
    const int kRangeSize = 30;
    QRectF outside_rectf{ start_pos_x_ - kRangeSize, start_pos_y_ - kRangeSize,  rectf_.width() + 2 * kRangeSize, rectf_.height() + 2 * kRangeSize };
    return PointInRectangle(outside_rectf, point);
}

bool TextShape::PointInRectangle(const QRectF& rect, const QPointF& point) {
    return rect.contains(point);
}

void TextShape::DrawShape(QPainter &painter) {
    text_document_.setHtml(this->html_content_);
    QSizeF doc_size = text_document_.size();
    rectf_ = QRectF{ start_pos_x_, start_pos_y_, doc_size.width(), doc_size.height() };
    painter.save();
    painter.translate(start_pos_x_, start_pos_y_);   // 重要 painter.drawRect(start_pos_x_, start_pos_y_, doc_size.width(), doc_size.height());  可以绘制到 start_pos_x_ ， start_pos_y_ 处，
                                                     // 但是 drawContents 需要将painter 先进行位移
    
    text_document_.drawContents(&painter, QRectF(0, 0, doc_size.width(), doc_size.height()));  // 重要,要想 

    painter.restore();
}


void TextShape::MoveShape(const QPoint &curPoint, const QPoint &nextPoint)
{
    QPoint dis = nextPoint - curPoint;
    this->SetStartPosX(this->start_pos_x_ + dis.x());
    this->SetStartPosY(this->start_pos_y_ + dis.y());
}

void TextShape::PaintFrame(QPainter &painter) {
    painter.save(); 
    QPen frame_pen(Qt::blue, 1 ,Qt::DashDotLine, Qt::RoundCap);
    painter.setPen(frame_pen);
    painter.drawRect(this->start_pos_x_-4,this->start_pos_y_-25,this->word_count_*20+10,30);
    painter.restore();
}





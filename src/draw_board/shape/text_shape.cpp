#include "text_shape.h"

TextShape::TextShape() {
    shape_type_ = EShapeType::kText;
    start_pos_x_ = 0.0;
    start_pos_y_ = 0.0;
}

TextShape::TextShape(QPoint& click_point, ContentEdit& content_edit) {
    shape_type_ = EShapeType::kText;
    start_pos_x_ = click_point.x();
    start_pos_y_ = click_point.y();
    content_edit.clear();
    content_edit.show();
    content_edit.setGeometry(click_point.x(),click_point.y(),200,30);
    content_edit.setFocus();
}

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

    return false;
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
    painter.save(); // 保存画笔
    QPen frame_pen(Qt::blue, 1 ,Qt::DashDotLine, Qt::RoundCap);
    painter.setPen(frame_pen);
    painter.drawRect(this->start_pos_x_-4,this->start_pos_y_-25,this->word_count_*20+10,30);
    painter.restore(); // 恢复画笔
}

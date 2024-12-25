#include "content_edit.h"
#include <qtextdocument.h>

#include <qtextboundaryfinder.h>
#include <qdebug.h>
#include <qboxlayout.h>
#include <qsizepolicy.h>
#include <qpixmap.h>

ContentEdit::ContentEdit(QWidget *parent) : QPlainTextEdit(parent) {
}

ContentEdit::~ContentEdit()
{

}

void ContentEdit::focusOutEvent(QFocusEvent *e){
    hide();
    //    emit Signal_GetContent(this->text());
    QPlainTextEdit::focusOutEvent(e);
}

void ContentEdit::keyPressEvent(QKeyEvent *e) {
    //if(e->key() == Qt::Key_Enter
    //        || e->key() ==Qt::Key_Escape
    //        || e->key() == Qt::Key_Return){
    //    hide();
    //    emit Signal_GetContent(this->toPlainText());
    //
    //    QTextDocument* doc = this->document();
    //    int nCnt = doc->blockCount();
    //    for (int i = 0; i < nCnt; ++i)
    //    {
    //        QTextBlock textBlock = doc->findBlockByNumber(i);
    //        QString strtext = textBlock.text();
    //        qDebug() << "--:" << strtext;
    //    }
    // 
    //
    //
    //    this->clear();
    //}
    emit Signal_GetContent(this->toPlainText());
    QPlainTextEdit::keyPressEvent(e);
}

void ContentEdit::contextMenuEvent(QContextMenuEvent *){
    return;// 不要让菜单弹出，信号传递
}


TextEditWidget::TextEditWidget(QWidget* parent) : AutoSizeWidget(false, parent) {
    InitView();
    InitSigChannel();
}


TextEditWidget::~TextEditWidget() {


}

void TextEditWidget::InitView() {
    setMouseTracking(true);

    auto main_vlayout = new QVBoxLayout(bak_);
    main_vlayout->setAlignment(Qt::AlignTop);
    main_vlayout->setContentsMargins(0, 0, 0, 0);
    main_vlayout->setSpacing(0);

    title_bar_ = new QWidget();
    title_bar_->setMouseTracking(true);
    title_bar_->setStyleSheet("background-color:#ff0000;");
    auto title_hlayout = new QHBoxLayout(title_bar_);
    title_hlayout->setAlignment(Qt::AlignTop);
    title_hlayout->setContentsMargins(0, 0, 0, 0);
    title_hlayout->setSpacing(0);
    close_btn_ = new QToolButton();
    close_btn_->setFixedSize(30, 30);
    title_hlayout->addStretch(1);
    title_hlayout->addWidget(close_btn_);

    main_vlayout->addWidget(title_bar_);

    auto edit_hlayout = new QHBoxLayout();
    edit_hlayout->setContentsMargins(10, 0, 10, 10);
    edit_ = new QTextEdit();
    auto edit_size_policy = edit_->sizePolicy();
    edit_size_policy.setHorizontalPolicy(QSizePolicy::Expanding);
    edit_size_policy.setVerticalPolicy(QSizePolicy::Expanding);
    edit_hlayout->addWidget(edit_);
    main_vlayout->addLayout(edit_hlayout);

    auto btn_hlayout = new QHBoxLayout();
    btn_hlayout->setAlignment(Qt::AlignTop);
    btn_hlayout->setContentsMargins(0, 0, 0, 0);
    btn_hlayout->setSpacing(0);

    delete_all_btn_ = new QToolButton();
    delete_all_btn_->setFixedSize(30, 30);

    ok_btn_ = new QToolButton();
    ok_btn_->setFixedSize(30, 30);

    ok_btn_->setText("6");

    btn_hlayout->addStretch(1);
    btn_hlayout->addWidget(delete_all_btn_);
    btn_hlayout->addSpacing(8);
    btn_hlayout->addWidget(ok_btn_);
    btn_hlayout->addSpacing(8);

    main_vlayout->addLayout(btn_hlayout);
}


void TextEditWidget::mouseMoveEvent(QMouseEvent* event) {
   /* QRect title_rect = title_bar_->geometry();
    qDebug() << "0 title_rect: " << title_rect;
    title_rect.setY(title_rect.y() + 16);
    if (title_rect.contains(event->pos())) {

        setCursor(Qt::SizeAllCursor);

        if (pressed_) {
            move(event->pos() - point_ + pos());
        }
        qDebug() << "in";
        QWidget::mouseMoveEvent(event);
    }
    else {


        setCursor(Qt::ArrowCursor);
        qDebug() << "out";
        AutoSizeWidget::mouseMoveEvent(event);
    }
    qDebug() << "1 title_rect: " << title_rect;
    qDebug() << "pos : " << event->pos();*/





    QRect title_rect = title_bar_->geometry();
    title_rect.setY(title_rect.y() + 16);
    if (title_rect.contains(event->pos())) {
        if (pressed_) {
            enter_move_state = true;
        }
    }

    if (enter_move_state) {
        setCursor(Qt::SizeAllCursor);
        move(event->pos() - point_ + pos());
        QWidget::mouseMoveEvent(event);
    }
    else {
        AutoSizeWidget::mouseMoveEvent(event);
    }
}


void TextEditWidget::mouseReleaseEvent(QMouseEvent* event)
{
    pressed_ = false;

    enter_move_state = false;


    AutoSizeWidget::mouseReleaseEvent(event);
}

void TextEditWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        pressed_ = true;
        point_ = event->pos();
    }

    AutoSizeWidget::mousePressEvent(event);
}

void TextEditWidget::InitSigChannel() {
    connect(ok_btn_, &QToolButton::clicked, this, [=]() {
        

       /* auto d = edit_->document();*/

        //emit SigTextEdit(*edit_);


        //document = *d;

        emit SigHtml(edit_->toHtml());

       /// QTextDocument document;

       // QTextDocument* doc = edit_->document();
       ///* QTextDocument new_doc = *doc;*/
       //// emit SigTextDocument(*doc);
       // QPointF position(10, 10); // 左上角起点，留出一些边距
       //  // 遍历每一行（QTextBlock）
       // for (QTextBlock block = doc->begin(); block.isValid(); block = block.next()) {
       //     QTextLayout* layout = block.layout(); // 获取当前行的布局
       //     if (!layout) continue;
   
       //     // 遍历布局中的每一行（考虑自动换行）
       //     for (int i = 0; i < layout->lineCount(); ++i) {
       //         QTextLine line = layout->lineAt(i);
       //            

       //         // 设置每行的绘制位置
       //         QPointF linePosition = position + QPointF(0, line.y());
       //         //line.draw(&painter, linePosition);

       //         qDebug() << "line: " << line.;
       //     }
   
       // // 更新下一行的位置，加入块高度
       // position.setY(position.y() + layout->boundingRect().height());
   // }


    });
}

void TextEditWidget::ToPixmap() {

    // 获取 QPlainTextEdit 的 QTextDocument
    QTextDocument* doc = edit_->document();

    // 设置初始绘制位置
   // QPointF position(10, 10); // 左上角起点，留出一些边距
   //
   // // 遍历每一行（QTextBlock）
   // for (QTextBlock block = doc->begin(); block.isValid(); block = block.next()) {
   //     QTextLayout* layout = block.layout(); // 获取当前行的布局
   //     if (!layout) continue;
   //
   //     // 遍历布局中的每一行（考虑自动换行）
   //     for (int i = 0; i < layout->lineCount(); ++i) {
   //         QTextLine line = layout->lineAt(i);
   //
   //         // 设置每行的绘制位置
   //         QPointF linePosition = position + QPointF(0, line.y());
   //         line.draw(&painter, linePosition);
   //     }
   //
   //     // 更新下一行的位置，加入块高度
   //     position.setY(position.y() + layout->boundingRect().height());
   // }
}
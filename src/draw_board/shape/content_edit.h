#pragma once
#include <QLineEdit>
#include <QFocusEvent>
#include <QKeyEvent>
#include <QContextMenuEvent>
#include <QWidget>
#include <QMouseEvent>
#include <qtextedit.h>
#include <qplaintextedit.h>
#include <qtoolbutton.h>
#include <QTextBlock>
#include <qevent.h>
#include "auto_size_widget.h"

// to do 改为可以换行的
class ContentEdit : public QPlainTextEdit {
    Q_OBJECT
public:
    ContentEdit(QWidget *parent = nullptr);
    ~ContentEdit();

    void focusOutEvent(QFocusEvent *e) override;

    void keyPressEvent(QKeyEvent *e) override;

    void contextMenuEvent(QContextMenuEvent *event) override;

    //    void focusInEvent(QFocusEvent *) override;

signals:
    void Signal_GetContent(QString qstr);


private:
};

class TextEditWidget : public AutoSizeWidget {
    Q_OBJECT
public:
    TextEditWidget(QWidget* parent = nullptr);
    ~TextEditWidget();
    void InitView();

    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    

Q_SIGNALS:
    //void SigTextDocument(QTextDocument* text_doc);

    //void SigTextEdit(QTextEdit);

    void SigHtml(QString);

private:
    void ToPixmap();
    void InitSigChannel();
private:
    QWidget* title_bar_ = nullptr;

    QToolButton* close_btn_ = nullptr;
    QTextEdit* edit_ = nullptr;
    QToolButton* delete_all_btn_ = nullptr;
    QToolButton* ok_btn_ = nullptr;


    bool pressed_ = false;

    bool enter_move_state = false;

    QPoint point_;

   



};




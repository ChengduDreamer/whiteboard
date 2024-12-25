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

class TextEditWidget : public AutoSizeWidget {
    Q_OBJECT
public:
    TextEditWidget(QWidget* parent = nullptr);
    ~TextEditWidget();
    void InitView();
    void SetFocus();
    void Clear();
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




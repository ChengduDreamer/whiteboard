#pragma once
#include <QFocusEvent>
#include <QKeyEvent>
#include <QContextMenuEvent>
#include <QWidget>
#include <QMouseEvent>
#include <qtextedit.h>
#include <QTextBlock>
#include <qevent.h>
#include "auto_size_widget.h"

class YKIconButton;

class TextEditWidget : public AutoSizeWidget {
    Q_OBJECT
public:
    TextEditWidget(QWidget* parent = nullptr);
    ~TextEditWidget();
   
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;

    void SetFocus();
    void Clear();
    void SetHtml(const QString& html);
    int GetTitleBarHeight();
Q_SIGNALS:
    void SigHtml(QString);
    void SigCancel();
private:
    void InitView();
    void InitSigChannel();
private:
    QWidget* title_bar_ = nullptr;
    YKIconButton* close_btn_ = nullptr;
    QTextEdit* edit_ = nullptr;
    YKIconButton* ok_btn_ = nullptr;
    bool pressed_ = false;
    bool enter_move_state = false;
    QPoint point_;
};




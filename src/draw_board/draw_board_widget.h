#pragma once
#include <qwidget.h>
#include <qevent.h>
class QButtonGroup;
class QToolButton;
class DrawWidget;

class DrawBoardWidget : public QWidget
{
    Q_OBJECT
public:
    DrawBoardWidget(QWidget *parent = nullptr);
    ~DrawBoardWidget();

    void resizeEvent(QResizeEvent *event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

public slots:
    void OnRectangleBtnClicked();
    void OnEllipseBtnClicked();
    void OnLineBtnClicked();
    void OnTextBtnClicked();   
    void OnSelectBtnClicked();
    void OnRevokeBtnClicked();
    void OnCustomLineBtnClicked();
private:
    void InitView();
    void InitSigChannel();
private:
    QString content_text_;                         

    QToolButton* ellipase_btn_ = nullptr;          
    QToolButton* rectangle_btn_ = nullptr;         
    QToolButton* line_btn_ = nullptr;              
    QToolButton* custom_line_btn_ = nullptr;       
    QToolButton* text_btn_ = nullptr;                 
    QToolButton* revoke_btn_ = nullptr;            
    QButtonGroup* btn_group_ = nullptr;

    QToolButton* select_btn_ = nullptr;            
    DrawWidget* draw_widget_;                     
private:
    QString tool_btn_style_;

};

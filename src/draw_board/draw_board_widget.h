#pragma once
#include <qwidget.h>
#include <qevent.h>
class QButtonGroup;
class QToolButton;
class DrawWidget;
class YKIconButton;

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
    void OnDeleteBtnClicked();
    void OnRevokeBtnClicked();
    void OnCustomLineBtnClicked();
private:
    void InitView();
    void InitSigChannel();
private:
    QString content_text_;                         

    YKIconButton* ellipase_btn_ = nullptr;          
    YKIconButton* rectangle_btn_ = nullptr;         
    YKIconButton* line_btn_ = nullptr;              
    YKIconButton* custom_line_btn_ = nullptr;       
    YKIconButton* text_btn_ = nullptr;                 
    YKIconButton* placeholder_btn_ = nullptr;
    QButtonGroup* btn_group_ = nullptr;

    YKIconButton* revoke_btn_ = nullptr;            
    YKIconButton* delete_btn_ = nullptr;
    DrawWidget* draw_widget_;                     

};

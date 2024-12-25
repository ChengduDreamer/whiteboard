#ifndef CDRAWBOARDWIDGET_H
#define CDRAWBOARDWIDGET_H

#include <qwidget.h>
#include <qevent.h>
#include "MACRO.h"
#include "DrawWidget.h"

class QButtonGroup;
class QToolButton;

class CDrawBoardWidget : public QWidget
{
    Q_OBJECT
public:
    CDrawBoardWidget(QWidget *parent = nullptr);
    ~CDrawBoardWidget();

    void resizeEvent(QResizeEvent *event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

public slots:
    void OnRectangleBtnClicked();
    void OnEllipseBtnClicked();
    //void OnTriangleBtnClicked();
    void OnLineBtnClicked();
    void OnTextBtnClicked();   
    //void OnErasureBtnClicked();
    void OnSelectBtnClicked();
    void OnRevokeBtnClicked();
    void OnCustomLineBtnClicked();
private:
    void InitView();
    void InitSigChannel();
private:
    QString content_text_;                            // 文字获取

    QToolButton* ellipase_btn_ = nullptr;                        // 椭圆
    QToolButton* rectangle_btn_ = nullptr;                       // 矩形
    //QToolButton* triangle_btn_ = nullptr;                        // 三角形
    QToolButton* line_btn_ = nullptr;                            // 直线
    QToolButton* custom_line_btn_ = nullptr;                            // 画笔
    QToolButton* text_btn_ = nullptr;                            // 文字             
    //QToolButton* erasure_btn_ = nullptr;                         // 擦除
    QToolButton* revoke_btn_ = nullptr;                          // 撤销上一步
    QButtonGroup* btn_group_ = nullptr;


    QToolButton* select_btn_ = nullptr;                          // 选择

    DrawWidget* draw_widget_;                     // 绘画窗体，用于绘画的所有操作
private:
    QString tool_btn_style_;

};
#endif // CDRAWBOARDWIDGET_H

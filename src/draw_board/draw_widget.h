#pragma once

#include <qopenglwidget.h>
#include <QPainter>
#include <QPen>
#include <QFont>
#include <QBrush>
#include <QMouseEvent>
#include <QDebug>
#include <QVector>
#include <QPainterPath>
#include <QTimer>
#include <QSharedPointer>
#include <QPoint>
#include <QLineEdit>
#include <QKeyEvent>
#include <qpixmap.h>
#include <memory>
#include "shape/base_shape.h"

class QLineEdit;
class QBrush;
class QTimer;

class TextShape;
class TextEditWidget;
class DrawBoardWidget;

class DrawWidget :public QWidget
{
    Q_OBJECT
    friend class DrawBoardWidget;
public:
    DrawWidget(QWidget *parent = nullptr);
    ~DrawWidget();

    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
   
    void SetShapeType(const EShapeType &shape_type) {
        draw_shape_type_ = shape_type;
    }

    EShapeType GetShapeType() {
        return draw_shape_type_;
    }

    //撤销操作
    void Revoke();
 
    //存储画笔的点
    QVector<QPoint> points_data_;

    enum class EMouseState {
        kGeneral,
        kMoveShape,
        kDrawShape,
    };

    EMouseState mouse_state_ = EMouseState::kGeneral;

    // 当前选中的对象
    std::shared_ptr<BaseShape> cur_select_shape_ = nullptr;
    std::vector<std::shared_ptr<BaseShape>> shapes_;

    void SetBackground(QPixmap&& pixmap);

private:
    void InitView();
    void InitSigChannel();

private:
    
    TextEditWidget* text_edit_ = nullptr;

    // 文本编辑位置
    QPoint text_point_;               
      
    // 当前绘画的类型
    EShapeType draw_shape_type_ = EShapeType::kUnkonwn;

    // 鼠标左键是否按下
    bool mouse_left_btn_pressed_ = false;

    //鼠标点击的坐标
    QPoint clicked_point_;            

    // 鼠标移动的坐标
    QPoint move_point_;               

    //画笔
    QPen black_pen_;

    // 文字字体
    QFont text_font_;

    //空画刷 背景
    QBrush null_brush_;

    // 白色 背景
    QBrush white_brush_;
    
    // 编辑状态中的文本图形
    std::shared_ptr<TextShape> editing_text_shape_ = nullptr;

    QPixmap bg_pixmap_;

    QPixmap origin_pixmap_;
};


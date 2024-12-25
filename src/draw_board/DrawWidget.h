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
#include <memory>

//#include "systemdata.h"
#include "shape/base_shape.h"
#include "shape/content_edit.h"
#include "shape/custom_line_shape.h"
#include "shape/line_shape.h"
#include "shape/ellipse_shape.h"
#include "shape/rectangle_shape.h"
#include "shape/text_shape.h"

class QLineEdit;
class QBrush;
class QTimer;
//class SystemData;
class TextEditWidget;

class CDrawBoardWidget;

class DrawWidget :public QOpenGLWidget
{
    Q_OBJECT
    friend class CDrawBoardWidget;
public:
    DrawWidget(QWidget *parent = nullptr);
    ~DrawWidget();

    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
   
    inline void SetShapeType(const EShapeType &shape_type) {
        shape_type_ = shape_type;
    }

    inline EShapeType GetShapeType(){
        return shape_type_;
    }

    //撤销操作
    void Revoke();

    //是否是选择状态
    bool select_btn_clicked_ = false;
 
    //存储画笔的点
    QVector<QPoint> points_data_;

private:
    void InitView();
    void InitSigChannel();

private slots:
    void fn_Recv_ContentEdit_GetContent(const QString &qstrContent);
    //void fn_Change_StatusEdit_Visual(const QString &qstrContent);

private:
    // 当前选中的对象
    std::shared_ptr<BaseShape> cur_select_shape_ = nullptr;

    // 文本编辑窗口
    //ContentEdit content_edit_;        

    TextEditWidget* text_edit_ = nullptr;

    // 文本编辑位置
    QPoint text_point_;               
      
    // 当前绘画的类型
    EShapeType shape_type_ = EShapeType::kUnkonwn;

    // 鼠标左键是否按下
    bool mouse_left_btn_pressed_ = false;

    //鼠标点击的坐标
    QPoint clicked_point_;            

    // 鼠标移动的坐标
    QPoint move_point_;               

    //QLineEdit m_StatusEdit; // 文本框中的文字

    //画笔
    QPen black_pen_;

    // 文字字体
    QFont text_font_;

    //空画刷  背景
    QBrush null_brush_;

    // 白色  背景
    QBrush white_brush_;

    //QBrush m_BackgroundBrush;// 自己设置测试的背景色
    //QBrush m_ErasureBrush;//橡皮檫颜色
    //    QVector<QVector<QPoint>> ErasurePoints;
    //QVector<QPoint> ErasurePoint;// 橡皮檫的容器

    //bool m_DemensionBtnClicked = false;
    //QVector<QPoint> DemensionsPoint;// 标注的三个点

    //ERotateType m_RotateType;// 旋转角度
    //QPoint *m_StartingClickPoint;// 用于做旋转的基点指针

    //GLfloat zscale=1; // 缩放比例属性

    // 移动操作的变量

    //QPoint m_MoveTempPoint;// 鼠标移动的坐标
    
    // 选中的对象下标
    int cur_selected_shape_index_ = -1;

    // 是否双击
    bool double_clicked_ = false;

   // const QPoint *m_CapturePoint = nullptr;// 捕获的点


    //std::shared_ptr<BaseShape> CreateShapeItem(EShapeType& type, QPoint& clickedPoint, QPoint& movePoint, QVector<QPoint>& Vec, ContentEdit& contentEdit);


    std::vector<std::shared_ptr<BaseShape>> shapes_;
};


#include "draw_board_widget.h"
#include <qboxlayout.h>
#include <qfile.h>
#include <qdebug.h>
#include <QPushButton.h>
#include <qbuttongroup.h>
#include <qtimer.h>
#include <qpixmap.h>
#include <qfiledialog.h>
#include <qfileinfo.h>
#include <qsettings.h>
#include <qdatetime.h>
#include <qdir.h>
#include "public/yk_icon_button.h"
#include "draw_widget.h"

static const QString kSavePngDir = "yk_save_png_dir";

static const QString kOpenPngDir = "yk_open_png_dir";

DrawBoardWidget::DrawBoardWidget(QWidget *parent): QWidget(parent) {

    qsettings_ = std::make_shared<QSettings>("YKSoftWare", "YKDrawBoardWidget");
    InitView();
    InitSigChannel();
    resize(800, 600);
}

DrawBoardWidget::~DrawBoardWidget() {
    
}

void DrawBoardWidget::InitView() {
    const int kIconBtnSize = 30;

    setMouseTracking(true);
    setAttribute(Qt::WA_StyledBackground);
    this->setWindowTitle(QStringLiteral("白板"));
 
    auto main_vlayout = new QVBoxLayout(this);
    main_vlayout->setSpacing(0);
    main_vlayout->setAlignment(Qt::AlignTop);
    main_vlayout->setContentsMargins(0, 0, 0, 0);

    draw_widget_ = new DrawWidget(this);
    main_vlayout->addWidget(draw_widget_);

    auto menu_bar_hlayout = new QHBoxLayout();
    menu_bar_hlayout->setSpacing(12);
    menu_bar_hlayout->setAlignment(Qt::AlignLeft);
    menu_bar_hlayout->setContentsMargins(0, 0, 0, 0);

    QWidget* shape_btn_bk_widget = new QWidget();
    //shape_btn_bk_widget->setStyleSheet("border:1px solid #99aaee;");
    auto shape_btn_hlayout = new QHBoxLayout(shape_btn_bk_widget);
    shape_btn_hlayout->setSpacing(12);
    shape_btn_hlayout->setAlignment(Qt::AlignLeft);
    shape_btn_hlayout->setContentsMargins(8, 0, 8, 0);

    YKIconButton::BackgroundInfo icon_bg_info;
    icon_bg_info.m_background_color_normal = icon_bg_info.m_background_color_hover = icon_bg_info.m_background_color_disable = icon_bg_info.m_background_color_press = QColor(0xff, 0xff, 0xff, 0);
    icon_bg_info.m_background_color_checked = QColor(0xad, 0xd8, 0xe6);

    btn_group_ = new QButtonGroup();
    ellipase_btn_ = new YKIconButton();
    ellipase_btn_->Init(QSize(kIconBtnSize, kIconBtnSize), ":/draw_board/image/oper_icon/circle_normal.svg", ":/draw_board/image/oper_icon/circle_hover.svg", ":/draw_board/image/oper_icon/circle_press.svg");
    ellipase_btn_->SetUseSvg(true);
    ellipase_btn_->SetBackgroundInfo(icon_bg_info);

    rectangle_btn_ = new YKIconButton();
    rectangle_btn_->Init(QSize(kIconBtnSize, kIconBtnSize), ":/draw_board/image/oper_icon/rectangle_normal.svg", ":/draw_board/image/oper_icon/rectangle_hover.svg", ":/draw_board/image/oper_icon/rectangle_press.svg");
    rectangle_btn_->SetUseSvg(true);
    rectangle_btn_->SetBackgroundInfo(icon_bg_info);

    line_btn_ = new YKIconButton();
    line_btn_->Init(QSize(kIconBtnSize, kIconBtnSize), ":/draw_board/image/oper_icon/line_normal.svg", ":/draw_board/image/oper_icon/line_hover.svg", ":/draw_board/image/oper_icon/line_press.svg");
    line_btn_->SetUseSvg(true);
    line_btn_->SetBackgroundInfo(icon_bg_info);

    custom_line_btn_ = new YKIconButton();
    custom_line_btn_->Init(QSize(kIconBtnSize, kIconBtnSize), ":/draw_board/image/oper_icon/draw_pen_normal.svg", ":/draw_board/image/oper_icon/draw_pen_hover.svg", ":/draw_board/image/oper_icon/draw_pen_press.svg");
    custom_line_btn_->SetUseSvg(true);
    custom_line_btn_->SetBackgroundInfo(icon_bg_info);

    text_btn_ = new YKIconButton();
    text_btn_->Init(QSize(kIconBtnSize, kIconBtnSize), ":/draw_board/image/oper_icon/text_edit_normal.svg", ":/draw_board/image/oper_icon/text_edit_hover.svg", ":/draw_board/image/oper_icon/text_edit_press.svg");
    text_btn_->SetUseSvg(true);
    text_btn_->SetBackgroundInfo(icon_bg_info);

    open_file_btn_ = new YKIconButton();
    open_file_btn_->Init(QSize(kIconBtnSize, kIconBtnSize), ":/draw_board/image/oper_icon/file_open_normal.svg", ":/draw_board/image/oper_icon/file_open_hover.svg", ":/draw_board/image/oper_icon/file_open_press.svg");
    open_file_btn_->SetUseSvg(true);

    download_btn_ = new YKIconButton();
    download_btn_->Init(QSize(kIconBtnSize, kIconBtnSize), ":/draw_board/image/oper_icon/download_normal.svg", ":/draw_board/image/oper_icon/download_hover.svg", ":/draw_board/image/oper_icon/download_press.svg");
    download_btn_->SetUseSvg(true);

    delete_btn_ = new YKIconButton();
    delete_btn_->Init(QSize(kIconBtnSize, kIconBtnSize), ":/draw_board/image/oper_icon/delete_element_normal.svg", ":/draw_board/image/oper_icon/delete_element_hover.svg", ":/draw_board/image/oper_icon/delete_element_press.svg");
    delete_btn_->SetUseSvg(true);

    revoke_btn_ = new YKIconButton();
    revoke_btn_->Init(QSize(kIconBtnSize, kIconBtnSize), ":/draw_board/image/oper_icon/backspace_normal.svg", ":/draw_board/image/oper_icon/backspace_hover.svg", ":/draw_board/image/oper_icon/backspace_press.svg");
    revoke_btn_->SetUseSvg(true);

    placeholder_btn_ = new YKIconButton();
    placeholder_btn_->setVisible(false);

    btn_group_->addButton(ellipase_btn_);
    btn_group_->addButton(rectangle_btn_);
    btn_group_->addButton(line_btn_);
    btn_group_->addButton(custom_line_btn_);
    btn_group_->addButton(text_btn_);
    btn_group_->addButton(placeholder_btn_);
    btn_group_->setExclusive(true);

    for (auto btn : btn_group_->buttons()) {
        btn->setCheckable(true);
    }

    shape_btn_hlayout->addWidget(ellipase_btn_);
    shape_btn_hlayout->addWidget(rectangle_btn_);
    shape_btn_hlayout->addWidget(line_btn_);
    shape_btn_hlayout->addWidget(custom_line_btn_);
    shape_btn_hlayout->addWidget(text_btn_);

    //menu_bar_hlayout->addStretch(1);
    menu_bar_hlayout->addWidget(shape_btn_bk_widget);
    menu_bar_hlayout->addStretch(1);
    menu_bar_hlayout->addWidget(open_file_btn_);
    menu_bar_hlayout->addWidget(download_btn_);
    menu_bar_hlayout->addWidget(delete_btn_);
    menu_bar_hlayout->addWidget(revoke_btn_);
    menu_bar_hlayout->addSpacing(30);

    main_vlayout->addLayout(menu_bar_hlayout);

    
    download_btn_->setToolTip("save as png.");
    delete_btn_->setToolTip("delete selected graphics.");
    revoke_btn_->setToolTip("delete the graphic drawn in the previous step.");
}

void DrawBoardWidget::InitSigChannel() {
    connect(ellipase_btn_, &QPushButton::clicked, this, &DrawBoardWidget::OnEllipseBtnClicked);
    connect(rectangle_btn_, &QPushButton::clicked, this, &DrawBoardWidget::OnRectangleBtnClicked);
    connect(line_btn_, &QPushButton::clicked, this, &DrawBoardWidget::OnLineBtnClicked);
    connect(text_btn_, &QPushButton::clicked, this, &DrawBoardWidget::OnTextBtnClicked);
    connect(custom_line_btn_, &QPushButton::clicked, this, &DrawBoardWidget::OnCustomLineBtnClicked);

    connect(download_btn_, &QPushButton::clicked, this, &DrawBoardWidget::OnDownloadBtnClicked);
    connect(delete_btn_, &QPushButton::clicked, this, &DrawBoardWidget::OnDeleteBtnClicked);
    connect(revoke_btn_, &QPushButton::clicked, this, &DrawBoardWidget::OnRevokeBtnClicked);
    connect(open_file_btn_, &QPushButton::clicked, this, &DrawBoardWidget::OnOpenFileBtnClicked);
}


void DrawBoardWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
}

void DrawBoardWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Delete: {
        if(draw_widget_->cur_select_shape_ ){
            draw_widget_->shapes_.erase(std::remove(draw_widget_->shapes_.begin(), draw_widget_->shapes_.end(), draw_widget_->cur_select_shape_), draw_widget_->shapes_.end());
            draw_widget_->cur_select_shape_ = NULL;
        }
        break;
    }
    case Qt::Key_Escape:
        RestoreDrawWidget();
        break;
    case Qt::Key_Return:
        break;
    case Qt::Key_F1:
        break;
    }
    QWidget::keyPressEvent(event);
}

void DrawBoardWidget::keyReleaseEvent(QKeyEvent *event) {
    QWidget::keyReleaseEvent(event);
}

void DrawBoardWidget::OnRectangleBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kReckangle);
    rectangle_btn_->setChecked(true);
}

void DrawBoardWidget::OnEllipseBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kEllipse);
    ellipase_btn_->setChecked(true);
}

void DrawBoardWidget::OnLineBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kLine);
    line_btn_->setChecked(true);
}

void DrawBoardWidget::OnTextBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kText);
    text_btn_->setChecked(true);
}

void DrawBoardWidget::OnDeleteBtnClicked() {
    if (draw_widget_->cur_select_shape_) {
        draw_widget_->shapes_.erase(std::remove(draw_widget_->shapes_.begin(), draw_widget_->shapes_.end(), draw_widget_->cur_select_shape_), draw_widget_->shapes_.end());
        draw_widget_->cur_select_shape_ = NULL;
    }
}

void DrawBoardWidget::OnRevokeBtnClicked() {
    draw_widget_->Revoke();
}

void DrawBoardWidget::OnCustomLineBtnClicked() {
    draw_widget_->SetShapeType(EShapeType::kCustomLine);
    custom_line_btn_->setChecked(true);
}

void DrawBoardWidget::OnDownloadBtnClicked() {
    RestoreDrawWidget();
    auto pixmap = draw_widget_->grab();
    QString save_dir_str = qsettings_->value(kSavePngDir).toString();
    bool dir_exists = false;
    if (!save_dir_str.isEmpty()) {
        QDir save_dir{ save_dir_str };
        if (save_dir.exists()) {
            dir_exists = true;
        }
    }

    qint64 timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch(); //毫秒级
    qDebug() << "save_dir_str: " << save_dir_str;
    QString save_file_path;
    if (dir_exists) {
        QDir save_dir{ save_dir_str };
        save_file_path =  save_dir.absoluteFilePath(QString("%1.png").arg(QString::number(timestamp))); // 拼接文件名的时候， 文件名前面不要再带路径分隔符
    }
    else {
        save_file_path = QString("./%1.png").arg(QString::number(timestamp));
    }

    qDebug() << "save_file_path: " << save_file_path;
    QString file_path = QFileDialog::getSaveFileName(this, "Save Widget as PNG", save_file_path, "Images (*.png)");
    if (!file_path.isEmpty()) {
        if (pixmap.save(file_path, "PNG")) {
            qDebug() << "Widget saved as PNG:" << file_path;
            QFileInfo file_info{ file_path };
            qsettings_->setValue(kSavePngDir, file_info.absolutePath());
            qsettings_->sync();
        }
        else {
            qDebug() << "Failed to save the widget as PNG.";
        }
    }
}

void DrawBoardWidget::RestoreDrawWidget() {
    draw_widget_->SetShapeType(EShapeType::kUnkonwn);
    draw_widget_->cur_select_shape_ = NULL;
    placeholder_btn_->setChecked(true);
}

void DrawBoardWidget::OnOpenFileBtnClicked() {
    QString open_dir_str = qsettings_->value(kOpenPngDir).toString();
    bool dir_exists = false;
    if (!open_dir_str.isEmpty()) {
        QDir open_dir{ open_dir_str };
        if (open_dir.exists()) {
            dir_exists = true;
        }
    }

    //QString file_name = QFileDialog::getOpenFileName(this, "Select a Image File", "", "Images (*.png *.jpg *.jpeg);;All Files (*)");  // 这样就可以多条过滤条件
    QString file_name = QFileDialog::getOpenFileName(this, "Select a Image File", dir_exists ? open_dir_str : QString(""), "Images (*.png *.jpg *.jpeg);");
    if (file_name.isEmpty()) {
        return;
    }
    qDebug() << "Selected file:" << file_name;

    QFileInfo file_info{ file_name };
    qsettings_->setValue(kOpenPngDir, file_info.absolutePath());
    qsettings_->sync();

    QPixmap pixmap;
    pixmap.load(file_name);
    this->resize(pixmap.size());  // to do ，如果图片太大，需要增加滚动条
    draw_widget_->SetBackground(std::move(pixmap));

}


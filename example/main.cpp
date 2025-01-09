#include <iostream>
#include <memory>
#include <QApplication>
#include <QScreen>
#include <qfile.h>
#include "draw_board/draw_board_widget.h"

//using namespace yk;
// to do 

int main(int argc, char* argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QCoreApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
    QApplication a(argc, argv);

    
 
    DrawBoardWidget w;
    w.show();

    return a.exec();
}

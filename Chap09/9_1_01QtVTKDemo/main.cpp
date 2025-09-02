// main.cpp
#include <QApplication>
#include <QSurfaceFormat> // 可能需要设置OpenGL格式
#include <QVTKOpenGLNativeWidget.h>
#include "MainWindow.h"

int main(int argc, char **argv)
{
    // 设置OpenGL表面格式，确保兼容性
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
    QApplication app(argc, argv);

    MainWindow window;
    window.show();
    return app.exec();
}
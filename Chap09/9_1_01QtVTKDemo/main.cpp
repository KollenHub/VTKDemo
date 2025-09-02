// main.cpp
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QSurfaceFormat> // 可能需要设置OpenGL格式

// 关键头文件
#include <QVTKOpenGLNativeWidget.h> 
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>

int main(int argc, char** argv)
{
    // 设置OpenGL表面格式，确保兼容性
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

    QApplication app(argc, argv);

    // 创建主窗口和中央部件
    QMainWindow mainWindow;
    QWidget* centralWidget = new QWidget(&mainWindow);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    // 1. 创建QVTKOpenGLNativeWidget
    QVTKOpenGLNativeWidget* vtkWidget = new QVTKOpenGLNativeWidget(centralWidget);
    layout->addWidget(vtkWidget);

    // 2. (可选) 关联VTK渲染窗口
    //    也可以直接使用 vtkWidget->renderWindow()
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkWidget->setRenderWindow(renderWindow); 

    // 3. 创建简单的VTK管线（圆锥）
    vtkNew<vtkConeSource> coneSource;
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(coneSource->GetOutputPort());
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);

    double left[]={0.0,0.0,0.5,1.0};
    double right[]={0.5,0.0,1.0,1.0};

    vtkNew<vtkRenderer> leftRenderer;
    leftRenderer->AddActor(actor);
    leftRenderer->SetBackground(0.5, 0.5, 0.8); // 设置背景色
    leftRenderer->SetViewport(left);

    vtkNew<vtkRenderer> rightRenderer;
    rightRenderer->AddActor(actor);
    rightRenderer->SetBackground(0.5, 0.5, 0); // 设置背景色
    rightRenderer->SetViewport(right);

    // 4. 将渲染器添加到VTK渲染窗口
    renderWindow->AddRenderer(leftRenderer);
    renderWindow->AddRenderer(rightRenderer);
    // 或者使用: renderWindow->AddRenderer(renderer);

    // 5. 调用Render()进行初始渲染
    vtkWidget->renderWindow()->Render();

    mainWindow.setCentralWidget(centralWidget);
    mainWindow.resize(800, 600);
    mainWindow.show();

    return app.exec();
}
#include "MainWindow.h"
#include <QVTKOpenGLNativeWidget.h>
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <QPushButton>
#include "OperationBar.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVTKOpenGLNativeWidget *vtkWidget = new QVTKOpenGLNativeWidget(this->ui->centralwidget);
    vtkWidget->setMinimumWidth(600);

    ui->vtkContainer->addWidget(vtkWidget, 0, 0, 2, 2);

    this->ui->vtkContainer->setContentsMargins(0, 0, 0, 0);
    this->ui->vtkContainer->setSpacing(0);

    OperationBar *bar = new OperationBar(this);
    bar->setContentsMargins(0, 0, 0, 0);
    bar->setFixedHeight(30);
    // 添加工具条
    ui->vtkContainer->addWidget(bar, 0, 0);

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

    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(actor);
    renderer->SetBackground(0.5, 0.5, 0.8); // 设置背景色

    vtkNew<vtkRenderer> rightRenderer;
    rightRenderer->AddActor(actor);
    rightRenderer->SetBackground(0.5, 0.5, 0); // 设置背景色

    // 4. 将渲染器添加到VTK渲染窗口
    renderWindow->AddRenderer(renderer);
    renderWindow->AddRenderer(rightRenderer);
    // 或者使用: renderWindow->AddRenderer(renderer);

    // 5. 调用Render()进行初始渲染
    vtkWidget->renderWindow()->Render();
    this->resize(800, 600);
}

MainWindow::~MainWindow()
{
}

#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataMapper.h>
#include "AutoCom.h"

// 网格平滑
int main(int argc, char *argv[])
{

    AutoCOM::Init();
    vtkSmartPointer<vtkPLYReader> reader = vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName("../datas/bunny.ply");
    reader->Update();

    vtkSmartPointer<vtkSmoothPolyDataFilter> smoothFilter = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
    smoothFilter->SetInputConnection(reader->GetOutputPort());

    // 迭代次数
    smoothFilter->SetNumberOfIterations(200);
    smoothFilter->Update();

    vtkSmartPointer<vtkPolyDataMapper> originMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    originMapper->SetInputData(reader->GetOutput());

    vtkSmartPointer<vtkActor> originActor = vtkSmartPointer<vtkActor>::New();
    originActor->SetMapper(originMapper);

    vtkSmartPointer<vtkPolyDataMapper> smoothMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    smoothMapper->SetInputData(smoothFilter->GetOutput());

    vtkSmartPointer<vtkActor> smoothActor = vtkSmartPointer<vtkActor>::New();
    smoothActor->SetMapper(smoothMapper);

    double left[4] = {0.0, 0.0, 0.5, 1.0};
    double right[4] = {0.5, 0.0, 1.0, 1.0};

    vtkSmartPointer<vtkRenderer> originRenderer = vtkSmartPointer<vtkRenderer>::New();
    originRenderer->SetViewport(left);
    originRenderer->AddActor(originActor);
    originRenderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderer> smoothRenderer = vtkSmartPointer<vtkRenderer>::New();
    smoothRenderer->SetViewport(right);
    smoothRenderer->AddActor(smoothActor);
    smoothRenderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(originRenderer);
    renderWindow->AddRenderer(smoothRenderer);
    renderWindow->SetSize(800, 400);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
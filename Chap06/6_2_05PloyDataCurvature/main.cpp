#include <vtkPointData.h>
#include <vtkScalarBarActor.h>
#include <vtkProperty.h>
#include <vtkSmartPointer.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include "AutoCom.h"
#include <vtkCurvatures.h>
#include <vtkLookupTable.h>

int main(int argc, char *argv[])
{
    AutoCOM::Init();
    vtkSmartPointer<vtkPLYReader> reader = vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName("../datas/bunny.ply");
    reader->Update();

    vtkSmartPointer<vtkCurvatures> curvatureFilter = vtkSmartPointer<vtkCurvatures>::New();
    curvatureFilter->SetInputConnection(reader->GetOutputPort());
    //四种计算曲率的方法
    // curvatureFilter->SetCurvatureTypeToMaximum();
    // curvatureFilter->SetCurvatureTypeToGaussian();
    // curvatureFilter->SetCurvatureTypeToMinimum();
    curvatureFilter->SetCurvatureTypeToMean();
    curvatureFilter->Update();

    double sacalarRange[2];
    curvatureFilter->GetOutput()->GetScalarRange(sacalarRange);

    vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();

    lut->SetHueRange(0.0, 0.6);
    lut->SetAlphaRange(1.0, 1.0);
    lut->SetValueRange(1.0, 1.0);
    lut->SetSaturationRange(1.0, 1.0);
    lut->SetNumberOfTableValues(256);
    lut->SetRange(sacalarRange);
    lut->Build();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(curvatureFilter->GetOutput());
    mapper->SetScalarRange(sacalarRange);
    mapper->SetLookupTable(lut);

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkScalarBarActor> scalarBar = vtkSmartPointer<vtkScalarBarActor>::New();
    scalarBar->SetLookupTable(mapper->GetLookupTable());
    scalarBar->SetTitle(curvatureFilter->GetOutput()->GetPointData()->GetScalars()->GetName());
    scalarBar->SetNumberOfLabels(5);

    // 渲染器
    vtkSmartPointer<vtkRenderer> originRenderer = vtkSmartPointer<vtkRenderer>::New();
    originRenderer->AddActor(actor);
    originRenderer->AddActor2D(scalarBar);
    originRenderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(originRenderer);
    renderWindow->SetSize(600, 320);
    renderWindow->Render();
    renderWindow->SetWindowName("PolyDataCurvature");

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

    return 0;
}
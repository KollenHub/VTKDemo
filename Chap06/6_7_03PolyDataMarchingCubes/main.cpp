#include <vtkSmartPointer.h>
#include <vtkMarchingCubes.h>
#include <vtkContourFilter.h>
#include <vtkVoxelModeller.h>
#include <vtkSphereSource.h>
#include <vtkImageData.h>
#include <vtkMetaImageReader.h>
#include <vtkInteractorStyleImage.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>

int main(int argc, char *argv[])
{

    vtkSmartPointer<vtkMetaImageReader> reader = vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName("../datas/head.mhd");
    ;
    reader->Update();

    double isoValue = 100;

    vtkSmartPointer<vtkMarchingCubes> surface = vtkSmartPointer<vtkMarchingCubes>::New();
    surface->SetInputData(reader->GetOutput());
    surface->ComputeNormalsOn();
    surface->SetValue(0, isoValue);
    surface->Update();

    vtkSmartPointer<vtkPolyDataMapper> surfaceMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    surfaceMapper->SetInputConnection(surface->GetOutputPort());
    surfaceMapper->ScalarVisibilityOff();

    vtkSmartPointer<vtkActor> surfaceActor = vtkSmartPointer<vtkActor>::New();
    surfaceActor->SetMapper(surfaceMapper);
    surfaceActor->GetProperty()->SetColor(1.0,0.0,0.0);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

    renderer->AddActor(surfaceActor);
    renderer->SetBackground(1.0,1.0,1.0);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(600,600);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderWindow->Render();

    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

    return 0;
}
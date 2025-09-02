#include <vtkJPEGReader.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageActor.h>

int main(int argc, char *argv[])
{
    vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();

    reader->SetFileName("../datas/lena.jpg");
    reader->Update();

    vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
    actor->SetInputData(reader->GetOutput());

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
    renderWindowInteractor->SetInteractorStyle(style);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start(); 
    return 0;
}
#include <vtkSmartPointer.h>
#include <vtkDistanceWidget.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkDistanceRepresentation.h>

int main(int argc, char *argv[])
{

    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();

    vtkSmartPointer<vtkRenderer> renderer =
        vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(1.0, 1.0, 1.0);

    renderWindow->AddRenderer(renderer);

    vtkSmartPointer<vtkRenderWindowInteractor> iren =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renderWindow);

    vtkSmartPointer<vtkDistanceWidget> distanceWidget =
        vtkSmartPointer<vtkDistanceWidget>::New();

    distanceWidget->SetInteractor(iren);
    distanceWidget->CreateDefaultRepresentation();
    static_cast<vtkDistanceRepresentation *>(distanceWidget->GetRepresentation())->SetLabelFormat("%-#6.3g px");

    distanceWidget->On();

    iren->Initialize();
    iren->Start();

    return EXIT_SUCCESS;
}
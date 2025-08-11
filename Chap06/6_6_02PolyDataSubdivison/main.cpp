#include <vtkSmartPointer.h>
#include <vtkPolyDataAlgorithm.h>
#include <vtkLinearSubdivisionFilter.h>
#include <vtkLoopSubdivisionFilter.h>
#include <vtkButterflySubdivisionFilter.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkPLYReader.h>
#include <vtkSphereSource.h>
int main(int argc, char *argv[])
{
    vtkSmartPointer<vtkPolyData> originMesh;

    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->Update();

    originMesh = sphereSource->GetOutput();

    double numberOfViewPorts = 3;
    int numberOfSubdivisions = 2;

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->SetSize(200 * numberOfViewPorts, 200);
    renderWindow->SetWindowName("Multiple ViewPorts");

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    for (size_t i = 0; i < numberOfViewPorts; i++)
    {
        vtkSmartPointer<vtkPolyDataAlgorithm> subdivsionFilter;
        switch (i)
        {
        case 0:
            subdivsionFilter = vtkSmartPointer<vtkLinearSubdivisionFilter>::New();
            dynamic_cast<vtkLinearSubdivisionFilter *>(subdivsionFilter.GetPointer())->SetNumberOfSubdivisions(numberOfSubdivisions);
            break;
        case 1:
            subdivsionFilter = vtkSmartPointer<vtkLoopSubdivisionFilter>::New();
            dynamic_cast<vtkLoopSubdivisionFilter *>(subdivsionFilter.GetPointer())->SetNumberOfSubdivisions(numberOfSubdivisions);
            break;
        case 2:
            subdivsionFilter = vtkSmartPointer<vtkButterflySubdivisionFilter>::New();
            dynamic_cast<vtkButterflySubdivisionFilter *>(subdivsionFilter.GetPointer())->SetNumberOfSubdivisions(numberOfSubdivisions);
            break;
        }
        subdivsionFilter->SetInputData(originMesh);
        subdivsionFilter->Update();

        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputConnection(subdivsionFilter->GetOutputPort());

        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);

        vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
        renderer->AddActor(actor);
        renderer->SetBackground(1.0, 1.0, 1.0);
        renderer->SetViewport(static_cast<double>(i)/numberOfViewPorts,0,static_cast<double>(i+1)/numberOfViewPorts,1);
        renderer->ResetCamera();


        renderWindow->AddRenderer(renderer);
    }

    renderWindow->SetSize(640,320);
    renderWindow->SetWindowName("PolyDataSubdivision");
    renderWindow->Render();
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
}
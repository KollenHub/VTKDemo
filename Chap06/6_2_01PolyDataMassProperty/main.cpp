#include <vtkPolyDataMapper.h>
#include <vtkSmartPointer.h>
#include <vtkMassProperties.h>
#include <vtkCubeSource.h>
#include <vtkTriangleFilter.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindowInteractor.h>
#include <AutoCom.h>

int main()
{
    AutoCOM::Init();

    vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
    cubeSource->Update();

    vtkSmartPointer<vtkTriangleFilter> triFilter = vtkSmartPointer<vtkTriangleFilter>::New();
    triFilter->SetInputData(cubeSource->GetOutput());
    triFilter->Update();

    vtkSmartPointer<vtkMassProperties> massProp = vtkSmartPointer<vtkMassProperties>::New();
    massProp->SetInputData(triFilter->GetOutput());

    float volume = massProp->GetVolume();
    float area = massProp->GetSurfaceArea();
    float maxArea = massProp->GetMaxCellArea();
    float minArea = massProp->GetMinCellArea();

    std::cout << "Volume: " << volume << std::endl;
    std::cout << "Area: " << area << std::endl;
    std::cout << "maxArea: " << maxArea << std::endl;
    std::cout << "minArea: " << minArea << std::endl;

    vtkSmartPointer<vtkPolyDataMapper> originMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    originMapper->SetInputData(cubeSource->GetOutput());

    vtkSmartPointer<vtkActor> originActor=vtkSmartPointer<vtkActor>::New();
    originActor->SetMapper(originMapper);
    originActor->GetProperty()->SetColor(1.0, 0.0, 0.0);
    originActor->GetProperty()->SetEdgeColor(0.0, 1.0, 0.0);
    originActor->GetProperty()->SetEdgeVisibility(1);

    vtkSmartPointer<vtkPolyDataMapper> targetMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    targetMapper->SetInputConnection(triFilter->GetOutputPort());

    vtkSmartPointer<vtkActor> targetActor = vtkSmartPointer<vtkActor>::New();
    targetActor->SetMapper(targetMapper);
    targetActor->GetProperty()->SetColor(0, 1, 0);
    targetActor->GetProperty()->SetEdgeColor(1, 0, 0);
    targetActor->GetProperty()->SetEdgeVisibility(1);


    double left [4]={0.0,0.0,0.5,1.0};
    double right [4]={0.5,0.0,1.0,1.0};

    vtkSmartPointer<vtkRenderer> originRenderer = vtkSmartPointer<vtkRenderer>::New();
    originRenderer->AddActor(originActor);
    originRenderer->SetBackground(1.0, 1.0, 1.0);
    originRenderer->SetViewport(left);

    vtkSmartPointer<vtkRenderer> targetRenderer = vtkSmartPointer<vtkRenderer>::New();
    targetRenderer->AddActor(targetActor);
    targetRenderer->SetBackground(1.0, 1.0, 1.0);
    targetRenderer->SetViewport(right);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(originRenderer);
    renderWindow->AddRenderer(targetRenderer);
    renderWindow->SetWindowName("PolyDataMapper Mass Property");

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
    return 0;
}
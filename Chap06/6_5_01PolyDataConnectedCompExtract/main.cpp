#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkConeSource.h>
#include <vtkAppendPolyData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataConnectivityFilter.h>

int main(int argc, char *argv[])
{
    vtkSmartPointer<vtkSphereSource> sphereSource =
        vtkSmartPointer<vtkSphereSource>::New();

    sphereSource->SetRadius(10);
    sphereSource->SetThetaResolution(10);
    sphereSource->SetPhiResolution(10);
    sphereSource->Update();

    vtkSmartPointer<vtkConeSource> coneSource =
        vtkSmartPointer<vtkConeSource>::New();

    coneSource->SetRadius(5);
    coneSource->SetHeight(10);
    coneSource->SetCenter(25, 0, 0);
    coneSource->Update();

    vtkSmartPointer<vtkAppendPolyData> appendFilter = vtkSmartPointer<vtkAppendPolyData>::New();

    appendFilter->AddInputData(sphereSource->GetOutput());
    appendFilter->AddInputData(coneSource->GetOutput());
    appendFilter->Update();

    vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter = vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();

    connectivityFilter->SetInputData(appendFilter->GetOutput());
    // 提取最大连通区域
    connectivityFilter->SetExtractionModeToLargestRegion();
    // 连通区域标记，配合ColorRegionOn(),生成一个名为RegionId的点属性数据
    //  connectivityFilter->SetExtractionModeToSpecifiedRegions();
    // 提取一个或者多个连通区域，通过AddSpecifiedRegion()方法添加多个区域号吃
    //  connectivityFilter->SetExtractionModeToSpecifiedRegions();
    //  connectivityFilter->AddSpecifiedRegion(0);
    connectivityFilter->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(connectivityFilter->GetOutput());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(1, 1, 1);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(600, 600);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
    return 0;
}
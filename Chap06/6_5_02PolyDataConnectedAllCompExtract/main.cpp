#include <vtkPolyDataWriter.h>
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
    // 获取所有的连通区域
    connectivityFilter->SetExtractionModeToAllRegions();
    connectivityFilter->Update();

    // 获取连通区域数量
    int regionNum = connectivityFilter->GetNumberOfExtractedRegions();

    for (size_t i = 0; i < regionNum; i++)
    {
        vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter2 = vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
        connectivityFilter2->SetInputData(appendFilter->GetOutput());
        connectivityFilter2->InitializeSpecifiedRegionList();
        connectivityFilter2->SetExtractionModeToSpecifiedRegions();
        connectivityFilter2->AddSpecifiedRegion(i);
        connectivityFilter2->Update();

        char str[256];
        sprintf(str, "region%d", i);
        strcat(str,".vtk");

        vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
        writer->SetFileName(str);
        writer->SetInputData(connectivityFilter2->GetOutput());
        writer->Update();
    }
    return 0;
}
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyData.h>
#include <vtkPLYReader.h>
#include <vtkDecimatePro.h>
#include <vtkQuadricDecimation.h>
#include <vtkQuadricClustering.h>
#include "AutoCom.h"
#include <chrono>
#include "timer.h"

int main(int argc, char *argv[])
{
    AutoCOM::Init();
    vtkSmartPointer<vtkPLYReader> reader = vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName("../datas/bunny.ply");
    reader->Update();


    //源数据
    vtkSmartPointer<vtkPolyDataMapper> originMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    originMapper->SetInputData(reader->GetOutput());
    vtkSmartPointer<vtkActor> originActor = vtkSmartPointer<vtkActor>::New();
    originActor->SetMapper(originMapper);


    vtkSmartPointer<vtkActor> decimateProActor = vtkSmartPointer<vtkActor>::New();
    // 边坍塌
    {
        timer t("vtkDecimatePro");
        vtkSmartPointer<vtkDecimatePro> decimateProFilter = vtkSmartPointer<vtkDecimatePro>::New();
        decimateProFilter->SetInputConnection(reader->GetOutputPort());
        // 减少的百分比
        decimateProFilter->SetTargetReduction(0.6);
        decimateProFilter->Update();

        vtkSmartPointer<vtkPolyDataMapper> decimateProMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        decimateProMapper->SetInputConnection(decimateProFilter->GetOutputPort());
        decimateProMapper->Update();
        decimateProActor->SetMapper(decimateProMapper);
    }

    // 面坍塌
    vtkSmartPointer<vtkActor> decimateActor = vtkSmartPointer<vtkActor>::New();
    {
        timer t("vtkQuadricDecimation");
        vtkSmartPointer<vtkQuadricDecimation> decimateFilter = vtkSmartPointer<vtkQuadricDecimation>::New();
        decimateFilter->SetInputConnection(reader->GetOutputPort());
        // 减少的百分比
        decimateFilter->SetTargetReduction(0.6);
        decimateFilter->Update();

        vtkSmartPointer<vtkPolyDataMapper> decimateMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        decimateMapper->SetInputConnection(decimateFilter->GetOutputPort());
        decimateMapper->Update();
        decimateActor->SetMapper(decimateMapper);
    }

    // 面坍塌
    vtkSmartPointer<vtkActor> clusteringActor = vtkSmartPointer<vtkActor>::New();
    {
        timer t("vtkQuadricClustering");
        vtkSmartPointer<vtkQuadricClustering> clusteringFilter = vtkSmartPointer<vtkQuadricClustering>::New();
        clusteringFilter->SetInputConnection(reader->GetOutputPort());
        clusteringFilter->SetNumberOfDivisions(10, 10, 10); // x, y, z方向的分区数
        clusteringFilter->Update();

        vtkSmartPointer<vtkPolyDataMapper> clusteringMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        clusteringMapper->SetInputConnection(clusteringFilter->GetOutputPort());
        clusteringMapper->Update();
        clusteringActor->SetMapper(clusteringMapper);
    }

    double originVP[4]={0.0,0.0,0.5,0.5};
    double decimateProVP[4]={0.5,0.0,1.0,0.5};
    double decimateVP[4]={0.0,0.5,0.5,1.0};
    double clusteringVP[4]={0.5,0.5,1.0,1.0};

    vtkSmartPointer<vtkRenderer> originRenderer=vtkSmartPointer<vtkRenderer>::New();
    originRenderer->AddActor(originActor);
    originRenderer->SetViewport(originVP);
    originRenderer->SetBackground(1,1,1);

    vtkSmartPointer<vtkRenderer> decimateProRenderer=vtkSmartPointer<vtkRenderer>::New();
    decimateProRenderer->AddActor(decimateProActor);
    decimateProRenderer->SetViewport(decimateProVP);
    decimateProRenderer->SetBackground(1,1,1);

    vtkSmartPointer<vtkRenderer> decimateRenderer=vtkSmartPointer<vtkRenderer>::New();
    decimateRenderer->AddActor(decimateActor);
    decimateRenderer->SetViewport(decimateVP);
    decimateRenderer->SetBackground(1,1,1);

    vtkSmartPointer<vtkRenderer> clusteringRenderer=vtkSmartPointer<vtkRenderer>::New();
    clusteringRenderer->AddActor(clusteringActor);
    clusteringRenderer->SetViewport(clusteringVP);
    clusteringRenderer->SetBackground(1,1,1);

    vtkSmartPointer<vtkRenderWindow> renderWindow=vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(originRenderer);
    renderWindow->AddRenderer(decimateProRenderer);
    renderWindow->AddRenderer(decimateRenderer);
    renderWindow->AddRenderer(clusteringRenderer);
    renderWindow->SetSize(800,800);

    vtkSmartPointer<vtkRenderWindowInteractor> interactor=vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);
    interactor->Initialize();
    renderWindow->Render();
    interactor->Start();



    

}

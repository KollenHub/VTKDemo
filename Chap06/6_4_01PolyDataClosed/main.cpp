#include <iostream>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPolyData.h>
#include <vtkPolyDataNormals.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSelection.h>
#include <vtkSelectionNode.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkIdTypeArray.h>
#include <vtkExtractSelection.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkFeatureEdges.h>
#include <vtkFillHolesFilter.h>
#include <vtkInformation.h>

void GenerateData(vtkSmartPointer<vtkPolyData> input)
{
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->Update();

    vtkSmartPointer<vtkIdTypeArray> ids = vtkSmartPointer<vtkIdTypeArray>::New();

    ids->SetNumberOfComponents(1);
    ids->InsertNextValue(2);
    ids->InsertNextValue(10);

    vtkSmartPointer<vtkSelectionNode> selectionNode = vtkSmartPointer<vtkSelectionNode>::New();
    selectionNode->SetFieldType(vtkSelectionNode::CELL);
    selectionNode->SetContentType(vtkSelectionNode::INDICES);
    selectionNode->SetSelectionList(ids);
    selectionNode->GetProperties()->Set(vtkSelectionNode::INVERSE(), 1);

    vtkSmartPointer<vtkSelection> selection = vtkSmartPointer<vtkSelection>::New();
    selection->AddNode(selectionNode);

    vtkSmartPointer<vtkExtractSelection> extractSelection = vtkSmartPointer<vtkExtractSelection>::New();
    extractSelection->SetInputData(0, sphereSource->GetOutput());
    extractSelection->SetInputData(1, selection);
    extractSelection->Update();

    vtkSmartPointer<vtkDataSetSurfaceFilter> surfaceFilter = vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
    surfaceFilter->SetInputConnection(extractSelection->GetOutputPort());
    surfaceFilter->Update();

    input->ShallowCopy(surfaceFilter->GetOutput());
}

int main(int argc, char *argv[])
{

    vtkSmartPointer<vtkPolyData> input = vtkSmartPointer<vtkPolyData>::New();
    GenerateData(input);

    vtkSmartPointer<vtkFeatureEdges> featureEdges = vtkSmartPointer<vtkFeatureEdges>::New();
    featureEdges->SetInputData(input);
    featureEdges->BoundaryEdgesOn();
    featureEdges->FeatureEdgesOff();
    featureEdges->ManifoldEdgesOff();
    featureEdges->NonManifoldEdgesOff();
    featureEdges->Update();

    int numberOfOpenEdges = featureEdges->GetOutput()->GetNumberOfCells();
    if (numberOfOpenEdges)
    {
        std::cout << "Number of open edges: " << numberOfOpenEdges << std::endl;
    }
    else
    {
        std::cout << "No open edges" << std::endl;
        return 0;
    }

    vtkSmartPointer<vtkFillHolesFilter> fillHolesFilter = vtkSmartPointer<vtkFillHolesFilter>::New();
    fillHolesFilter->SetInputData(input);
    fillHolesFilter->Update();

    vtkSmartPointer<vtkPolyDataNormals> normals = vtkSmartPointer<vtkPolyDataNormals>::New();
    normals->SetInputConnection(fillHolesFilter->GetOutputPort());
    normals->ConsistencyOn();
    normals->SplittingOff();
    normals->Update();

    double left[4] = {0.0, 0.0, 0.5, 1.0};
    double right[4] = {0.5, 0.0, 1.0, 1.0};

    vtkSmartPointer<vtkPolyDataMapper>
        originMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    originMapper->SetInputData(input);
    originMapper->Update();

    vtkSmartPointer<vtkProperty> backfaceProp =
        vtkSmartPointer<vtkProperty>::New();
    backfaceProp->SetDiffuseColor(0.89, 0.81, 0.34);

    vtkSmartPointer<vtkActor> originActor = vtkSmartPointer<vtkActor>::New();
    originActor->SetMapper(originMapper);
    originActor->SetBackfaceProperty(backfaceProp);
    originActor->GetProperty()->SetDiffuseColor(1.0, 0.3882, 0.2784);

    //设置缺口actor
    vtkSmartPointer<vtkPolyDataMapper> edgeMapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    edgeMapper->SetInputData(featureEdges->GetOutput());
    vtkSmartPointer<vtkActor> edgeActor =
        vtkSmartPointer<vtkActor>::New();
    edgeActor->SetMapper(edgeMapper);
    edgeActor->GetProperty()->SetEdgeColor(0., 0., 1.0);
    edgeActor->GetProperty()->SetEdgeVisibility(1);
    edgeActor->GetProperty()->SetLineWidth(5);

    vtkSmartPointer<vtkRenderer> originRenderer = vtkSmartPointer<vtkRenderer>::New();
    originRenderer->SetViewport(left);
    originRenderer->AddActor(originActor);
    originRenderer->AddActor(edgeActor);

    vtkSmartPointer<vtkPolyDataMapper>
        targetMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    targetMapper->SetInputData(normals->GetOutput());
    targetMapper->Update();

    vtkSmartPointer<vtkActor> targetActor = vtkSmartPointer<vtkActor>::New();
    targetActor->SetMapper(targetMapper);
    targetActor->GetProperty()->SetEdgeColor(0., 0., 1.0);
    targetActor->GetProperty()->SetEdgeVisibility(1);
    targetActor->GetProperty()->SetLineWidth(5);
    targetActor->GetProperty()->SetDiffuseColor(1.0, 0.3882, 0.2784);

    vtkSmartPointer<vtkRenderer> targetRenderer = vtkSmartPointer<vtkRenderer>::New();
    targetRenderer->SetViewport(right);
    targetRenderer->AddActor(targetActor);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(originRenderer);
    renderWindow->AddRenderer(targetRenderer);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

    return 0;
}
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkPoints.h>
#include <vtkPolygon.h>
#include <vtkTriangle.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkUnsignedCharArray.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
int main()
{

    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(0, 0, 0);
    points->InsertNextPoint(1, 0, 0);
    points->InsertNextPoint(1, 1.0, 0);
    points->InsertNextPoint(0, 1.0, 0);
    points->InsertNextPoint(2.0, 0.0, 0.0);

    vtkSmartPointer<vtkPolygon> polygon = vtkSmartPointer<vtkPolygon>::New();

    polygon->GetPointIds()->SetNumberOfIds(4);
    polygon->GetPointIds()->SetId(0, 0);
    polygon->GetPointIds()->SetId(1, 1);
    polygon->GetPointIds()->SetId(2, 2);
    polygon->GetPointIds()->SetId(3, 3);

    vtkSmartPointer<vtkTriangle> triangle = vtkSmartPointer<vtkTriangle>::New();
    triangle->GetPointIds()->SetId(0, 1);
    triangle->GetPointIds()->SetId(1, 2);
    triangle->GetPointIds()->SetId(2, 4);

    vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
    cells->InsertNextCell(triangle);
    cells->InsertNextCell(polygon);

    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points);
    polydata->SetPolys(cells);


    //颜色
    unsigned char red[3] = {255, 0, 0};
    unsigned char green[3]={0,255,0};
    unsigned char blue[3]={0,0,255};

    //点颜色和单元颜色取其一，不然是顶点颜色渲染优先
    //点颜色
    vtkSmartPointer<vtkUnsignedCharArray> pointColors=vtkSmartPointer<vtkUnsignedCharArray>::New();
    pointColors->SetNumberOfComponents(3);
    pointColors->InsertNextTypedTuple(red);
    pointColors->InsertNextTypedTuple(green);
    pointColors->InsertNextTypedTuple(blue);
    pointColors->InsertNextTypedTuple(green);
    pointColors->InsertNextTypedTuple(red);
    polydata->GetPointData()->SetScalars(pointColors);

    //单元颜色
    vtkSmartPointer<vtkUnsignedCharArray> cellColors=vtkSmartPointer<vtkUnsignedCharArray>::New();
    cellColors->SetNumberOfComponents(3);
    cellColors->InsertNextTypedTuple(red);
    cellColors->InsertNextTypedTuple(green);
    polydata->GetCellData()->SetScalars(cellColors);


    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polydata);
    mapper->Update();

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(0, 0, 0);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

    return 0;
}
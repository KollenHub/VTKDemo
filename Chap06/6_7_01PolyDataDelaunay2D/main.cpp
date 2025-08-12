
#include <vtkProperty.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDelaunay2D.h>
#include <vtkMath.h>

int main(int argc, char *argv[])
{
    // Setup points
    vtkSmartPointer<vtkPoints> points =
        vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(0.0, 0.0, 0.0);    // 左下角
    points->InsertNextPoint(3.0, 0.0, 0.0);    // 右下角
    points->InsertNextPoint(3.0, 1.0, 0.0);    // 右上角
    points->InsertNextPoint(2.0, 1.0, 0.0);    // 右上凹点
    points->InsertNextPoint(2.0, 2.0, 0.0);    // 右中上
    points->InsertNextPoint(3.0, 2.0, 0.0);    // 右上角
    points->InsertNextPoint(3.0, 3.0, 0.0);    // 最右上角
    points->InsertNextPoint(0.0, 3.0, 0.0);    // 左上角
    
    // 内凹部分 (顺时针方向)
    points->InsertNextPoint(0.0, 2.0, 0.0);    // 左中上
    points->InsertNextPoint(1.0, 2.0, 0.0);    // 中上
    points->InsertNextPoint(1.0, 1.0, 0.0);    // 中凹点
    points->InsertNextPoint(0.0, 1.0, 0.0);    // 左中下


    // unsigned int gridSize = 10;
    // for (size_t x = 0; x < gridSize; x++)
    // {
    //     for (size_t y = 0; y < gridSize; y++)
    //     {
    //         points->InsertNextPoint(x, y, vtkMath::Random(0.0, 3.0));
    //     }
    // }

    vtkSmartPointer<vtkPolyData> polydata =
        vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points);

    vtkSmartPointer<vtkDelaunay2D> delaunay =
        vtkSmartPointer<vtkDelaunay2D>::New();

    delaunay->SetInputData(polydata);
    delaunay->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(delaunay->GetOutputPort());

    vtkSmartPointer<vtkActor> actor =
        vtkSmartPointer<vtkActor>::New();

    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(1.0, 0.0, 0.0);

    vtkSmartPointer<vtkRenderer> renderer =
        vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(600, 600);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

    return 0;
}
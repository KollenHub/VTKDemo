
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
#include <vtkPolygon.h>

int main(int argc, char *argv[])
{
    // Setup points
    vtkSmartPointer<vtkPoints> points =
        vtkSmartPointer<vtkPoints>::New();

    unsigned int gridSize = 10;
    for (size_t x = 0; x < gridSize; x++)
    {
        for (size_t y = 0; y < gridSize; y++)
        {
            points->InsertNextPoint(x, y, vtkMath::Random(0.0, 3.0));
        }
    }


    //顺时针扣洞，逆时针扣出来
    std::vector<int> boundaryPts={0,1,2,3,4,5,6,7,17,27,37,47,46,45,35,25,24,23,22,21,20,10};

    //下移一行，右一格
    for (size_t i = 0; i < boundaryPts.size(); i++)
    {
        boundaryPts[i]+=11;
    }

    //反转
    // std::reverse(boundaryPts.begin(),boundaryPts.end());



    // 设置边界
    vtkSmartPointer<vtkPolygon> poly = vtkSmartPointer<vtkPolygon>::New();
    //必须要顺序连接，无法跨越，顺时针扣洞
    for(auto i:boundaryPts)
    {
        poly->GetPointIds()->InsertNextId(i);
    }
    vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
    cells->InsertNextCell(poly);

    vtkSmartPointer<vtkPolyData> boundary = vtkSmartPointer<vtkPolyData>::New();
    boundary->SetPoints(points);
    boundary->SetPolys(cells);

    vtkSmartPointer<vtkPolyData> polydata =
        vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points);

    vtkSmartPointer<vtkDelaunay2D> delaunay =
        vtkSmartPointer<vtkDelaunay2D>::New();
    delaunay->SetInputData(polydata);
    delaunay->SetSourceData(boundary);
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
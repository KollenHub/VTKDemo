#include <vtkSmartPointer.h>
#include <vtkPlaneSource.h>
#include <vtkPolyData.h>
#include <vtkFloatArray.h>
#include <vtkLookupTable.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCellData.h>
#include <vtkPointData.h>

int main(int, char *[])
{

    vtkSmartPointer<vtkPlaneSource> gridSource = vtkSmartPointer<vtkPlaneSource>::New();

    gridSource->SetXResolution(3);
    gridSource->SetYResolution(3);
    gridSource->Update();

    vtkSmartPointer<vtkPolyData> grid = gridSource->GetOutput();
    vtkSmartPointer<vtkFloatArray> cellScalars = vtkSmartPointer<vtkFloatArray>::New();
    vtkSmartPointer<vtkFloatArray> cellVectors = vtkSmartPointer<vtkFloatArray>::New();
    cellVectors->SetNumberOfComponents(3);

    for (size_t i = 0; i < 9; i++)
    {
        cellScalars->InsertNextValue(i + 1);
        cellVectors->InsertNextTuple3(0.0, 0.0, 1.0);
    }

    grid->GetCellData()->SetScalars(cellScalars);
    grid->GetCellData()->SetVectors(cellVectors);

    vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
    lut->SetNumberOfTableValues(10);
    lut->Build();
    lut->SetTableValue(0, 0, 0, 0, 1);
    lut->SetTableValue(1, 0.8900, 0.8100, 0.3400, 1);
    lut->SetTableValue(2, 1.0000, 0.3882, 0.2784, 1);
    lut->SetTableValue(3, 0.9608, 0.8706, 0.7020, 1);
    lut->SetTableValue(4, 0.9020, 0.9020, 0.9804, 1);
    lut->SetTableValue(5, 1.0000, 0.4900, 0.2500, 1);
    lut->SetTableValue(6, 0.5300, 0.1500, 0.3400, 1);
    lut->SetTableValue(7, 0.9804, 0.5020, 0.4471, 1);
    lut->SetTableValue(8, 0.7400, 0.9900, 0.7900, 1);
    lut->SetTableValue(9, 0.0, 1.0, 0.0, 1);

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(grid);
    //设置标量最大值和最小值，超过这个值会被映射为最大值
    mapper->SetScalarRange(0, 9);
    
    //设置颜色表
    mapper->SetLookupTable(lut);
    //设置的是cell-data
    mapper->SetScalarModeToUseCellData();
    
    // SetScalarModeToDefault(); //默认设置，线使用点标量数据，再考虑单元数据
    // SetScalarModeToUsePointData(); //只考虑使用点标量数据
    // SetScalarModeToUseCellData(); //只考虑使用单元标量数据
    // SetScalarModeToUsePointFieldData(); //使用点属性数据
    // SetScalarModeToUseCellFieldData(); //使用单元属性数据


    //使用点属性数据，
    //TODO:其实需要检查一下点标量数据怎么设置
    vtkSmartPointer<vtkIntArray> pointField= vtkSmartPointer<vtkIntArray>::New();
    pointField->SetName("Field");
    pointField->SetNumberOfComponents(3);
    pointField->InsertNextTuple3(1,0,0);
    pointField->InsertNextTuple3(2,0,0);
    pointField->InsertNextTuple3(3,0,0);
    pointField->InsertNextTuple3(4,0,0);
    pointField->InsertNextTuple3(5,0,0);

    // grid->GetPointData()->SetScalars(pointField);
    // mapper->SetScalarModeToUsePointFieldData();
    // mapper->SelectColorArray("Field");

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

    return EXIT_SUCCESS;
}
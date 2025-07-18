#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>


int main()
{
   //创建点集数据:包含两个坐标点
   vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

   points->InsertNextPoint(0.0, 0.0, 0.0);
   points->InsertNextPoint(1.0, 0.0, 0.0);

   //创建多边形数据
   vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
   polydata->SetPoints(points);

   //准备加入点数据的标量值，两个标量值分别为1和2
   vtkSmartPointer<vtkDoubleArray> scalars = vtkSmartPointer<vtkDoubleArray>::New();
   scalars->SetNumberOfValues(2);
   scalars->SetValue(0, 1.0);
   scalars->SetValue(1, 2.0);

   //先获取多边形数据的点数据指针，然后设置该点数据的标量属性值 
   polydata->GetPointData()->SetScalars(scalars);

   //输出索引号为0的点的标量值
   double scalar1=vtkDoubleArray::SafeDownCast(polydata->GetPointData()->GetScalars())->GetValue(0);

   std::cout<< "double scalar1: "<<scalar1<<std::endl;

   return 0;
}
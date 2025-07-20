#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtk3DSImporter.h>
#include <vtkRenderer.h>
int main()
{
   // 3DS Import
   vtkSmartPointer<vtk3DSImporter> importer = vtkSmartPointer<vtk3DSImporter>::New();
   importer->SetFileName("../datas/R8.3ds");
   //计算发现
   importer->ComputeNormalsOn();
   importer->Read();

   vtkSmartPointer<vtkRenderer> renderer=importer->GetRenderer();

   vtkSmartPointer<vtkRenderWindow> renderWindow = importer->GetRenderWindow();

   vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

   renderWindowInteractor->SetRenderWindow(renderWindow);

   renderWindowInteractor->Initialize();
   renderWindowInteractor->Start();
   return 0;
}
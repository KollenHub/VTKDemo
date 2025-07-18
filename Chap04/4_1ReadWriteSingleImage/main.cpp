#include <vtkSmartPointer.h>
#include <vtkPNGReader.h>
#include <vtkImageViewer2.h>
#include <vtkRenderer.h>
#include <vtkJPEGWriter.h>
#include <vtkRenderWindowInteractor.h>

int main()
{
   vtkSmartPointer<vtkPNGReader> reader = vtkSmartPointer<vtkPNGReader>::New();

   reader->SetFileName("../datas/VTK-logo.png");

   // 宣誓读取的单幅PNG
   vtkSmartPointer<vtkImageViewer2> viewer = vtkSmartPointer<vtkImageViewer2>::New();

   viewer->SetInputConnection(reader->GetOutputPort());

   vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

   viewer->SetupInteractor(renderWindowInteractor);

   viewer->Render();
   viewer->GetRenderer()->ResetCamera();
   viewer->Render();


   //保存成JPG图像
   vtkSmartPointer<vtkJPEGWriter> writer = vtkSmartPointer<vtkJPEGWriter>::New();
   writer->SetFileName("output.jpg");
   writer->SetInputConnection(reader->GetOutputPort());
   writer->Write();

   return 0;
}
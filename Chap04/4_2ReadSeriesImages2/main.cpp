#include <vtkSmartPointer.h>
#include <vtkStringArray.h>
#include <vtkStdString.h>
#include <vtkJPEGReader.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>



int main()
{
   //读取 JPG 序列图像
   vtkSmartPointer<vtkJPEGReader> reader=vtkSmartPointer<vtkJPEGReader>::New();
   reader->SetFilePrefix("../datas/Head/head");
   reader->SetFilePattern("%s%03d.jpg");
   reader->SetDataExtent(0,255,0,255,1,100);
   reader->Update();

   //显示读取的JPG图像
   vtkSmartPointer<vtkImageViewer2> viewer=vtkSmartPointer<vtkImageViewer2>::New();
   viewer->SetInputConnection(reader->GetOutputPort());

   vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor=vtkSmartPointer<vtkRenderWindowInteractor>::New();
   viewer->SetupInteractor(renderWindowInteractor);

   viewer->SetSlice(50);
   viewer->SetSliceOrientationToXY();
   viewer->SetupInteractor(renderWindowInteractor);

   viewer->Render();

   renderWindowInteractor->Start();

   return 0;
}
#include <vtkSmartPointer.h>
#include <vtkStringArray.h>
#include <vtkStdString.h>
#include <vtkJPEGReader.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>



int main()
{
   //生成图像序列的文件名属猪
   vtkSmartPointer<vtkStringArray> fileArray=vtkSmartPointer<vtkStringArray>::New();
   char fileName[128];
   for(int i=0;i<100;i++)
   {
      sprintf(fileName,"../datas/Head/head%03d.jpg",i+1);
      fileArray->InsertNextValue(fileName);
   }

   //读取 JPG 序列图像
   vtkSmartPointer<vtkJPEGReader> reader=vtkSmartPointer<vtkJPEGReader>::New();
   reader->SetFileNames(fileArray);

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
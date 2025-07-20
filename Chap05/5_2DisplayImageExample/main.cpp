#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMetaImageReader.h>
#include <vtkImageViewer2.h>

int main()
{
	// 创建reader
	vtkSmartPointer<vtkMetaImageReader> reader = vtkSmartPointer<vtkMetaImageReader>::New();
	reader->SetFileName("../datas/head.mhd");
	reader->Update();

	vtkSmartPointer<vtkImageViewer2> imgViewer = vtkSmartPointer<vtkImageViewer2>::New();

	vtkSmartPointer<vtkRenderWindowInteractor> rwInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

	imgViewer->SetupInteractor(rwInteractor);

	imgViewer->SetInputConnection(reader->GetOutputPort());

	// 窗位
	imgViewer->SetColorLevel(500);

    //窗宽：图像显示的灰度范围，一般来说显示器灰度范围位256级，而医学图像的灰度
	//范围远远大于该范围，因此通过显示器显示时不能显示所有灰度级，需要用窗宽
	//来定义欲显示的灰度范围，当灰度值高于该范围的最大值是，均以白影显示，低于该值是以黑影显示
	imgViewer->SetColorWindow(2000);

	//最低可见度：Level-ColorWindow/2
	//最高可见度：Level+ColorWindow/2

    //切片索引
	imgViewer->SetSlice(40);

    //切片方向
	imgViewer->SetSliceOrientationToXY();

    //渲染
	imgViewer->Render();

	rwInteractor->Initialize();
	rwInteractor->Start();

	return 0;
}
#include <vtkSmartPointer.h>
#include <vtkBMPReader.h>
#include <vtkImageData.h>
#include <vtkImageChangeInformation.h>

int main()
{
	vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();

	reader->SetFileName("../datas/lena.bmp");

	reader->Update();

	int dims[3];
	reader->GetOutput()->GetDimensions(dims);

	std::cout << "图像维数" << dims[0] << " " << dims[1] << " " << dims[2] << std::endl;

	double origin[3];
	reader->GetOutput()->GetOrigin(origin);
	std::cout << "图像原点" << origin[0] << " " << origin[1] << " " << origin[2] << std::endl;

	double spacing[3];

	reader->GetOutput()->GetSpacing(spacing);
	std::cout << "像素间隔" << spacing[0] << " " << spacing[1] << " " << spacing[2] << std::endl;

	vtkSmartPointer<vtkImageChangeInformation> changer = vtkSmartPointer<vtkImageChangeInformation>::New();

	changer->SetInputData(reader->GetOutput());
	changer->SetOutputOrigin(100, 100, 0);
	changer->SetOutputSpacing(5, 5, 1);
	changer->SetCenterImage(1);
	changer->Update();

    
	changer->GetOutput()->GetDimensions(dims);

	std::cout << "图像维数" << dims[0] << " " << dims[1] << " " << dims[2] << std::endl;

     //结果为（-1277.5,-1277.5,0) 根据图像维数和像素间隔计算
	 //新图像的大小为(512-1)*5,而setcenterimage是移动到中心，所以是新图像一半的大小
	changer->GetOutput()->GetOrigin(origin);
	std::cout << "图像原点" << origin[0] << " " << origin[1] << " " << origin[2] << std::endl;

	changer->GetOutput()->GetSpacing(spacing);
	std::cout << "像素间隔" << spacing[0] << " " << spacing[1] << " " << spacing[2] << std::endl;

	return 0;
}
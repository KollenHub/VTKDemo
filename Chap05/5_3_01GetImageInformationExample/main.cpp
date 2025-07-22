#include <vtkSmartPointer.h>
#include <vtkBMPReader.h>
#include <vtkImageData.h>

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
	std::cout << "图像原点" << origin[0] << " " << origin[1] << " " << origin[2]<<std::endl;

	double spacing[3];

	reader->GetOutput()->GetSpacing(spacing);
	std::cout<<"像素间隔"<<spacing[0]<<" "<<spacing[1]<<" "<<spacing[2]<<std::endl;

	return 0;
}
#include <vtkSmartPointer.h>
#include <vtkBMPReader.h>
#include <vtkImageData.h>
#include <vtkImageChangeInformation.h>
#include <vtkImageActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageIterator.h>
#include <vtkImageLuminance.h>

int main()
{
	vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();

	reader->SetFileName("../datas/lena.bmp");

	reader->Update();

	// 彩色变灰度 ImagingColor模块
	vtkSmartPointer<vtkImageLuminance> luminanceFilter = vtkSmartPointer<vtkImageLuminance>::New();

	luminanceFilter->SetInputConnection(reader->GetOutputPort());

	luminanceFilter->Update();

	vtkSmartPointer<vtkImageActor> sourceImgActor = vtkSmartPointer<vtkImageActor>::New();
	sourceImgActor->SetInputData(reader->GetOutput());

	vtkSmartPointer<vtkImageActor> targetImgActor = vtkSmartPointer<vtkImageActor>::New();
	targetImgActor->SetInputData(luminanceFilter->GetOutput());

	// 视口
	double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
	double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

	// 渲染
	vtkSmartPointer<vtkRenderer> sourceRenderer = vtkSmartPointer<vtkRenderer>::New();
	sourceRenderer->SetViewport(leftViewport);
	sourceRenderer->AddActor(sourceImgActor);

	vtkSmartPointer<vtkRenderer> targetRenderer = vtkSmartPointer<vtkRenderer>::New();
	targetRenderer->SetViewport(rightViewport);
	targetRenderer->AddActor(targetImgActor);

	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

	vtkSmartPointer<vtkRenderWindowInteractor>
		rwInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

	vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();

	rwInteractor->SetInteractorStyle(style);

	renderWindow->SetInteractor(rwInteractor);

	renderWindow->AddRenderer(sourceRenderer);
	renderWindow->AddRenderer(targetRenderer);

	rwInteractor->Initialize();
	rwInteractor->Start();

	return 0;
}
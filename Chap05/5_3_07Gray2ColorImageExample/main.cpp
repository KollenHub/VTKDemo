#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkLookupTable.h>
#include <vtkImageMapToColors.h>

int main()
{
	vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();

	reader->SetFileName("../datas/lena-gray.jpg");

	reader->Update();

	vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();

	lut->SetTableRange(0, 255);
	lut->SetHueRange(0.1, 0.5);
	lut->SetValueRange(0.6, 1.0);
	lut->Build();

	vtkSmartPointer<vtkImageMapToColors> colorMap = vtkSmartPointer<vtkImageMapToColors>::New();
	colorMap->SetInputConnection(reader->GetOutputPort());
	colorMap->SetLookupTable(lut);
	colorMap->Update();

	vtkSmartPointer<vtkImageActor> sourceImgActor = vtkSmartPointer<vtkImageActor>::New();
	sourceImgActor->SetInputData(reader->GetOutput());

	vtkSmartPointer<vtkImageActor> targetImgActor = vtkSmartPointer<vtkImageActor>::New();
	targetImgActor->SetInputData(colorMap->GetOutput());

	// 视口
	double originViewport[4] = {0.0, 0.0, 0.5, 1.0};
	double targetViewport[4] = {0.5, 0.0, 1.0, 1.0};

	// 渲染
	vtkSmartPointer<vtkRenderer> sourceRenderer = vtkSmartPointer<vtkRenderer>::New();
	sourceRenderer->SetViewport(originViewport);
	sourceRenderer->AddActor(sourceImgActor);

	vtkSmartPointer<vtkRenderer> targetRenderer = vtkSmartPointer<vtkRenderer>::New();
	targetRenderer->SetViewport(targetViewport);
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
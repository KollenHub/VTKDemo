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
#include <vtkImageExtractComponents.h>

int main()
{
	vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();

	reader->SetFileName("../datas/lena.bmp");

	reader->Update();

	// 提取红绿蓝
	vtkSmartPointer<vtkImageExtractComponents> extractRedFilter = vtkSmartPointer<vtkImageExtractComponents>::New();
	extractRedFilter->SetInputConnection(reader->GetOutputPort());
	extractRedFilter->SetComponents(0);
	extractRedFilter->Update();

	vtkSmartPointer<vtkImageExtractComponents> extractGreenFilter = vtkSmartPointer<vtkImageExtractComponents>::New();
	extractGreenFilter->SetInputConnection(reader->GetOutputPort());
	extractGreenFilter->SetComponents(1);
	extractGreenFilter->Update();

	vtkSmartPointer<vtkImageExtractComponents> extractBlueFilter = vtkSmartPointer<vtkImageExtractComponents>::New();
	extractBlueFilter->SetInputConnection(reader->GetOutputPort());
	extractBlueFilter->SetComponents(2);
	extractBlueFilter->Update();

	vtkSmartPointer<vtkImageActor> sourceImgActor = vtkSmartPointer<vtkImageActor>::New();
	sourceImgActor->SetInputData(reader->GetOutput());

	vtkSmartPointer<vtkImageActor> redImgActor = vtkSmartPointer<vtkImageActor>::New();
	redImgActor->SetInputData(extractRedFilter->GetOutput());

	vtkSmartPointer<vtkImageActor> greenImgActor = vtkSmartPointer<vtkImageActor>::New();
	greenImgActor->SetInputData(extractGreenFilter->GetOutput());

	vtkSmartPointer<vtkImageActor> blueImgActor = vtkSmartPointer<vtkImageActor>::New();
	blueImgActor->SetInputData(extractBlueFilter->GetOutput());

	// 视口
	double originViewport[4] = {0.0, 0.0, 0.25, 1.0};
	double redViewport[4] = {0.25, 0.0, 0.5, 1.0};
	double greenViewport[4] = {0.5, 0.0, 0.75, 1.0};
	double blueViewport[4] = {0.75, 0.0, 1.0, 1.0};

	// 渲染
	vtkSmartPointer<vtkRenderer> sourceRenderer = vtkSmartPointer<vtkRenderer>::New();
	sourceRenderer->SetViewport(originViewport);
	sourceRenderer->AddActor(sourceImgActor);

	vtkSmartPointer<vtkRenderer> redRenderer = vtkSmartPointer<vtkRenderer>::New();
	redRenderer->SetViewport(redViewport);
	redRenderer->AddActor(redImgActor);

vtkSmartPointer<vtkRenderer> greenRenderer = vtkSmartPointer<vtkRenderer>::New();
	greenRenderer->SetViewport(greenViewport);
	greenRenderer->AddActor(greenImgActor);

	vtkSmartPointer<vtkRenderer> blueRenderer = vtkSmartPointer<vtkRenderer>::New();
	blueRenderer->SetViewport(blueViewport);
	blueRenderer->AddActor(blueImgActor);


	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

	vtkSmartPointer<vtkRenderWindowInteractor>
		rwInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

	vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();

	rwInteractor->SetInteractorStyle(style);

	renderWindow->SetInteractor(rwInteractor);

	renderWindow->AddRenderer(sourceRenderer);
	renderWindow->AddRenderer(redRenderer);
	renderWindow->AddRenderer(greenRenderer);
	renderWindow->AddRenderer(blueRenderer);

	rwInteractor->Initialize();
	rwInteractor->Start();

	return 0;
}
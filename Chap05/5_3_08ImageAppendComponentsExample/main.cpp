#include <vtkSmartPointer.h>
#include <vtkImageActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageAppendComponents.h>

int main()
{
	//红
	vtkSmartPointer<vtkImageCanvasSource2D> red = vtkSmartPointer<vtkImageCanvasSource2D>::New();
	red->SetScalarTypeToUnsignedChar();
	red->SetNumberOfScalarComponents(1);
	red->SetExtent(0, 100, 0,100, 0, 0);
	red->FillBox(0,100,0,100);
	red->SetDrawColor(255,0,0);
	red->FillBox(20,40,20,40);
	red->Update();

	//绿
	vtkSmartPointer<vtkImageCanvasSource2D> green = vtkSmartPointer<vtkImageCanvasSource2D>::New();
	green->SetScalarTypeToUnsignedChar();
	green->SetNumberOfScalarComponents(1);
	green->SetExtent(0, 100, 0,100, 0, 0);
	green->FillBox(0,100,0,100);
	green->SetDrawColor(0,255,0);
	green->FillBox(30,50,30,50);
	green->Update();

	//蓝
	vtkSmartPointer<vtkImageCanvasSource2D> blue = vtkSmartPointer<vtkImageCanvasSource2D>::New();
	blue->SetScalarTypeToUnsignedChar();
	blue->SetNumberOfScalarComponents(1);
	blue->SetExtent(0, 100, 0,100, 0, 0);
	blue->FillBox(0,100,0,100);
	blue->SetDrawColor(0,255,0);
	blue->FillBox(30,50,30,50);
	blue->Update();

	vtkSmartPointer<vtkImageAppendComponents> appendFilter = vtkSmartPointer<vtkImageAppendComponents>::New();
	appendFilter->AddInputConnection(red->GetOutputPort());
	appendFilter->AddInputConnection(green->GetOutputPort());
	appendFilter->AddInputConnection(blue->GetOutputPort());
	appendFilter->Update();

	vtkSmartPointer<vtkImageActor> targetImgActor = vtkSmartPointer<vtkImageActor>::New();
	targetImgActor->SetInputData(appendFilter->GetOutput());

	vtkSmartPointer<vtkImageActor> redImgActor = vtkSmartPointer<vtkImageActor>::New();
	redImgActor->SetInputData(red->GetOutput());

	vtkSmartPointer<vtkImageActor> greenImgActor = vtkSmartPointer<vtkImageActor>::New();
	greenImgActor->SetInputData(green->GetOutput());

	vtkSmartPointer<vtkImageActor> blueImgActor = vtkSmartPointer<vtkImageActor>::New();
	blueImgActor->SetInputData(blue->GetOutput());

	// 视口
	double originViewport[4] = {0.0, 0.0, 0.25, 1.0};
	double redViewport[4] = {0.25, 0.0, 0.5, 1.0};
	double greenViewport[4] = {0.5, 0.0, 0.75, 1.0};
	double blueViewport[4] = {0.75, 0.0, 1.0, 1.0};

	// 渲染
	vtkSmartPointer<vtkRenderer> sourceRenderer = vtkSmartPointer<vtkRenderer>::New();
	sourceRenderer->SetViewport(originViewport);
	sourceRenderer->AddActor(targetImgActor);

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
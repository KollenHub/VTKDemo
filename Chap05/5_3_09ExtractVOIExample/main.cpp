#include <vtkSmartPointer.h>
#include <vtkBMPReader.h>
#include <vtkImageActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageAppendComponents.h>
#include <vtkExtractVOI.h>
#include <vtkImageData.h>

int main()
{

	vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();
	reader->SetFileName("../datas/lena.bmp");
	reader->Update();

	// 维数
	int dims[3];
	reader->GetOutput()->GetDimensions(dims);

	vtkSmartPointer<vtkExtractVOI> extractVOI = vtkSmartPointer<vtkExtractVOI>::New();
	extractVOI->SetInputConnection(reader->GetOutputPort());
	// 区域大小,角点为左下角
	extractVOI->SetVOI(dims[0]/4, 3 * dims[0] / 4, dims[0]/4, 3 * dims[1] / 4, 0, 0);
	extractVOI->Update();

	vtkSmartPointer<vtkImageActor> sourceImgActor = vtkSmartPointer<vtkImageActor>::New();
	sourceImgActor->SetInputData(reader->GetOutput());

	vtkSmartPointer<vtkImageActor> targetImgActor = vtkSmartPointer<vtkImageActor>::New();
	targetImgActor->SetInputData(extractVOI->GetOutput());

	// 视口
	double sourceViewport[4] = {0.0, 0.0, 0.5, 1.0};
	double targetViewport[4] = {0.5, 0.0, 1.0, 1.0};

	// 渲染
	vtkSmartPointer<vtkRenderer> sourceRenderer = vtkSmartPointer<vtkRenderer>::New();
	sourceRenderer->SetViewport(sourceViewport);
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
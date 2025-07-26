#include <vtkSmartPointer.h>
#include <vtkImageActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageAppendComponents.h>
#include <vtkExtractVOI.h>
#include <vtkImageData.h>
#include <vtkMetaImageReader.h>
#include <vtkMatrix4x4.h>
#include <vtkImageReslice.h>
#include "vtkImageInteractionCallback.hpp"

int main()
{

	vtkSmartPointer<vtkMetaImageReader> reader = vtkSmartPointer<vtkMetaImageReader>::New();
	reader->SetFileName("../datas/brain.mhd");
	reader->Update();

	int extent[6];
	double spacing[3];
	double origin[3];

	reader->GetOutput()->GetExtent(extent);
	reader->GetOutput()->GetSpacing(spacing);
	reader->GetOutput()->GetOrigin(origin);

	double center[3];
	center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
	center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
	center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);

	static double axialElements[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1};

	static double coronalElements[16] = {
		1, 0, 0, 0,
		0, 0, 1, 0,
		0, -1, 0, 0,
		0, 0, 0, 1}; // 提取平行于XZ平面的切片 标准的笛卡尔坐标系中，X轴正方向为右，Y轴正方向为后，Z轴正方向为上

	static double sagittalElements[16] = {
		0, 0, -1, 0,
		1, 0, 0, 0,
		0, -1, 0, 0,
		0, 0, 0, 1
	};//提取平行于YZ平面的切片 标准的笛卡尔坐标系中，X轴正方向为右，Y轴正方向为后，Z轴正方向为上
 
	vtkSmartPointer<vtkMatrix4x4>
		resliceAxes = vtkSmartPointer<vtkMatrix4x4>::New();
	resliceAxes->DeepCopy(axialElements);
	resliceAxes->SetElement(0, 3, center[0]);
	resliceAxes->SetElement(1, 3, center[1]);
	resliceAxes->SetElement(2, 3, center[2]);

	vtkSmartPointer<vtkImageReslice> reslice = vtkSmartPointer<vtkImageReslice>::New();
	reslice->SetInputConnection(reader->GetOutputPort());
	reslice->SetOutputDimensionality(2);
	reslice->SetResliceAxes(resliceAxes);
	reslice->SetInterpolationModeToLinear();
	reslice->Update();

	vtkSmartPointer<vtkImageActor> sourceImgActor = vtkSmartPointer<vtkImageActor>::New();
	sourceImgActor->SetInputData(reslice->GetOutput());

	// 渲染
	vtkSmartPointer<vtkRenderer> sourceRenderer = vtkSmartPointer<vtkRenderer>::New();
	sourceRenderer->AddActor(sourceImgActor);

	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

	vtkSmartPointer<vtkRenderWindowInteractor>
		rwInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

    
	vtkSmartPointer<vtkImageInteractionCallback> callback=vtkSmartPointer<vtkImageInteractionCallback>::New();
	callback->SetInteractor(rwInteractor);
	callback->SetImageReslice(reslice);

	vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();

	style->AddObserver(vtkCommand::MouseMoveEvent, callback);
	style->AddObserver(vtkCommand::LeftButtonPressEvent, callback);
	style->AddObserver(vtkCommand::LeftButtonReleaseEvent, callback);

	rwInteractor->SetInteractorStyle(style);
	renderWindow->SetInteractor(rwInteractor);

	renderWindow->AddRenderer(sourceRenderer);
	rwInteractor->Initialize();
	rwInteractor->Start();

	return 0;
}
#include <vtkArrowSource.h>
#include <vtkCylinderSource.h>
#include <vtkSphereSource.h>
#include <vtkConeSource.h>
#include <vtkLineSource.h>
#include <vtkCubeSource.h>
#include <vtkDiskSource.h>
#include <vtkPlaneSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAppendPolyData.h>
int main()
{

	// 椎体
	vtkSmartPointer<vtkConeSource> coneSource = vtkSmartPointer<vtkConeSource>::New();
	coneSource->SetCenter(10, 0, 0);
	coneSource->Update();

	// 箭头
	vtkSmartPointer<vtkArrowSource> arrowSource = vtkSmartPointer<vtkArrowSource>::New();
	arrowSource->SetArrowOriginToCenter();
	arrowSource->Update();

	// 圆柱
	vtkSmartPointer<vtkCylinderSource> cylinderSource = vtkSmartPointer<vtkCylinderSource>::New();
	cylinderSource->SetCenter(5, 0, 0);
	cylinderSource->Update();

	// 线
	vtkSmartPointer<vtkLineSource> lineSource = vtkSmartPointer<vtkLineSource>::New();
	lineSource->SetPoint1(7.5, -5, 0);
	lineSource->SetPoint2(10, -5, 0);
	lineSource->Update();

	// 立方体
	vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
	cubeSource->SetCenter(-5, 0, 0);
	cubeSource->Update();

	// 球体
	vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->SetCenter(-5, -5, 0);
	sphereSource->Update();

	// 环
	vtkSmartPointer<vtkDiskSource> diskSource = vtkSmartPointer<vtkDiskSource>::New();
	// diskSource->SetCenter(0, -5, 0);
	diskSource->Update();

	// 平面
	vtkSmartPointer<vtkPlaneSource> planeSource = vtkSmartPointer<vtkPlaneSource>::New();
	planeSource->SetCenter(5, -5, 0);
	planeSource->Update();

	vtkSmartPointer<vtkAppendPolyData> appendPolyData = vtkSmartPointer<vtkAppendPolyData>::New();

	appendPolyData->AddInputConnection(coneSource->GetOutputPort());
	;
	appendPolyData->AddInputConnection(arrowSource->GetOutputPort());
	appendPolyData->AddInputConnection(cylinderSource->GetOutputPort());
	appendPolyData->AddInputConnection(lineSource->GetOutputPort());
	appendPolyData->AddInputConnection(cubeSource->GetOutputPort());
	appendPolyData->AddInputConnection(sphereSource->GetOutputPort());
	appendPolyData->AddInputConnection(diskSource->GetOutputPort());
	appendPolyData->AddInputConnection(planeSource->GetOutputPort());
	appendPolyData->Update();

	// Mapper
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(appendPolyData->GetOutput());

	// Renderer
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(0, 0, 0);

	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	vtkSmartPointer<vtkRenderWindowInteractor> rwInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

	rwInteractor->SetRenderWindow(renderWindow);
	rwInteractor->Initialize();
	rwInteractor->Start();
	return 0;
}
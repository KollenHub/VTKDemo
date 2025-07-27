#include <vtkConeSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
int main()
{

	//Source
	vtkSmartPointer<vtkConeSource> coneSource = vtkSmartPointer<vtkConeSource>::New();
	coneSource->Update();

	vtkSmartPointer<vtkPolyData> cone = coneSource->GetOutput();

	int nPoints = cone->GetNumberOfPoints();
	int nCells = cone->GetNumberOfCells();

	std::cout << "Points Number:" << nPoints << std::endl;

	std::cout << "Cells Number:" << nCells << std::endl;

    //Mapper
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(cone);

    //Filter
    //......

    
	//Renderer
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(0, 0, 0);

	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	vtkSmartPointer<vtkRenderWindowInteractor> rwInteractor=vtkSmartPointer<vtkRenderWindowInteractor>::New();

	rwInteractor->SetRenderWindow(renderWindow);
	rwInteractor->Initialize();
	rwInteractor->Start();
	return 0;
}
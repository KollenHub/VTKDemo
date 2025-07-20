#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleImage.h>


int main()
{
   //创建canvas
   vtkSmartPointer<vtkImageCanvasSource2D> canvas=vtkSmartPointer<vtkImageCanvasSource2D>::New();

   //设置存储类型为unsigned char
   canvas->SetScalarTypeToUnsignedChar();

   canvas->SetNumberOfScalarComponents(1);
   canvas->SetExtent(0,100,0,100,0,0);
   canvas->SetDrawColor(0,0,0,0);
   canvas->FillBox(0,100,0,100);

   canvas->SetDrawColor(255,0,0,0);
   canvas->FillBox(20,40,20,40);
   canvas->Update();

    
	// Create actors
	vtkSmartPointer<vtkImageActor> redActor =
		vtkSmartPointer<vtkImageActor>::New();
	redActor->SetInputData(canvas->GetOutput());

	// Define viewport ranges
	// (xmin, ymin, xmax, ymax)
	double redViewport[4] = {0.0, 0.0, 1.0, 1.0};
	// Setup renderers
	vtkSmartPointer<vtkRenderer> redRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	redRenderer->SetViewport(redViewport);
	redRenderer->AddActor(redActor);
	redRenderer->ResetCamera();
	redRenderer->SetBackground(1.0, 1.0, 1.0);

	// Setup render window
	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(redRenderer);
	renderWindow->SetSize( 640, 480 );
	renderWindow->Render();
	renderWindow->SetWindowName("ImageCanvasSource2D");

	// Setup render window interactor
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkInteractorStyleImage> style =
		vtkSmartPointer<vtkInteractorStyleImage>::New();

	renderWindowInteractor->SetInteractorStyle(style);
	// Render and start interaction
	renderWindowInteractor->SetRenderWindow(renderWindow);
	renderWindowInteractor->Initialize();
	renderWindowInteractor->Start();

   return 0;
   
}
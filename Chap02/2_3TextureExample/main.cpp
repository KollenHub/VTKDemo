#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkLight.h>
#include <vtkCamera.h>
#include <vtkJPEGReader.h>
#include <vtkPlaneSource.h>
#include <vtkTexture.h>
int main()
{
  
   vtkSmartPointer<vtkJPEGReader> reader =
      vtkSmartPointer<vtkJPEGReader>::New();

    reader->SetFileName("../datas/texture1.jpg");

    vtkSmartPointer<vtkTexture> texture =
      vtkSmartPointer<vtkTexture>::New();
      texture->SetInputConnection(reader->GetOutputPort());

    vtkSmartPointer<vtkPlaneSource> plane =
      vtkSmartPointer<vtkPlaneSource>::New();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(plane->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();

  actor->SetMapper(mapper);
  actor->SetTexture(texture);

  vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();

  renderer->AddActor(actor);
  renderer->SetBackground(0.1, 0.2, 0.4);


  vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();

  renderWindow->AddRenderer(renderer);

  renderWindow->SetSize(300, 300);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();

  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
      vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

  iren->SetInteractorStyle(style);

  iren->SetRenderWindow(renderWindow);
  iren->Initialize();
  iren->Start();
  return 0;
}
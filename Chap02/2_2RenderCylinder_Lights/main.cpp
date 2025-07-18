#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkLight.h>
#include <vtkCamera.h>

int main()
{
  // 创建圆柱体
  vtkSmartPointer<vtkCylinderSource> cylinder =
      vtkSmartPointer<vtkCylinderSource>::New();

  cylinder->SetHeight(3.0);
  cylinder->SetRadius(1.0);
  cylinder->SetResolution(10);

  vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(cylinder->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();

  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();

  renderer->AddActor(actor);
  renderer->SetBackground(0.1, 0.2, 0.4);

  // 添加灯光
  vtkSmartPointer<vtkLight> light1 =
      vtkSmartPointer<vtkLight>::New();

  light1->SetColor(0, 1.0, 0);
  light1->SetPosition(0.0, 0.0, 1.0);
  light1->SetFocalPoint(renderer->GetActiveCamera()->GetFocalPoint());
  renderer->AddLight(light1);

  vtkSmartPointer<vtkLight> light2 =
      vtkSmartPointer<vtkLight>::New();
  light2->SetColor(0.0,0.0,1);
  light2->SetPosition(0.0, 0, -1);
  light2->SetFocalPoint(renderer->GetActiveCamera()->GetFocalPoint());
  renderer->AddLight(light2);
  

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
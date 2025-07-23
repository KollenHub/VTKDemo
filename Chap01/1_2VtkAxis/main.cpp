#include <vtkActor.h>
#include <vtkCameraOrientationWidget.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCylinderSource.h>
#include <vtkCubeSource.h>

int main(int argc, char* argv[])
{

  // 创建圆柱体
  vtkSmartPointer<vtkCylinderSource> cylinder =
      vtkSmartPointer<vtkCylinderSource>::New();
  cylinder->SetHeight(3.0);
  cylinder->SetRadius(1.0);
  cylinder->SetResolution(10);

  vtkNew<vtkCubeSource> box;
  box->SetCenter(20,20,0);
  box->SetXLength(20);
  box->SetYLength(10);
  box->SetZLength(5);

  vtkNew<vtkRenderer> renderer;
  vtkNew<vtkRenderWindow> renWin;
  vtkNew<vtkRenderWindowInteractor> iRen;

  vtkNew<vtkPolyDataMapper> mapper;
  mapper->AddInputConnection(cylinder->GetOutputPort());

  vtkNew<vtkPolyDataMapper> mapper2;
  mapper2->AddInputConnection(box->GetOutputPort());

  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);

    vtkNew<vtkActor> actor2;
  actor2->SetMapper(mapper2);

  renderer->AddActor(actor);
  renderer->AddActor(actor2);

  renWin->AddRenderer(renderer);
  renWin->SetSize(600, 600);
  renWin->SetWindowName("CameraOrientationWidget");

  // Important: The interactor must be set prior to enabling the widget.
  iRen->SetRenderWindow(renWin);

  vtkNew<vtkCameraOrientationWidget> camOrientManipulator;
  camOrientManipulator->SetParentRenderer(renderer);
  // Enable the widget.
  camOrientManipulator->On();

  renWin->Render();
  iRen->Initialize();
  iRen->Start();

  return EXIT_SUCCESS;
}
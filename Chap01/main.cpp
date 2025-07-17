#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>

int main()
{

  vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();

  renderWindow->Render();

  std::cin.get();

  return 0;
}
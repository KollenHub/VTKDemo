#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>

void DeepCopy(double destination[16], const double source[16])
{
  for (int i = 0; i < 16; i++)
  {
    destination[i] = source[i];
  }
}

int main()
{

  // vtkSmartPointer<vtkRenderWindow> renderWindow =
  //     vtkSmartPointer<vtkRenderWindow>::New();

  // renderWindow->Render();

  // std::cin.get();

  double elem[4][4];

  static double sagittalElements[16] = {
      0, 0, -1, 0,
      0, 1, 0, 0,
      1, 0, 0, 0,
      0, 0, 0, 1};

  DeepCopy(*elem, sagittalElements);

  for (size_t i = 0; i < 4; i++)
  {
    for (size_t j = 0; j < 4; j++)
    {
      std::cout << elem[i][j] << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
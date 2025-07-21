#include <vtkSmartPointer.h>
#include <vtkBMPReader.h>
#include <vtkImageData.h>
#include <vtkImageChangeInformation.h>
#include <vtkImageActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>

int main()
{
	vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();

	reader->SetFileName("../datas/lena.bmp");

	reader->Update();

	int dims[3];
	reader->GetOutput()->GetDimensions(dims);

	int numOfComp = reader->GetOutput()->GetNumberOfScalarComponents();

	for (size_t k = 0; k < dims[2]; k++)
	{
		for (size_t j = 0; j < dims[1]; j++)
		{
			for (size_t i = 0; i < dims[0]; i++)
			{
				double calValue= i*i+j*j;
				if (calValue<100000&&calValue>80000)
				{
					unsigned char *pixel = (unsigned char *)(reader->GetOutput()->GetScalarPointer(i, j, k));
					*pixel = 255;
					*(pixel + 1) = 0;
					*(pixel + 2) = 0;
				}
			}
		}
	}

	vtkSmartPointer<vtkImageActor> imgActor = vtkSmartPointer<vtkImageActor>::New();
	imgActor->SetInputData(reader->GetOutput());

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(imgActor);

	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

	vtkSmartPointer<vtkRenderWindowInteractor>
		rwInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

	vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();

	rwInteractor->SetInteractorStyle(style);

	renderWindow->SetInteractor(rwInteractor);

	renderWindow->AddRenderer(renderer);

	rwInteractor->Initialize();
	rwInteractor->Start();

	return 0;
}
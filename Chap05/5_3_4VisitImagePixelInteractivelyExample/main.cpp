#include <vtkSmartPointer.h>
#include <vtkBMPReader.h>
#include <vtkImageData.h>
#include <vtkImageChangeInformation.h>
#include <vtkImageActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageIterator.h>

int main()
{
	vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();

	reader->SetFileName("../datas/lena.bmp");

	reader->Update();

	// 定义子区域
	int subRegion[6] = {0, 300, 0, 300, 0, 0};
	vtkImageIterator<unsigned char> it(reader->GetOutput(), subRegion);

    
	while(!it.IsAtEnd())
	{
		unsigned char * inSI=it.BeginSpan();
		unsigned char * inSIEnd=it.EndSpan();
        //元组级别    
		while(inSI!=inSIEnd)
		{
			//Component级别
			//反转图像
			*inSI=255-(*inSI);
			++inSI;
		}
		it.NextSpan();
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
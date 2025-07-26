#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageData.h>
#include <vtkJPEGReader.h>
#include <vtkImageAccumulate.h>
#include <vtkIntArray.h>
#include <vtkFieldData.h>
#include <vtkBarChartActor.h>
#include <vtkProperty2D.h>
#include <vtkLegendBoxActor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindow.h>
int main()
{

	vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
	reader->SetFileName("../datas/lena-gray.jpg");
	reader->Update();

	int bins = 16;
	int comps = 1;

	vtkSmartPointer<vtkImageAccumulate> histogram = vtkSmartPointer<vtkImageAccumulate>::New();
	histogram->SetInputData(reader->GetOutput());
	histogram->SetComponentExtent(0, bins - 1, 0, 0, 0, 0);
	histogram->SetComponentSpacing(256.0 / bins, 0.0, 0.0);
	histogram->Update();

	int *output = static_cast<int *>(histogram->GetOutput()->GetScalarPointer());

	vtkSmartPointer<vtkIntArray> dataArray = vtkSmartPointer<vtkIntArray>::New();

	dataArray->SetNumberOfComponents(1);

	for (int i = 0; i < bins; i++)
	{

		for (int j = 0; j < comps; j++)
		{
			dataArray->InsertNextTuple1(*output++);
		}
	}

	vtkSmartPointer<vtkDataObject> dataObject=vtkSmartPointer<vtkDataObject>::New();

	dataObject->GetFieldData()->AddArray(dataArray);

	vtkSmartPointer<vtkBarChartActor> barChart = vtkSmartPointer<vtkBarChartActor>::New();

    barChart->SetInput(dataObject);
	barChart->SetTitle("Gray Level Histogram");
	barChart->GetPositionCoordinate()->SetValue(0.05, 0.05, 0.0);
	barChart->GetPosition2Coordinate()->SetValue(0.95, 0.95, 0.0);
	barChart->GetProperty()->SetColor(1,1,1);
	barChart->GetLegendActor()->SetNumberOfEntries(dataObject->GetFieldData()->GetArray(0)->GetNumberOfTuples());
	barChart->LegendVisibilityOff();
	barChart->LabelVisibilityOff();
	
	double colors[3][3]=
	{
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 1}
	};

	int count = 0;
	for(int i=0;i<bins;++i)
	{
		for (size_t j = 0; j < comps; j++)
		{
			barChart->SetBarColor(count++,colors[j]);
		}
		
	}

	// 渲染
	vtkSmartPointer<vtkRenderer> sourceRenderer = vtkSmartPointer<vtkRenderer>::New();
	sourceRenderer->AddActor(barChart);

	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

	vtkSmartPointer<vtkRenderWindowInteractor>
		rwInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

	vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();

	rwInteractor->SetInteractorStyle(style);
	renderWindow->SetInteractor(rwInteractor);

	renderWindow->AddRenderer(sourceRenderer);
	rwInteractor->Initialize();
	rwInteractor->Start();

	return 0;
}
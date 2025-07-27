#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleImage.h>
#include <vtkJPEGReader.h>
#include <vtkImageThreshold.h>

int main()
{
    // 读取图像文件
    vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
    reader->SetFileName("../datas/lena.jpg");

    vtkSmartPointer<vtkImageThreshold> thresholdFilter = vtkSmartPointer<vtkImageThreshold>::New();
    thresholdFilter->SetInputConnection(reader->GetOutputPort());
    //取大于200为有效值
    // thresholdFilter->ThresholdByUpper(200);
    //取小于200为有效值
    // thresholdFilter->ThresholdByLower(200);
    //取100到200为有效值
    thresholdFilter->ThresholdBetween(100, 200);
    thresholdFilter->SetInValue(255);
    thresholdFilter->SetOutValue(0);
    thresholdFilter->Update();

    // 创建actors
    vtkSmartPointer<vtkImageActor> originalActor = vtkSmartPointer<vtkImageActor>::New();
    originalActor->SetInputData(reader->GetOutput());

    vtkSmartPointer<vtkImageActor> targetActor = vtkSmartPointer<vtkImageActor>::New();
    targetActor->SetInputData(thresholdFilter->GetOutput());

    double left[4] = {0, 0, 0.5, 1};
    double right[4] = {0.5, 0, 1, 1};

    // 创建渲染器
    vtkSmartPointer<vtkRenderer> originRenderer = vtkSmartPointer<vtkRenderer>::New();
    originRenderer->SetViewport(left);
    originRenderer->AddActor(originalActor);
    originRenderer->SetBackground(1, 1, 1);

    vtkSmartPointer<vtkRenderer> targetRenderer = vtkSmartPointer<vtkRenderer>::New();
    targetRenderer->SetViewport(right);
    targetRenderer->AddActor(targetActor);
    targetRenderer->SetBackground(1, 1, 1);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(originRenderer);
    renderWindow->AddRenderer(targetRenderer);
    renderWindow->SetSize(640, 480);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
    renderWindowInteractor->SetInteractorStyle(style);

    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
}

#include <vtkImageGaussianSmooth.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleImage.h>
#include <vtkJPEGReader.h>

// 高斯滤波
int main()
{
    // 读取图像文件
    vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
    // 不能直接使用彩色图进行梯度计算
    reader->SetFileName("../datas/lena-gray.jpg");

    vtkSmartPointer<vtkImageGaussianSmooth> gaussianFilter = vtkSmartPointer<vtkImageGaussianSmooth>::New();
    gaussianFilter->SetInputConnection(reader->GetOutputPort());
    gaussianFilter->SetDimensionality(2);
    gaussianFilter->SetRadiusFactor(5);
    gaussianFilter->SetStandardDeviation(3);
    gaussianFilter->Update();

    // 创建actors
    vtkSmartPointer<vtkImageActor> originalActor = vtkSmartPointer<vtkImageActor>::New();
    originalActor->SetInputData(reader->GetOutput());

    vtkSmartPointer<vtkImageActor> targetActor = vtkSmartPointer<vtkImageActor>::New();
    targetActor->SetInputData(gaussianFilter->GetOutput());

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

#include <vtkImageCast.h>
#include <vtkImageConvolve.h>
#include <vtkImageShiftScale.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleImage.h>
#include <vtkJPEGReader.h>

// 均值滤波
int main()
{
    // 读取图像文件
    vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
    // 不能直接使用彩色图进行梯度计算
    reader->SetFileName("../datas/lena-gray.jpg");

    vtkSmartPointer<vtkImageCast> originalCastFilter = vtkSmartPointer<vtkImageCast>::New();
    originalCastFilter->SetInputConnection(reader->GetOutputPort());
    originalCastFilter->SetOutputScalarTypeToFloat();
    originalCastFilter->Update();

    vtkSmartPointer<vtkImageConvolve> convolveFilter = vtkSmartPointer<vtkImageConvolve>::New();
    convolveFilter->SetInputConnection(reader->GetOutputPort());
    double kernal[25] = {
        0.04, 0.04, 0.04, 0.04, 0.04,
        0.04, 0.04, 0.04, 0.04, 0.04,
        0.04, 0.04, 0.04, 0.04, 0.04,
        0.04, 0.04, 0.04, 0.04, 0.04,
        0.04, 0.04, 0.04, 0.04, 0.04};

    convolveFilter->SetKernel5x5(kernal);
    convolveFilter->Update();

    vtkSmartPointer<vtkImageCast> convCastFilter = vtkSmartPointer<vtkImageCast>::New();
    convCastFilter->SetInputData(convolveFilter->GetOutput());
    convCastFilter->SetOutputScalarTypeToUnsignedChar();
    convCastFilter->Update();

    // 创建actors
    vtkSmartPointer<vtkImageActor> originalActor = vtkSmartPointer<vtkImageActor>::New();
    originalActor->SetInputData(reader->GetOutput());

    vtkSmartPointer<vtkImageActor> targetActor = vtkSmartPointer<vtkImageActor>::New();
    targetActor->SetInputData(convCastFilter->GetOutput());

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

#include <vtkImageFFT.h>
#include <vtkImageRFFT.h>
#include <vtkImageExtractComponents.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleImage.h>
#include <vtkJPEGReader.h>
#include <vtkImageShiftScale.h>
#include <vtkImageCast.h>

// 各向异性滤波
int main()
{
    // 读取图像文件
    vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
    // 不能直接使用彩色图进行梯度计算
    reader->SetFileName("../datas/lena.jpg");

    vtkSmartPointer<vtkImageFFT> fftFilter = vtkSmartPointer<vtkImageFFT>::New();
    fftFilter->SetInputConnection(reader->GetOutputPort());
    fftFilter->SetDimensionality(2);
    fftFilter->Update();

    vtkSmartPointer<vtkImageExtractComponents> fftExtractReal = vtkSmartPointer<vtkImageExtractComponents>::New();
    fftExtractReal->SetInputConnection(fftFilter->GetOutputPort());
    fftExtractReal->SetComponents(0);

    double range[2];
    fftExtractReal->GetOutput()->GetScalarRange(range);

    vtkSmartPointer<vtkImageShiftScale> shiftScale =
        vtkSmartPointer<vtkImageShiftScale>::New();

    shiftScale->SetOutputScalarTypeToUnsignedChar();
    shiftScale->SetScale(255 / (range[1] - range[0]));
    shiftScale->SetShift(-range[0]);
    shiftScale->SetInputConnection(fftExtractReal->GetOutputPort());
    shiftScale->Update();

    vtkSmartPointer<vtkImageRFFT> rfftFilter = vtkSmartPointer<vtkImageRFFT>::New();
    rfftFilter->SetInputConnection(fftFilter->GetOutputPort());
    rfftFilter->SetDimensionality(2);
    rfftFilter->Update();

    vtkSmartPointer<vtkImageExtractComponents> rfftExtractReal = vtkSmartPointer<vtkImageExtractComponents>::New();
    rfftExtractReal->SetInputConnection(rfftFilter->GetOutputPort());
    rfftExtractReal->SetComponents(0);

    vtkSmartPointer<vtkImageCast> castFilter = vtkSmartPointer<vtkImageCast>::New();
    castFilter->SetOutputScalarTypeToUnsignedChar();
    castFilter->SetInputConnection(rfftExtractReal->GetOutputPort());
    castFilter->Update();

    // 创建actors
    vtkSmartPointer<vtkImageActor> originalActor = vtkSmartPointer<vtkImageActor>::New();
    originalActor->SetInputData(reader->GetOutput());

    vtkSmartPointer<vtkImageActor> fftActor = vtkSmartPointer<vtkImageActor>::New();
    fftActor->SetInputData(shiftScale->GetOutput());

    vtkSmartPointer<vtkImageActor> rfftActor = vtkSmartPointer<vtkImageActor>::New();
    rfftActor->SetInputData(castFilter->GetOutput());

    double left[4] = {0, 0, 0.33, 1};
    double middle[4] = {0.33, 0, 0.66, 1};
    double right[4] = {0.66, 0, 1, 1};

    // 创建渲染器
    vtkSmartPointer<vtkRenderer> originRenderer = vtkSmartPointer<vtkRenderer>::New();
    originRenderer->SetViewport(left);
    originRenderer->AddActor(originalActor);
    originRenderer->SetBackground(1, 1, 1);

    vtkSmartPointer<vtkRenderer> fftRenderer = vtkSmartPointer<vtkRenderer>::New();
    fftRenderer->SetViewport(middle);
    fftRenderer->AddActor(fftActor);
    fftRenderer->SetBackground(1, 1, 1);

    vtkSmartPointer<vtkRenderer> rfftRenderer = vtkSmartPointer<vtkRenderer>::New();
    rfftRenderer->SetViewport(right);
    rfftRenderer->AddActor(rfftActor);
    rfftRenderer->SetBackground(1, 1, 1);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(originRenderer);
    renderWindow->AddRenderer(fftRenderer);
    renderWindow->AddRenderer(rfftRenderer);
    renderWindow->SetSize(640, 480);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
    renderWindowInteractor->SetInteractorStyle(style);

    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
}

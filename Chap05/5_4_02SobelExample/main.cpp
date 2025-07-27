#include <vtkImageMagnitude.h>
#include <vtkImageShiftScale.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleImage.h>
#include <vtkJPEGReader.h>
#include <vtkImageSobel2D.h>
#include <vtkImageExtractComponents.h>
#include <vtkImageMathematics.h>

int main()
{
    // 读取图像文件
    vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
    // 不能直接使用彩色图进行梯度计算
    reader->SetFileName("../datas/lena-gray.jpg");

    vtkSmartPointer<vtkImageSobel2D> sobelFilter = vtkSmartPointer<vtkImageSobel2D>::New();
    sobelFilter->SetInputConnection(reader->GetOutputPort());

    vtkSmartPointer<vtkImageExtractComponents> extractXFilter = vtkSmartPointer<vtkImageExtractComponents>::New();

    extractXFilter->SetComponents(0);
    extractXFilter->SetInputConnection(sobelFilter->GetOutputPort());
    extractXFilter->Update();

    double xRange[2];
    extractXFilter->GetOutput()->GetScalarRange(xRange);

    vtkSmartPointer<vtkImageMathematics> xImageAbs = vtkSmartPointer<vtkImageMathematics>::New();

    xImageAbs->SetOperationToAbsoluteValue();
    xImageAbs->SetInputConnection(extractXFilter->GetOutputPort());
    xImageAbs->Update();

    vtkSmartPointer<vtkImageShiftScale> xShiftScale = vtkSmartPointer<vtkImageShiftScale>::New();
    xShiftScale->SetOutputScalarTypeToUnsignedChar();
    xShiftScale->SetScale(255 / xRange[1]);
    xShiftScale->SetInputConnection(xImageAbs->GetOutputPort());
    xShiftScale->Update();

    vtkSmartPointer<vtkImageExtractComponents> extractYFilter = vtkSmartPointer<vtkImageExtractComponents>::New();
    extractXFilter->SetComponents(1);
    extractYFilter->SetInputConnection(sobelFilter->GetOutputPort());
    extractYFilter->Update();

    double yRange[2];
    extractYFilter->GetOutput()->GetScalarRange(yRange);
    vtkSmartPointer<vtkImageMathematics> yImageAbs = vtkSmartPointer<vtkImageMathematics>::New();
    yImageAbs->SetOperationToAbsoluteValue();
    yImageAbs->SetInputConnection(extractYFilter->GetOutputPort());
    yImageAbs->Update();

    vtkSmartPointer<vtkImageShiftScale> yShiftScale = vtkSmartPointer<vtkImageShiftScale>::New();
    yShiftScale->SetOutputScalarTypeToUnsignedChar();
    yShiftScale->SetScale(255 / yRange[1]);
    yShiftScale->SetInputConnection(yImageAbs->GetOutputPort());
    yShiftScale->Update();

    // 创建actors
    vtkSmartPointer<vtkImageActor> originalActor = vtkSmartPointer<vtkImageActor>::New();
    originalActor->SetInputData(reader->GetOutput());

    vtkSmartPointer<vtkImageActor> xTargetActor = vtkSmartPointer<vtkImageActor>::New();
    xTargetActor->SetInputData(xShiftScale->GetOutput());

    vtkSmartPointer<vtkImageActor> yTargetActor = vtkSmartPointer<vtkImageActor>::New();
    yTargetActor->SetInputData(yShiftScale->GetOutput());

    double left[4] = {0, 0, 0.33, 1};
    double middle[4] = {0.33, 0, 0.66, 1};
    double right[4] = {0.66, 0, 1, 1};

    // 创建渲染器
    vtkSmartPointer<vtkRenderer> originRenderer = vtkSmartPointer<vtkRenderer>::New();
    originRenderer->SetViewport(left);
    originRenderer->AddActor(originalActor);
    originRenderer->SetBackground(1, 1, 1);

    vtkSmartPointer<vtkRenderer> xTargetRenderer = vtkSmartPointer<vtkRenderer>::New();
    xTargetRenderer->SetViewport(middle);
    xTargetRenderer->AddActor(xTargetActor);
    xTargetRenderer->SetBackground(1, 1, 1);

    vtkSmartPointer<vtkRenderer> yTargetRenderer = vtkSmartPointer<vtkRenderer>::New();
    yTargetRenderer->SetViewport(right);
    yTargetRenderer->AddActor(yTargetActor);
    yTargetRenderer->SetBackground(1, 1, 1);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(originRenderer);
    renderWindow->AddRenderer(xTargetRenderer);
    renderWindow->AddRenderer(yTargetRenderer);
    renderWindow->SetSize(640, 480);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
    renderWindowInteractor->SetInteractorStyle(style);

    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
}

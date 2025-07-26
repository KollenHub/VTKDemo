#include <vtkBMPReader.h>
#include <vtkSmartPointer.h>
#include <vtkImageShrink3D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindow.h>
#include <vtkImageMagnify.h>

int main()
{
    vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();
    reader->SetFileName("../datas/lena.bmp");
    reader->Update();

    // 降采样
    vtkSmartPointer<vtkImageShrink3D> downFilter = vtkSmartPointer<vtkImageShrink3D>::New();

    downFilter->SetInputConnection(reader->GetOutputPort());
    downFilter->SetShrinkFactors(16, 16, 1);
    downFilter->Update();

    // 升采样
    vtkSmartPointer<vtkImageMagnify> upFilter = vtkSmartPointer<vtkImageMagnify>::New();

    upFilter->SetInputConnection(reader->GetOutputPort());
    upFilter->SetMagnificationFactors(10,10, 1);
    upFilter->SetInterpolate(1); //1=线性插值，0=最近邻插值
    upFilter->Update();

    int originalDims[3];
    reader->GetOutput()->GetDimensions(originalDims);

    double originalSpace[3];
    reader->GetOutput()->GetSpacing(originalSpace);

    int downDims[3];
    downFilter->GetOutput()->GetDimensions(downDims);

    double downSpace[3];
    downFilter->GetOutput()->GetSpacing(downSpace);

    int upDims[3];
    upFilter->GetOutput()->GetDimensions(upDims);

    double upSpace[3];
    upFilter->GetOutput()->GetSpacing(upSpace);

    std::cout << "Oringinal image dimensions: " << originalDims[0] << " " << originalDims[1] << " " << originalDims[2] << std::endl;

    std::cout << "Original image spacing: " << originalSpace[0] << " " << originalSpace[1] << " " << originalSpace[2] << std::endl;

    std::cout << "Down image dimensions: " << downDims[0] << " " << downDims[1] << " " << downDims[2] << std::endl;

    std::cout << "Down image spacing: " << downSpace[0] << " " << downSpace[1] << " " << downSpace[2] << std::endl;

    std::cout << "up image dimensions: " << upDims[0] << " " << upDims[1] << " " << upDims[2] << std::endl;

    std::cout << "up image spacing: " << upSpace[0] << " " << upSpace[1] << " " << upSpace[2] << std::endl;

    // 创建actors
    vtkSmartPointer<vtkImageActor> originalActor = vtkSmartPointer<vtkImageActor>::New();
    originalActor->SetInputData(reader->GetOutput());

    vtkSmartPointer<vtkImageActor> downActor = vtkSmartPointer<vtkImageActor>::New();
    downActor->SetInputData(downFilter->GetOutput());

    vtkSmartPointer<vtkImageActor> upActor = vtkSmartPointer<vtkImageActor>::New();
    upActor->SetInputData(upFilter->GetOutput());


    double left[4]={0,0,0.33,1};
    double middle[4]={0.33,0,0.66,1};
    double right[4]={0.66,0,1,1};

    // 创建渲染器
    vtkSmartPointer<vtkRenderer> originRenderer = vtkSmartPointer<vtkRenderer>::New();
    originRenderer->SetViewport(left);
    originRenderer->AddActor(originalActor);
    originRenderer->SetBackground(1, 1, 1);

    vtkSmartPointer<vtkRenderer> upRenderer = vtkSmartPointer<vtkRenderer>::New();
    upRenderer->SetViewport(middle);
    upRenderer->AddActor(upActor);
    upRenderer->SetBackground(1, 1, 1);

    
    vtkSmartPointer<vtkRenderer> downRenderer = vtkSmartPointer<vtkRenderer>::New();
    downRenderer->SetViewport(right);
    downRenderer->AddActor(downActor);
    downRenderer->SetBackground(1, 1, 1);


    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(originRenderer);
    renderWindow->AddRenderer(upRenderer);
    renderWindow->AddRenderer(downRenderer);
    renderWindow->SetSize(640, 480);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
    renderWindowInteractor->SetInteractorStyle(style);

    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
}

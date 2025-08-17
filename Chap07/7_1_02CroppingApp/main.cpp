
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkMetaImageReader.h>
#include <vtkImageCast.h>
#include <vtkVolumeProperty.h>
#include <vtkGPUVolumeRayCastMapper.h>
// #include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkDataObject.h>
#include <vtkImageData.h>
#include <vtkStructuredPointsReader.h>
#include <vtkStructuredPoints.h>
#include <vtkAxisHelper.h>
#include <vtkCamera.h>
int main(int argc, char *argv[])
{

    // vtkSmartPointer<vtkMetaImageReader> reader = vtkSmartPointer<vtkMetaImageReader>::New();
    // reader->SetFileName("../datas/HeadMRVolume.mhd");
    // reader->Update();
    vtkSmartPointer<vtkStructuredPointsReader> reader = vtkSmartPointer<vtkStructuredPointsReader>::New();
    reader->SetFileName("../datas/mummy.128.vtk");
    reader->Update();

    vtkSmartPointer<vtkImageCast> cast = vtkSmartPointer<vtkImageCast>::New();
    cast->SetInputData(reader->GetOutput());
    cast->SetOutputScalarTypeToUnsignedShort();
    cast->Update();

    vtkSmartPointer<vtkGPUVolumeRayCastMapper> originVolumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
    originVolumeMapper->SetInputData(cast->GetOutput());
    originVolumeMapper->SetAutoAdjustSampleDistances(0);

    vtkSmartPointer<vtkGPUVolumeRayCastMapper> croppingVolumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
    croppingVolumeMapper->SetInputData(cast->GetOutput());
    croppingVolumeMapper->SetAutoAdjustSampleDistances(0);
    croppingVolumeMapper->SetCropping(1);
    croppingVolumeMapper->SetCroppingRegionPlanes(100, 200, 100, 200, 100, 200);
    croppingVolumeMapper->SetCroppingRegionFlags(
        0x0000001 | 0x0000002 | 0x0000004 |
        0x0000008 | 0x0000010 | 0x0000020 |
        0x0000040 | 0x0000080 | 0x0000100 |
        0x0000200 | 0x0000400 | 0x0000800 | 
        0x0001000 | 0x0002000 | 0x0004000 | 
        0x0008000 | 0x0010000 | 0x0020000 | 
        0x0040000 | 0x0080000 | 0x0100000 | 
        0x0200000 | 0x0400000 | 0x0800000 | 
        0x1000000 | 0x2000000 | 0x4000000 );

    vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
    volumeProperty->SetInterpolationTypeToLinear();
    volumeProperty->ShadeOn();
    volumeProperty->SetAmbient(0.4);
    volumeProperty->SetDiffuse(0.6);
    volumeProperty->SetSpecular(0.2);

    vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
    compositeOpacity->AddPoint(70.0, 0.0);
    compositeOpacity->AddPoint(90.0, 0.4);
    compositeOpacity->AddPoint(180.0, 0.6);
    volumeProperty->SetScalarOpacity(compositeOpacity);

    vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
    colorTransferFunction->AddRGBPoint(0.0, 0.0, 0.0, 0.0);
    colorTransferFunction->AddRGBPoint(64.0, 1.0, 0.52, 0.30);
    colorTransferFunction->AddRGBPoint(190.0, 1.0, 1.0, 1.0);
    colorTransferFunction->AddRGBPoint(220.0, .2, .2, .2);
    volumeProperty->SetColor(colorTransferFunction);

    vtkSmartPointer<vtkVolume> originVolume = vtkSmartPointer<vtkVolume>::New();
    originVolume->SetMapper(originVolumeMapper);
    originVolume->SetProperty(volumeProperty);

    vtkSmartPointer<vtkVolume> croppingVolume = vtkSmartPointer<vtkVolume>::New();
    croppingVolume->SetMapper(croppingVolumeMapper);
    croppingVolume->SetProperty(volumeProperty);

    double left[4] = {0.0, 0.0, 0.5, 1.0};
    double right[4] = {0.5, 0.0, 1.0, 1.0};

    vtkSmartPointer<vtkRenderer> originRenderer = vtkSmartPointer<vtkRenderer>::New();
    originRenderer->SetViewport(left);
    originRenderer->AddVolume(originVolume);
    originRenderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderer> croppingRenderer = vtkSmartPointer<vtkRenderer>::New();
    croppingRenderer->SetViewport(right);
    croppingRenderer->AddVolume(croppingVolume);
    croppingRenderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(originRenderer);
    renderWindow->AddRenderer(croppingRenderer);
    renderWindow->SetSize(600, 600);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // 设置坐标轴
    vtkNew<vtkAxisHelper> originAxisHelper;
    originAxisHelper->SetViewport(0.3, 0.8, 0.5, 1.0);
    originAxisHelper->SetParentRenderer(originRenderer);
    // camOrientManipulator->SquareResize();
    // Enable the widget.
    originAxisHelper->On();

    vtkNew<vtkAxisHelper> croppingAxisHelper;
    croppingAxisHelper->SetParentRenderer(croppingRenderer);
    // Enable the widget.
    croppingAxisHelper->On();

    renderWindow->Render();
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

    return 0;
}

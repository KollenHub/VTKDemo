
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

    vtkSmartPointer<vtkGPUVolumeRayCastMapper> volumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
    volumeMapper->SetInputData(cast->GetOutput());
    volumeMapper->SetAutoAdjustSampleDistances(0);

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

    vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
    volume->SetMapper(volumeMapper);
    volume->SetProperty(volumeProperty);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddVolume(volume);
    renderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(600, 600);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderWindow->Render();
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

    return 0;
}

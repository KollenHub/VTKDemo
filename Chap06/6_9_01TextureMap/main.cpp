#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkTexture.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkTextureMapToCylinder.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCylinderSource.h>
#include <vtkBMPReader.h>


int main(int argc,char *argv[])
{
    vtkSmartPointer<vtkBMPReader> textureReader=vtkSmartPointer<vtkBMPReader>::New();

    textureReader->SetFileName("../datas/VTK-logo.bmp");
    textureReader->Update();

    vtkSmartPointer<vtkTexture> texture=vtkSmartPointer<vtkTexture>::New();
    texture->SetInputConnection(textureReader->GetOutputPort());
    texture->Update();

     vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
     cylinder->SetResolution(50);
     cylinder->SetRadius(5.0);
     cylinder->SetHeight(10.0);
     cylinder->Update();

     vtkSmartPointer<vtkTextureMapToCylinder> textureMapToCylinder = vtkSmartPointer<vtkTextureMapToCylinder>::New();
     textureMapToCylinder->SetInputConnection(cylinder->GetOutputPort());
     textureMapToCylinder->Update();


     vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

     mapper->SetInputConnection(textureMapToCylinder->GetOutputPort());

     vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();

     actor->SetMapper(mapper);
     actor->SetTexture(texture);

     vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

     renderer->AddActor(actor);
     renderer->SetBackground(0.1, 0.2, 0.4);

     vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

     renderWindow->AddRenderer(renderer);
     renderWindow->SetSize(600, 600);

     vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

     renderWindowInteractor->SetRenderWindow(renderWindow);
     renderWindowInteractor->Initialize();
     renderWindowInteractor->Start();

     return EXIT_SUCCESS;
}
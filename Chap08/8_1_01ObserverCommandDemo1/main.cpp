#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkCallbackCommand.h>
#include <vtkPNGReader.h>


    long preCount=0;
// 全局函数方式
void MyCallback(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData)
{
    std::cout<<"You have clicked "<<++preCount<<" times."<<std::endl;
}


int main(int, char *[])
{

    vtkSmartPointer<vtkPNGReader> reader =
        vtkSmartPointer<vtkPNGReader>::New();

    reader->SetFileName("../datas/VTK-logo.png");

    vtkSmartPointer<vtkImageViewer2> viewer =
        vtkSmartPointer<vtkImageViewer2>::New();

    vtkSmartPointer<vtkRenderWindowInteractor> iren =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();

    viewer->SetupInteractor(iren);
    viewer->SetInputConnection(reader->GetOutputPort());
    viewer->Render();

    vtkSmartPointer<vtkCallbackCommand> callback =
        vtkSmartPointer<vtkCallbackCommand>::New();

    callback->SetCallback(MyCallback);

    iren->SetRenderWindow(viewer->GetRenderWindow());
    iren->AddObserver(vtkCommand::LeftButtonPressEvent, callback);

    iren->Initialize();
    iren->Start();

    return EXIT_SUCCESS;
}
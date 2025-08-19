#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkCallbackCommand.h>
#include <vtkPolyDataMapper.h>
#include <vtkConeSource.h>
#include <vtkRenderer.h>
class vtkMyCallback : public vtkCommand
{
public:
    static vtkMyCallback *New()
    {
        return new vtkMyCallback;
    }

    void SetObject(vtkConeSource *cone)
    {
        m_Cone = cone;
    }

    /**
     * Execute the callback function.
     *
     * @param caller The object that invoked the callback.
     * @param eventId The ID of the event that triggered the callback.
     * @param callData Additional data associated with the event.
     *
     * This function is called when the specified event occurs. It
     * retrieves the vtkRenderWindowInteractor object from the caller
     * and prints the eventId.
     */
    virtual void Execute(vtkObject *caller, unsigned long eventId, void *callData)
    {
        std::cout << "Left button pressed" << std::endl;
        std::cout << "The Height:" << m_Cone->GetHeight() << std::endl;
        std::cout << "The Radius:" << m_Cone->GetRadius() << std::endl;
        std::cout<< "The Center:" << m_Cone->GetCenter() << std::endl;
        std::cout<< "The Resolution:" << m_Cone->GetResolution() << std::endl;
    }

private:
    vtkConeSource *m_Cone;
};

int main(int, char *[])
{
    vtkSmartPointer<vtkConeSource> cone =
        vtkSmartPointer<vtkConeSource>::New();
    cone->SetHeight(3.0);
    cone->SetRadius(1.0);
    cone->SetResolution(10);

    vtkSmartPointer<vtkPolyDataMapper> mapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(cone->GetOutputPort());

    vtkSmartPointer<vtkActor> actor =
        vtkSmartPointer<vtkActor>::New();

    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer =
        vtkSmartPointer<vtkRenderer>::New();

    renderer->AddActor(actor);
    renderer->SetBackground(.3, .6, .3); // Background color green

    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();

    renderWindow->AddRenderer(renderer);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();

    renderWindowInteractor->SetRenderWindow(renderWindow);

    vtkSmartPointer<vtkMyCallback> callback =
        vtkSmartPointer<vtkMyCallback>::New();

    callback->SetObject(cone);

    renderWindowInteractor->AddObserver(vtkCommand::LeftButtonPressEvent, callback);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
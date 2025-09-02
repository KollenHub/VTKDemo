#include <vtkPointPicker.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPropPicker.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>

class PointPickerInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
    static PointPickerInteractorStyle *New(){
        return new PointPickerInteractorStyle;
    };
    vtkTypeMacro(PointPickerInteractorStyle, vtkInteractorStyleTrackballCamera);

    virtual void OnLeftButtonDown()
    {

        std::cout << "Picking pixel" << this->Interactor->GetEventPosition()[0] << " " << this->Interactor->GetEventPosition()[1] << std::endl;

        this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0], this->Interactor->GetEventPosition()[1], 0, this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

        double picked[3];
        this->Interactor->GetPicker()->GetPickPosition(picked);

        std::cout << "Picked value: " << picked[0] << " " << picked[1] << " " << picked[2] << std::endl;

        vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
        sphereSource->Update();

        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputConnection(sphereSource->GetOutputPort());

        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);
        actor->SetPosition(picked);
        actor->SetScale(0.05);
        actor->GetProperty()->SetColor(1, 0, 0);

        this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actor);

        vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }

protected:
    PointPickerInteractorStyle() {}
};

int main(int argc, char **argv)
{
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

    vtkSmartPointer<vtkPointPicker> pointPicker = vtkSmartPointer<vtkPointPicker>::New();

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetPicker(pointPicker);
    renderWindowInteractor->SetRenderWindow(renderWindow);

    vtkSmartPointer<PointPickerInteractorStyle> style = vtkSmartPointer<PointPickerInteractorStyle>::New();
    renderWindowInteractor->SetInteractorStyle(style);

    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetCenter(0.0, 0.0, 0.0);
    sphereSource->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(.2, .3, .4);
    renderWindow->AddRenderer(renderer);

    
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}

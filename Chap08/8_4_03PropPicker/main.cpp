#include <vtkPolyDataMapper.h>
#include <vtkSphereSource.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPropPicker.h>

class PropPickerInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
    static PropPickerInteractorStyle *New()
    {
        return new PropPickerInteractorStyle;
    };
    vtkTypeMacro(PropPickerInteractorStyle, vtkInteractorStyleTrackballCamera);

    virtual void OnLeftButtonDown()
    {
        int *clickPos = this->GetInteractor()->GetEventPosition();

        // 根据点进行选择
        vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();

        picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());

        double *pos = picker->GetPickPosition();

        // 如果之前已经选择了，则取消选择

        if (this->LastPickedActor)
        {
            this->LastPickedActor->GetProperty()->DeepCopy(this->LastPickedProperty);
        }
        this->LastPickedActor = picker->GetActor();

        if (this->LastPickedActor)
        {
            // 保存属性
            this->LastPickedProperty->DeepCopy(this->LastPickedActor->GetProperty());

            this->LastPickedActor->GetProperty()->SetColor(1.0, 0.0, 0.0);
            this->LastPickedActor->GetProperty()->SetDiffuse(1.0);
            this->LastPickedActor->GetProperty()->SetSpecular(0.0);
        }

        vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }

protected:
    PropPickerInteractorStyle()
    {
        LastPickedActor = nullptr;
        LastPickedProperty = vtkProperty::New();
    }
    ~PropPickerInteractorStyle()
    {
        LastPickedProperty->Delete();
    }

private:
    PropPickerInteractorStyle(const PropPickerInteractorStyle &); // Not implemented

    vtkProperty* LastPickedProperty;

    vtkActor *LastPickedActor;
};

int main(int argc, char **argv)
{
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

    vtkSmartPointer<vtkRenderer> renderer =
        vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);
    renderWindowInteractor->SetRenderWindow(renderWindow);

    vtkSmartPointer<PropPickerInteractorStyle> style = PropPickerInteractorStyle::New();
    style->SetDefaultRenderer(renderer);
    renderWindowInteractor->SetInteractorStyle(style);

    for (size_t i = 0; i < 100; i++)
    {
        // 随机坐标
        double x = (double)rand() / RAND_MAX * 100 - 50;
        double y = (double)rand() / RAND_MAX * 100 - 50;
        double z = (double)rand() / RAND_MAX * 100 - 50;

        vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
        sphereSource->SetCenter(x, y, z);
        sphereSource->Update();

        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

        mapper->SetInputConnection(sphereSource->GetOutputPort());

        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();

        actor->SetMapper(mapper);

        renderer->AddActor(actor);
    }

    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
    return EXIT_SUCCESS;
}
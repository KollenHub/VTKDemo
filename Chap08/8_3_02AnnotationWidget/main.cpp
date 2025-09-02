#include <vtkCaptionActor2D.h>
#include <vtkCaptionRepresentation.h>
#include <vtkAxesActor.h>
#include <vtkActor.h>
#include <vtkBalloonRepresentation.h>
#include <vtkTextRepresentation.h>
#include <vtkTextProperty.h>
#include <vtkTextActor.h>
#include <vtkScalarBarActor.h>
#include <vtkScalarBarWidget.h>
#include <vtkTextWidget.h>
#include <vtkBalloonWidget.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkCaptionWidget.h>
#include <vtkSmartPointer.h>
#include <vtkDistanceWidget.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkLookupTable.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkUnstructuredGrid.h>

int main(int argc, char *argv[])
{

    vtkSmartPointer<vtkUnstructuredGridReader> reader = vtkSmartPointer<vtkUnstructuredGridReader>::New();
    reader->SetFileName("../datas/scalarBarWidgetTestData.vtk");
    reader->Update();

    vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
    lut->Build();

    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputConnection(reader->GetOutputPort());
    mapper->SetScalarRange(reader->GetOutput()->GetScalarRange());
    mapper->SetLookupTable(lut);

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();

    vtkSmartPointer<vtkRenderer> renderer =
        vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(1.0, 1.0, 1.0);
    renderer->AddActor(actor);
    renderWindow->AddRenderer(renderer);
    vtkSmartPointer<vtkRenderWindowInteractor> iren =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renderWindow);

    // vtkScalarBarWidget
    vtkSmartPointer<vtkScalarBarActor> scalarBarActor =
        vtkSmartPointer<vtkScalarBarActor>::New();
    scalarBarActor->SetOrientationToHorizontal();
    scalarBarActor->SetLookupTable(lut);

    vtkSmartPointer<vtkScalarBarWidget> scalarBarWidget =
        vtkSmartPointer<vtkScalarBarWidget>::New();
    scalarBarWidget->SetInteractor(iren);
    scalarBarWidget->SetScalarBarActor(scalarBarActor);
    scalarBarWidget->On();

    // vtkTextWidget
    vtkSmartPointer<vtkTextActor> textActor =
        vtkSmartPointer<vtkTextActor>::New();

    textActor->SetInput("Hello World");
    textActor->GetTextProperty()->SetColor(1.0, 0.0, 0.0);

    vtkSmartPointer<vtkTextWidget> textWidget =
        vtkSmartPointer<vtkTextWidget>::New();

    vtkSmartPointer<vtkTextRepresentation> textRep =
        vtkSmartPointer<vtkTextRepresentation>::New();

    textRep->GetPositionCoordinate()->SetValue(.15, .15);
    textRep->GetPosition2Coordinate()->SetValue(.7, .2);

    textWidget->SetRepresentation(textRep);
    textWidget->SetTextActor(textActor);
    textWidget->SetInteractor(iren);
    textWidget->SelectableOff();
    textWidget->On();

    // vtkBalloonWidget 悬浮显示
    vtkSmartPointer<vtkBalloonRepresentation> balloonRep =
        vtkSmartPointer<vtkBalloonRepresentation>::New();
    balloonRep->SetBalloonLayoutToImageRight();

    vtkSmartPointer<vtkBalloonWidget> balloonWidget =
        vtkSmartPointer<vtkBalloonWidget>::New();
    balloonWidget->SetInteractor(iren);
    balloonWidget->SetRepresentation(balloonRep);
    balloonWidget->AddBalloon(actor, "This is a balloon", NULL);
    balloonWidget->On();

    // vtkOrientationMarkerWidget
    vtkSmartPointer<vtkAxesActor> iconActor = vtkSmartPointer<vtkAxesActor>::New();
    vtkSmartPointer<vtkOrientationMarkerWidget> orientationWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    orientationWidget->SetOrientationMarker(iconActor);
    orientationWidget->SetOutlineColor(0.93, 0.57, 0.13);
    orientationWidget->SetInteractor(iren);
    orientationWidget->SetViewport(0, 0, 0.2, 0.2);
    orientationWidget->SetEnabled(1);
    orientationWidget->InteractiveOn();
    orientationWidget->On();

    // vtkCaptionWidget
    vtkSmartPointer<vtkCaptionRepresentation> captionRep = vtkSmartPointer<vtkCaptionRepresentation>::New();
    captionRep->GetCaptionActor2D()->SetCaption("Caption Widget");

    double captionPosition[3] = { 0.5, 0.0, 0.0 };
    captionRep->SetPosition(captionPosition);

    vtkSmartPointer<vtkCaptionWidget> captionWidget = vtkSmartPointer<vtkCaptionWidget>::New();
    captionWidget->SetInteractor(iren);
    captionWidget->SetRepresentation(captionRep);
    captionWidget->On();

    iren->Initialize();
    iren->Start();

    return EXIT_SUCCESS;
}
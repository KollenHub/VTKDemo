#include <vtkProperty.h>
#include <vtkSmartPointer.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataNormals.h>
#include <vtkPolyDataNormals.h>
#include <vtkPolyDataMapper.h>
#include <vtkMaskPoints.h>
#include <vtkArrowSource.h>
#include <vtkGlyph3D.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int argc, char *argv[])
{
    vtkSmartPointer<vtkPLYReader> reader = vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName("../datas/bunny.ply");
    reader->Update();

    vtkSmartPointer<vtkPolyDataNormals> normalsFilter = vtkSmartPointer<vtkPolyDataNormals>::New();

    normalsFilter->SetInputData(reader->GetOutput());
    //自动调整法线方向
    normalsFilter->SetAutoOrientNormals(true);
    //自动调节单元点顺序
    normalsFilter->SetConsistency(true);
    normalsFilter->SetComputePointNormals(1);
    normalsFilter->SetComputeCellNormals(1);
    normalsFilter->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(normalsFilter->GetOutput());


    //读入模型数据较大，使用mask随机采样300个点做符号化显示
    vtkSmartPointer<vtkMaskPoints> mask = vtkSmartPointer<vtkMaskPoints>::New();
    mask->SetInputData(normalsFilter->GetOutput());
    mask->SetMaximumNumberOfPoints(300);
    mask->RandomModeOn();
    mask->Update();

    vtkSmartPointer<vtkArrowSource> arrow = vtkSmartPointer<vtkArrowSource>::New();
    arrow->Update();
    vtkSmartPointer<vtkGlyph3D> glyph = vtkSmartPointer<vtkGlyph3D>::New();
    glyph->SetInputData(mask->GetOutput());
    glyph->SetSourceData(arrow->GetOutput());
    //指定要使用法向量数据来控制Glyph图形的方向
    glyph->SetVectorModeToUseNormal();
    //控制Glyph图形的大小
    glyph->SetScaleFactor(0.01);
    glyph->Update();

    vtkSmartPointer<vtkPolyDataMapper> originMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    originMapper->SetInputData(reader->GetOutput());

    vtkSmartPointer<vtkActor> originActor = vtkSmartPointer<vtkActor>::New();
    originActor->SetMapper(originMapper);

    vtkSmartPointer<vtkPolyDataMapper> normaledMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    normaledMapper->SetInputData(normalsFilter->GetOutput());

    vtkSmartPointer<vtkActor> normaledActor = vtkSmartPointer<vtkActor>::New();
    normaledActor->SetMapper(normaledMapper);

    vtkSmartPointer<vtkPolyDataMapper> glyphMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    glyphMapper->SetInputData(glyph->GetOutput());

    vtkSmartPointer<vtkActor> glyphActor = vtkSmartPointer<vtkActor>::New();
    glyphActor->SetMapper(glyphMapper);
    glyphActor->GetProperty()->SetColor(1.0, 0.0, 0.0);

    double originalViewport[4] = {0.0, 0.0, 0.33, 1.0};
    double normViewport[4] = {0.33, 0.0, 0.66, 1.0};
    double glphViewport[4] = {0.66, 0.0, 1.0, 1.0};

    // 渲染器
    vtkSmartPointer<vtkRenderer> originRenderer = vtkSmartPointer<vtkRenderer>::New();
    originRenderer->SetViewport(originalViewport);
    originRenderer->AddActor(originActor);
    originRenderer->ResetCamera();
    originRenderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderer> normaledRenderer = vtkSmartPointer<vtkRenderer>::New();
    normaledRenderer->SetViewport(normViewport);
    normaledRenderer->AddActor(normaledActor);
    normaledRenderer->ResetCamera();
    normaledRenderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderer> glyphRenderer = vtkSmartPointer<vtkRenderer>::New();
    glyphRenderer->SetViewport(glphViewport);
    glyphRenderer->AddActor(glyphActor);
    glyphRenderer->AddActor(normaledActor);
    glyphRenderer->ResetCamera();
    glyphRenderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(normaledRenderer);
    renderWindow->AddRenderer(glyphRenderer);
    renderWindow->AddRenderer(originRenderer);
    renderWindow->SetSize(600, 320);
    renderWindow->Render();
    renderWindow->SetWindowName("PolyDataNormal");

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

    return 0;
}
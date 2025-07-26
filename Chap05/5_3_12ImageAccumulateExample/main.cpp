#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageData.h>
#include <vtkJPEGReader.h>
#include <vtkImageAccumulate.h>
#include <vtkIntArray.h>
#include <vtkFieldData.h>
#include <vtkBarChartActor.h>
#include <vtkProperty2D.h>
#include <vtkLegendBoxActor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindow.h>

int main()
{
    // 直方图
	// 其中X表示灰度级别，256被分为16个级别
	// 其中Y轴表示存在的像素数量


    // 1. 读取图像文件
    vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
    reader->SetFileName("../datas/lena-gray.jpg"); // 设置图像路径
    reader->Update(); // 执行读取操作

    // 2. 设置直方图参数
    int bins = 16;    // 直方图的柱子数量（将0-255的灰度范围分成16个区间）
    int comps = 1;    // 组件数量（灰度图像为1，RGB彩色图像为3）

    // 3. 创建并设置直方图计算器
    vtkSmartPointer<vtkImageAccumulate> histogram = vtkSmartPointer<vtkImageAccumulate>::New();
    histogram->SetInputData(reader->GetOutput()); // 设置输入图像数据
    histogram->SetComponentExtent(0, bins - 1, 0, 0, 0, 0); // 设置直方图范围
    histogram->SetComponentSpacing(256.0 / bins, 0.0, 0.0); // 设置间距,设置数据在256范围内的比例
    histogram->Update(); // 执行计算

    // 4. 获取直方图计算结果
    int *output = static_cast<int *>(histogram->GetOutput()->GetScalarPointer());

    // 5. 将直方图数据存入数组
    vtkSmartPointer<vtkIntArray> dataArray = vtkSmartPointer<vtkIntArray>::New();
    dataArray->SetNumberOfComponents(1); // 设置数组组件数

    // 6. 填充直方图数据
    for (int i = 0; i < bins; i++)
    {
        for (int j = 0; j < comps; j++)
        {
            dataArray->InsertNextTuple1(*output++); // 逐个添加数据点
        }
    }

    // 7. 创建数据对象并添加直方图数据
    vtkSmartPointer<vtkDataObject> dataObject = vtkSmartPointer<vtkDataObject>::New();
    dataObject->GetFieldData()->AddArray(dataArray); // 将直方图数据添加到数据对象

    // 8. 创建柱状图Actor并设置属性
    vtkSmartPointer<vtkBarChartActor> barChart = vtkSmartPointer<vtkBarChartActor>::New();
    barChart->SetInput(dataObject); // 设置输入数据
    barChart->SetTitle("Gray Level Histogram"); // 设置图表标题
    barChart->GetPositionCoordinate()->SetValue(0.05, 0.05, 0.0); // 设置图表位置
    barChart->GetPosition2Coordinate()->SetValue(0.95, 0.95, 0.0); // 设置图表尺寸
    barChart->GetProperty()->SetColor(1, 1, 1); // 设置图表颜色（白色）
    barChart->GetLegendActor()->SetNumberOfEntries(dataObject->GetFieldData()->GetArray(0)->GetNumberOfTuples());
    barChart->LegendVisibilityOff(); // 关闭图例
    barChart->LabelVisibilityOff(); // 关闭标签

    // 9. 设置柱子颜色（虽然灰度图像通常不需要多种颜色）
    double colors[3][3] = {
        {1, 0, 0}, // 红
        {0, 1, 0}, // 绿
        {0, 0, 1}  // 蓝
    };

    int count = 0;
    for (int i = 0; i < bins; ++i)
    {
        for (size_t j = 0; j < comps; j++)
        {
            barChart->SetBarColor(count++, colors[j]); // 设置每个柱子的颜色
        }
    }

    // 10. 创建渲染器和渲染窗口
    vtkSmartPointer<vtkRenderer> sourceRenderer = vtkSmartPointer<vtkRenderer>::New();
    sourceRenderer->AddActor(barChart); // 将柱状图添加到渲染器

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> rwInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();

    // 11. 设置交互方式并初始化
    rwInteractor->SetInteractorStyle(style); // 设置交互样式
    renderWindow->AddRenderer(sourceRenderer); // 将渲染器添加到窗口
    rwInteractor->SetRenderWindow(renderWindow); // 设置交互器的渲染窗口
    rwInteractor->Initialize(); // 初始化交互器
    rwInteractor->Start(); // 开始交互

    return 0;
}
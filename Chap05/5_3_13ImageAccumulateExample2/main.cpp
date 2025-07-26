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
#include <vtkXYPlotActor.h>
#include <vtkImageExtractComponents.h>

int main()
{
    // 1. 读取图像文件
    vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
    reader->SetFileName("../datas/lena.jpg"); // 设置图像路径
    reader->Update();                         // 执行读取操作

    // 获取图像的通道数(如RGB图像有3个通道)
    int numComponents = reader->GetNumberOfScalarComponents();

    // 创建一个XY绘图对象，用于显示直方图
    vtkSmartPointer<vtkXYPlotActor> plot = vtkSmartPointer<vtkXYPlotActor>::New();

    // 配置绘图属性
    plot->ExchangeAxesOff();
    plot->SetLabelFormat("%g");       // 设置标签格式
    plot->SetXValuesToValue();       // X轴表示像素值
    plot->SetXTitle("Value");        // X轴标题
    plot->SetYTitle("Frequency");    // Y轴标题(频率)
    plot->SetXValuesToValue();

    // 定义颜色通道的颜色和标签
    double color[3][3] = {
        {1, 0, 0},  // 红色通道
        {0, 1, 0},  // 绿色通道
        {0, 0, 1}   // 蓝色通道
    };
    const char *labels[3] = {"red", "green", "blue"};

    // 用于记录X和Y轴的最大值，以便设置合适的坐标范围
    int xmax = 0;
    int ymax = 0;

    // 遍历每个颜色通道
    for (size_t i = 0; i < numComponents; ++i)
    {
        // 2. 提取当前颜色通道
        vtkSmartPointer<vtkImageExtractComponents> extract = 
            vtkSmartPointer<vtkImageExtractComponents>::New();
        extract->SetInputConnection(reader->GetOutputPort());
        extract->SetComponents(i);  // 设置要提取的通道索引
        extract->Update();

        // 3. 获取当前通道的像素值范围
        double range[2];
        extract->GetOutput()->GetScalarRange(range);  // 获取最小和最大像素值
        int extent = static_cast<int>(range[1] - range[0]) - 1;

        // 4. 计算直方图
        vtkSmartPointer<vtkImageAccumulate> histogram = 
            vtkSmartPointer<vtkImageAccumulate>::New();
        histogram->SetInputConnection(extract->GetOutputPort());
        histogram->SetComponentExtent(0, extent, 0, 0, 0, 0);  // 设置直方图范围
        histogram->SetComponentOrigin(range[0], 0, 0);         // 设置原点
        histogram->SetComponentSpacing(1, 0, 0);               // 设置间距
        histogram->Update();

        // 更新坐标轴的最大值
        if (range[1] > xmax) {
            xmax = range[1];
        }
        if (histogram->GetOutput()->GetScalarRange()[1] > ymax) {
            ymax = histogram->GetOutput()->GetScalarRange()[1];
        }

        // 5. 将直方图数据添加到绘图对象
        plot->AddDataSetInput(histogram->GetOutput());
        plot->SetPlotColor(i, color[i]);  // 设置曲线颜色
        plot->SetPlotLabel(i, labels[i]); // 设置曲线标签
        plot->LegendOn();                // 启用图例
    }

    // 6. 设置坐标轴范围
    plot->SetXRange(0, xmax);
    plot->SetYRange(0, ymax);

    // 7. 创建渲染器和渲染窗口
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(plot);  // 将绘图对象添加到渲染器

    vtkSmartPointer<vtkRenderWindow> renderWindow = 
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(800, 600);  // 设置窗口大小

    // 8. 创建窗口交互器
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // 设置交互样式(图像专用样式)
    vtkSmartPointer<vtkInteractorStyleImage> style = 
        vtkSmartPointer<vtkInteractorStyleImage>::New();
    renderWindowInteractor->SetInteractorStyle(style);

    // 启动交互
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
    
    return 0;
}
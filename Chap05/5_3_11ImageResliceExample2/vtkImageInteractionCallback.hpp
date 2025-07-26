#pragma once
#include <vtkCommand.h>
#include <vtkImageReslice.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageData.h>
#include <vtkMatrix4x4.h>
#include <vtkInteractorStyle.h>
class vtkImageInteractionCallback : public vtkCommand
{
private:
    int Slicing;
    vtkImageReslice *ImageReslice;
    vtkRenderWindowInteractor *Interactor;
    /* data */
public:
    static vtkImageInteractionCallback *New()
    {
        return new vtkImageInteractionCallback();
    }
    vtkImageInteractionCallback(/* args */)
    {
        this->Slicing = 0;
        this->ImageReslice = 0;
        this->Interactor = 0;
    }
    ~vtkImageInteractionCallback()
    {
    }

    void SetImageReslice(vtkImageReslice *reslice)
    {
        this->ImageReslice = reslice;
    }

    vtkImageReslice *GetImageReslice()
    {
        return this->ImageReslice;
    }

    void SetInteractor(vtkRenderWindowInteractor *interactor)
    {
        this->Interactor = interactor;
    }

    vtkRenderWindowInteractor *GetInteractor()
    {
        return this->Interactor;
    }

    virtual void Execute(vtkObject *caller, unsigned long eventId, void *vtkNotUsed(callData))
    {
        vtkRenderWindowInteractor *interactor = this->GetInteractor();

        // 获取最后的鼠标
        int lastPos[2];
        interactor->GetLastEventPosition(lastPos);

        // 获取当前的鼠标
        int curPos[2];
        interactor->GetEventPosition(curPos);

        if (eventId == vtkCommand::LeftButtonPressEvent)
        {
            this->Slicing = 1;
        }
        else if (eventId == vtkCommand::LeftButtonReleaseEvent)
        {
            this->Slicing = 0;
        }
        else if (eventId == vtkCommand::MouseMoveEvent)
        {
            if (this->Slicing)
            {
                vtkImageReslice *reslice = this->ImageReslice;
                int deltaY = lastPos[1] - curPos[1];

                reslice->Update();

                double sliceSpacing = reslice->GetOutput()->GetSpacing()[2];

                vtkMatrix4x4 *matrix = reslice->GetResliceAxes();

                // 移动中心点顺着切片的方向

                double point[4];
                double center[4];

                point[0] = 0.0;
                point[1] = 0.0;
                point[2] = sliceSpacing * deltaY;
                point[3] = 1.0;

                // 转换point到世界坐标
                matrix->MultiplyPoint(point, center);

                // 更新切片中心点
                matrix->SetElement(0, 3, center[0]);
                matrix->SetElement(1, 3, center[1]);
                matrix->SetElement(2, 3, center[2]);

                printf("%f%f%f\n", center[0], center[1], center[2]);

                interactor->Render();
            }
            else
            {
                // 如果没有按住鼠标左键则执行默认操作
                vtkInteractorStyle *style = vtkInteractorStyle::SafeDownCast(interactor->GetInteractorStyle());

                if (style)
                {
                    style->OnMouseMove();
                }
            }
        }
    }
};

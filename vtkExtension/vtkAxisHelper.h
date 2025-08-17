// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
/**
 * @class   vtkAxisHelper
 * @brief   A widget to manipulate vtkAxisHelper.
 *
 *
 * This 3D widget creates and manages its own vtkCameraOrientationRepresentation.
 * To use this widget, make sure you call SetParentRenderer() and enable the widget.
 * The jump-to-axis-viewpoint feature is animated over 20 frames. See SetAnimatorTotalFrames()
 * Turn off animation with AnimateOff()
 *
 * @par Event Bindings:
 * By default, the widget responds to the following VTK events (i.e., it
 * watches the vtkRenderWindowInteractor for these events):
 * <pre>
 * LeftButtonPressEvent - select the appropriate handle
 * LeftButtonReleaseEvent - release the currently selected handle
 * If one of the six handles are selected:
 *   MouseMoveEvent - rotate (if left button) , else set hover representation for nearest handle.
 * </pre>
 * These input events are not forwarded to any other observers. This widget
 * eats up mouse events. (AbortFlagOn).
 *
 * @par Event Bindings:
 * Note that the event bindings described above can be changed using this
 * class's vtkWidgetEventTranslator, which translates VTK events
 * into the vtkAxisHelper's widget events:
 * <pre>
 *   vtkWidgetEvent::Select -- some part of the widget has been selected
 *   vtkWidgetEvent::EndSelect -- the selection process has completed
 *   vtkWidgetEvent::Move -- a request for motion has been invoked
 * </pre>
 *
 * @par Event Bindings:
 * This class, and the affiliated vtkCameraOrientationRepresentation,
 * are second generation VTK widgets.
 *
 * @sa
 * vtkCameraOrientationRepresentation
 */

#ifndef vtkAxisHelper_h
#define vtkAxisHelper_h

#include "vtkAbstractWidget.h"
#include "vtkInteractionWidgetsModule.h" // needed for export macro
#include "vtkWeakPointer.h"              // for weak pointer ivar

VTK_ABI_NAMESPACE_BEGIN
class vtkCameraInterpolator;
class vtkCameraOrientationRepresentation;
class vtkRenderer;

class vtkAxisHelper : public vtkAbstractWidget
{
public:
  static vtkAxisHelper* New();
  vtkTypeMacro(vtkAxisHelper, vtkAbstractWidget);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  ///@{
  /**
   * Enable jump-to-axis-view animation.
   * See AnimatorTotalFrames.
   */
  vtkSetMacro(Animate, bool);
  vtkGetMacro(Animate, bool);
  vtkBooleanMacro(Animate, bool);
  ///@}

  ///@{
  /**
   * Length of animation. (in frames)
   */
  vtkSetClampMacro(AnimatorTotalFrames, int, 2, VTK_INT_MAX);
  vtkGetMacro(AnimatorTotalFrames, int);
  ///@}

  /**
   * Create a vtkCameraOrientationRepresentation.
   */
  void CreateDefaultRepresentation() override;

  /**
   * Fits the widget's renderer to a square viewport.
   */
  void SquareResize();

  void SetViewport(double xmin, double ymin, double xmax, double ymax);

  ///@{
  /**
   * This widget shows and manipulates the orientation of
   * the parent renderer's active camera.
   *
   * Note: The renderer must be part of a render window for
   * the widget to appear.
   */
  void SetParentRenderer(vtkRenderer* renderer);
  vtkRenderer* GetParentRenderer();
  ///@}

protected:
  vtkAxisHelper();
  ~vtkAxisHelper() override = default;

  // These methods handle events
  void ComputeWidgetState(int X, int Y, int modify = 0);
  static void SelectAction(vtkAbstractWidget*);
  static void EndSelectAction(vtkAbstractWidget*);
  static void MoveAction(vtkAbstractWidget*);

  // These control the representation and parent renderer's camera.
  void OrientParentCamera(double back[3], double up[3]);
  void OrientWidgetRepresentation();
  void InterpolateCamera(int t);

  // Manage the state of the widget
  enum class WidgetStateType : int
  {
    Inactive, // mouse is not over the widget, none of the handles are selected.
    Hot,      // mouse is over the widget but none of the handles are selected
    Active    // any one handle is selected, representation could be rotating.
  };
  WidgetStateType WidgetState = WidgetStateType::Inactive;

  vtkWeakPointer<vtkRenderer> ParentRenderer;

  // Store camera interpolations.
  vtkNew<vtkCameraInterpolator> CameraInterpolator;

  bool Animate = true;
  int AnimatorTotalFrames = 20;

  int ResizeObserverTag = -1;

private:
  vtkAxisHelper(const vtkAxisHelper&) = delete;
  void operator=(const vtkAxisHelper&) = delete;
};

VTK_ABI_NAMESPACE_END
#endif

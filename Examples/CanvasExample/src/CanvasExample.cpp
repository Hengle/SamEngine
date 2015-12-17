#include <CoreModule.h>
#include <LauncherModule.h>
#include <WindowModule.h>
#include <GraphicsModule.h>

using namespace SamEngine;

class CanvasExample : public IApplication
{
public:
    ApplicationState Initialize() override;

    ApplicationState Running() override;

    ApplicationState Finalize() override;

private:
    ClearState mClearState;
};

ApplicationState CanvasExample::Initialize()
{
    GetWindow().Initialize(WindowConfig::ForWindow(1024, 768, "CanvasExample"));
    GetGraphics().Initialize(GraphicsConfig());
    GetWindow().GetInput().GetMouse().SetCursorMode(MouseCursorMode::NORMAL);
    return ApplicationState::RUNNING;
}

ApplicationState CanvasExample::Running()
{
    GetGraphics().GetRenderer().ApplyTarget();
    GetGraphics().GetRenderer().ApplyClearState(mClearState);
    GetGraphics().GetCanvas().BeginFrame();
    GetGraphics().GetCanvas().SetColorFillStyle({ 255, 0, 0, 0 });
    GetGraphics().GetCanvas().FillRect(0, 0, 200, 300);
    GetGraphics().GetCanvas().EndFrame();
    GetGraphics().GetRenderer().Render();
    GetWindow().Present();
    return GetWindow().ShouldClose() ? ApplicationState::FINALIZE : ApplicationState::RUNNING;
}

ApplicationState CanvasExample::Finalize()
{
    GetGraphics().Finalize();
    GetWindow().Finalize();
    return ApplicationState::EXIT;
}

SamEngineApplication(CanvasExample)
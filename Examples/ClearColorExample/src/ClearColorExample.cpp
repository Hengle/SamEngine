#include <CoreModule.h>
#include <LauncherModule.h>
#include <WindowModule.h>
#include <GraphicsModule.h>

using namespace SamEngine;

class ClearColorExample : public IApplication
{
public:
    ApplicationState Initialize() override;

    ApplicationState Running() override;

    ApplicationState Finalize() override;

private:
    ClearState mClearState;
};

ApplicationState ClearColorExample::Initialize()
{
    GetWindow().Initialize(WindowConfig::ForWindow(800, 600, "ClearColorExample"));
    GetGraphics().Initialize(GraphicsConfig());
    return ApplicationState::RUNNING;
}

ApplicationState ClearColorExample::Running()
{
    mClearState.ClearColor += Color(0.01f, 0.005f, 0.0025f, 0.0f);
    mClearState.ClearColor = glm::mod(mClearState.ClearColor, Color(1.0f));

    GetGraphics().GetRenderer().ApplyTarget();
    GetGraphics().GetRenderer().ApplyClearState(mClearState);
    GetGraphics().GetRenderer().Render();
    GetWindow().Present();
    return GetWindow().ShouldClose() ? ApplicationState::FINALIZE : ApplicationState::RUNNING;
}

ApplicationState ClearColorExample::Finalize()
{
    GetGraphics().Finalize();
    GetWindow().Finalize();
    return ApplicationState::EXIT;
}

SamEngineApplication(ClearColorExample)
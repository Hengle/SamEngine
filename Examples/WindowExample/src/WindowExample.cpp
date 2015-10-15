#include <CoreModule.h>
#include <LauncherModule.h>
#include <WindowModule.h>

using namespace SamEngine;

class WindowExample : public IApplication
{
public:
    ApplicationState Initialize() override;

    ApplicationState Running() override;

    ApplicationState Finalize() override;
};

ApplicationState WindowExample::Initialize()
{
    GetWindow().Initialize(WindowConfig::ForWindow(800, 600, "WindowExample"));
    return ApplicationState::RUNNING;
}

ApplicationState WindowExample::Running()
{
    GetWindow().Present();
    return GetWindow().ShouldClose() ? ApplicationState::FINALIZE : ApplicationState::RUNNING;
}

ApplicationState WindowExample::Finalize()
{
    GetWindow().Finalize();
    return ApplicationState::EXIT;
}

SamEngineApplication(WindowExample)
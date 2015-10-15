#include <CoreModule.h>
#include <IOModule.h>
#include <HTTPModule.h>
#include <LauncherModule.h>

#include <cstring>

using namespace SamEngine;

class HTTPFilesystemExample : public IApplication
{
public:
    ApplicationState Initialize() override;

    ApplicationState Running() override;

    ApplicationState Finalize() override;

private:
    bool complete{ false };
};

ApplicationState HTTPFilesystemExample::Initialize()
{
    GetHTTP().Initialize();
    GetIO().Initialize();
    GetIO().SetFilesystemCreator("http", GetHTTPFilesystemCreator());
    GetIO().SetLocationPlaceholder("git", "http://leafnsand.github.io/");

    GetIO().Read("git:test.txt", [&](EventPtr &e)
    {
        if (e->GetStatus() == EventStatus::COMPLETE)
        {
            auto read_event = std::static_pointer_cast<IORequestReadEvent>(e);
            if (read_event)
            {
                auto data = read_event->GetData();
                GetLog().Debug("read complete: %s\n", data->GetBuffer());
                complete = true;
            }
        }
    });

    return ApplicationState::RUNNING;
}

ApplicationState HTTPFilesystemExample::Running()
{
    return complete ? ApplicationState::FINALIZE : ApplicationState::RUNNING;
}

ApplicationState HTTPFilesystemExample::Finalize()
{
    GetHTTP().Finalize();
    GetIO().Finalize();
    return ApplicationState::EXIT;
}

SamEngineApplication(HTTPFilesystemExample)
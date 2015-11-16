#include <CoreModule.h>
#include <IOModule.h>
#include <StorageModule.h>
#include <LauncherModule.h>

#include <cstring>

using namespace SamEngine;

class StorageFilesystemExample : public IApplication
{
public:
    ApplicationState Initialize() override;

    ApplicationState Running() override;

    ApplicationState Finalize() override;

private:
    bool complete{ false };
};

ApplicationState StorageFilesystemExample::Initialize()
{
    GetIO().Initialize();
    GetIO().SetFilesystemCreator("storage", GetStorageFilesystemCreator());
    GetIO().SetLocationPlaceholder("local", "storage://F:/SamEngine/Build/");

    auto hello = "Hello World!";
    auto test_data = Data::Create();
    test_data->Copy(hello, strlen(hello) + 1);
    GetIO().AsyncWrite("local:test.txt", test_data, [&](EventPtr e)
    {
        if (e->GetStatus() == EventStatus::COMPLETE)
        {
            GetLog().Debug("write complete.\n");
            GetIO().AsyncRead("local:test.txt", [&](EventPtr ee)
            {
                if (ee->GetStatus() == EventStatus::COMPLETE)
                {
                    auto read_event = std::static_pointer_cast<IORequestReadEvent>(ee);
                    if (read_event)
                    {
                        auto data = read_event->GetData();
                        GetLog().Debug("read complete: %s\n", data->GetBuffer());
                        complete = true;
                    }
                }
            });
        }
    });

    return ApplicationState::RUNNING;
}

ApplicationState StorageFilesystemExample::Running()
{
    return complete ? ApplicationState::FINALIZE : ApplicationState::RUNNING;
}

ApplicationState StorageFilesystemExample::Finalize()
{
    GetIO().Finalize();
    return ApplicationState::EXIT;
}

SamEngineApplication(StorageFilesystemExample)
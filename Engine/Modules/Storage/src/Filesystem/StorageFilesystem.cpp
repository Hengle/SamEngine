#include "StorageFilesystem.h"
#include "IStorage.h"

namespace SamEngine
{
    bool StorageFilesystem::Handle(const EventPtr &event)
    {
        if (event->GetID() == IOEventType::RequestReadEventID)
        {
            auto readEvent = std::static_pointer_cast<IORequestReadEvent>(event);
            readEvent->SetData(GetStorage().Read(readEvent->GetLocation().GetPath()));
        }
        else if (event->GetID() == IOEventType::RequestWriteEventID)
        {
            auto writeEvent = std::static_pointer_cast<IORequestWriteEvent>(event);
            GetStorage().Write(writeEvent->GetLocation().GetPath(), writeEvent->GetData());
        }
        else
        {
            s_error("storage filesystem: invalid event!\n");
        }
        event->SetCompleted();
        return true;
    }

    STORAGE_API Filesystem::Creator GetStorageFilesystemCreator()
    {
        return StorageFilesystem::Creator;
    }
}
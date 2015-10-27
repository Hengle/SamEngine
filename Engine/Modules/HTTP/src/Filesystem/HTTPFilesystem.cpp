#include "HTTPFilesystem.h"
#include "IHTTP.h"

namespace SamEngine
{
    bool HTTPFilesystem::Handle(const EventPtr &event)
    {
        if (event->GetID() == IOEventType::RequestReadEventID)
        {
            auto read_event = std::static_pointer_cast<IORequestReadEvent>(event);
            read_event->SetData(GetHTTP().Read(read_event->GetLocation().GetRaw()));
        }
        else
        {
            s_error("storage filesystem: invalid event!\n");
        }
        event->SetCompleted();
        return true;
    }

    HTTP_API Filesystem::Creator GetHTTPFilesystemCreator()
    {
        return HTTPFilesystem::Creator;
    }
}
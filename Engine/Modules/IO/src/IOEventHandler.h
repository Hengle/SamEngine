#pragma once

#include "Event/IORequestReadEvent.h"
#include "Event/IORequestWriteEvent.h"
#include "Event/IONotifyNewFilesystemEvent.h"
#include "Event/IONotifyReplaceFilesystemEvent.h"
#include "Event/IONotifyDeleteFilesystemEvent.h"
#include "Filesystem/Filesystem.h"

#include <EventModule.h>

#include <unordered_map>

namespace SamEngine
{
    class IOEventHandler : public IEventHandler
    {
    public:
        CREATE_FUNC_DECLARE(IOEventHandler)

        IOEventHandler();

        virtual bool Handle(EventPtr event) override;

    protected:
        void HandleRequestReadEvent(IORequestReadEventPtr event);

        void HandleRequestWriteEvent(IORequestWriteEventPtr event);

        void HandleNotifyNewFilesystemEvent(IONotifyNewFilesystemEventPtr event);

        void HandleNotifyReplaceFilesystemEvent(IONotifyReplaceFilesystemEventPtr event);

        void HandleNotifyDeleteFilesystemEvent(IONotifyDeleteFilesystemEventPtr event);

    private:
        std::unordered_map<std::string, FilesystemPtr> mFilesystems;

    protected:
        std::shared_ptr<EventDispatcher<IOEventType>> mEventDispather{ nullptr };
    };

    typedef std::shared_ptr<IOEventHandler> IOEventHandlerPtr;
}
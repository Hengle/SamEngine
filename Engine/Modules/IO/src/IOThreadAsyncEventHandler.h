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
    class IOThreadAsyncEventHandler : public ThreadAsyncEventHandler
    {
    public:
        CREATE_FUNC_DECLARE(IOThreadAsyncEventHandler)

        IOThreadAsyncEventHandler();

    protected:
        void EnterThread() override;

        void ExitThread() override;

    private:
        void HandleRequestReadEvent(IORequestReadEventPtr &event);

        void HandleRequestWriteEvent(IORequestWriteEventPtr &event);

        void HandleNotifyNewFilesystemEvent(IONotifyNewFilesystemEventPtr &event);

        void HandleNotifyReplaceFilesystemEvent(IONotifyReplaceFilesystemEventPtr &event);

        void HandleNotifyDeleteFilesystemEvent(IONotifyDeleteFilesystemEventPtr &event);

    protected:
        std::unordered_map<std::string, FilesystemPtr> mFilesystems;
    };

    typedef std::shared_ptr<IOThreadAsyncEventHandler> IOThreadAsyncEventHandlerPtr;
}
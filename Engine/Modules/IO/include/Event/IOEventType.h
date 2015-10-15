#pragma once

#include <EventModule.h>

namespace SamEngine
{
    class IO_API IOEventType
    {
    public:
        static const EventType TypeID = 'IO';

        static const EventID RequestReadEventID = RequestEventIDOfIndex(1);
        static const EventID RequestWriteEventID = RequestEventIDOfIndex(2);
        static const EventID InvalidRequestEventID = RequestEventIDOfIndex(3);
        static const uint32 RequestEventCount = 2;

        static const EventID InvalidResponseEventID = ResponseEventIDOfIndex(1);
        static const uint32 ResponseEventCount = 0;

        static const EventID NotifyNewFilesystemEventID = NotifyEventIDOfIndex(1);
        static const EventID NotifyReplaceFilesystemEventID = NotifyEventIDOfIndex(2);
        static const EventID NotifyDeleteFilesystemEventID = NotifyEventIDOfIndex(3);
        static const EventID InvalidNotifyEventID = NotifyEventIDOfIndex(4);
        static const uint32 NotifyEventCount = 3;
    };
}
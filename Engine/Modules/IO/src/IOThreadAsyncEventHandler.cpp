#include "IOThreadAsyncEventHandler.h"

namespace SamEngine
{
    IOThreadAsyncEventHandler::IOThreadAsyncEventHandler()
    {
        SetWaitTime(100);
    }

    bool IOThreadAsyncEventHandler::Handle(const EventPtr event)
    {
        return ThreadAsyncEventHandler::Handle(event);
    }

    void IOThreadAsyncEventHandler::EnterThread()
    {
        ThreadAsyncEventHandler::EnterThread();
        mWorker = std::static_pointer_cast<IEventHandler>(mEventDispather);
    }

    void IOThreadAsyncEventHandler::ExitThread()
    {
        mWorker.reset();
        ThreadAsyncEventHandler::ExitThread();
    }
}
#include "AsyncEventHandler.h"

namespace SamEngine
{
    bool AsyncEventHandler::Handle(const EventPtr &event)
    {
        event->SetHandling();
        mCache.push(event);
        return true;
    }

    void AsyncEventHandler::Dispatch()
    {
        if (mWorker != nullptr)
        {
            while (!mCache.empty())
            {
                mWorker->Handle(mCache.front());
                mCache.pop();
            }
        }
    }

    const IEventHandlerPtr &AsyncEventHandler::GetWorker() const
    {
        return mWorker;
    }

    void AsyncEventHandler::SetWorker(const IEventHandlerPtr &handler)
    {
        mWorker = handler;
    }
}
#pragma once

#include "IEventHandler.h"

#include <queue>

namespace SamEngine
{
    class EVENT_API AsyncEventHandler : public IEventHandler
    {
    public:
        virtual bool Handle(const EventPtr event) override;

        void Dispatch();

        IEventHandlerPtr GetWorker() const;

        void SetWorker(const IEventHandlerPtr handler);

    private:
        IEventHandlerPtr mWorker{ nullptr };
        std::queue<EventPtr> mCache;
    };
}
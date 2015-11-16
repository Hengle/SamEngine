#pragma once

#include "Event.h"

#include <memory>

namespace SamEngine
{
    class EVENT_API IEventHandler
    {
    public:
        virtual ~IEventHandler() {}

        virtual bool Handle(const EventPtr event) = 0;
    };

    typedef std::shared_ptr<IEventHandler> IEventHandlerPtr;
}
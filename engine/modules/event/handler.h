#pragma once

#include "event.h"

#include <memory>

namespace sam
{
    class handler
    {
    public:
        virtual ~handler() {}

        virtual bool dispatch(const event_ptr &e) { return false; }

        virtual void handle() {}
    };

    typedef std::shared_ptr<handler> handler_ptr;
}
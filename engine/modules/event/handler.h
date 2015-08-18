#pragma once

#include "event.h"

#include <memory>

namespace sam
{
    class handler
    {
    public:
        virtual ~handler() {}

        virtual bool handle(const event_ptr &e) { return false; }
    };

    typedef std::shared_ptr<handler> handler_ptr;
}
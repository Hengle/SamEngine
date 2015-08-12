#pragma once

#include "event.h"

#include "core/class.h"

#include <memory>

namespace sam
{
    class handler
    {
    public:
        CREATE_FUNC_DECLARE(handler)

        handler() {}

        virtual ~handler() {}

        virtual bool notify(const event_ptr &e) { return false; }

        virtual void handle() {}
    };

    typedef std::shared_ptr<handler> handler_ptr;
}
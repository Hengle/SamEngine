#pragma once

#include "core/class.h"

#include "event/event.h"

namespace sam
{
    class io_request_event : public event
    {
    public:
        CREATE_FUNC_DECLARE(io_request_event)

        io_request_event();

        virtual ~io_request_event();

        static const id id = 0;
    };

    typedef std::shared_ptr<io_request_event> io_request_event_ptr;
}
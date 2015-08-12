#pragma once

#include "event/event.h"

namespace sam
{
    class io_event_type
    {
    public:
        static const int32 count = 1;

        static const event::type type = 'I';
    };
}
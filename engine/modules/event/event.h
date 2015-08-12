#pragma once

#include "core/assert.h"
#include "core/class.h"
#include "core/types.h"

namespace sam
{
    class event
    {
    public:
        enum class status
        {
            pending,
            handling,
            complete,
            cancelled,
        };

        typedef int32 id;

        typedef int32 type;

        static const id invalid_id = (id) 0;

        CREATE_FUNC_DECLARE(event)

        event() : event_id(invalid_id), event_status(status::pending) {}

        virtual ~event() { s_assert(event_status == status::complete || event_status == status::cancelled); }

        bool is_type_of(type t) { return false; }

        id get_id() { return event_id; }

        status get_status() { return event_status; }

        void handle() { s_assert(event_status == status::pending); event_status = status::handling; }

        void finish() { s_assert(event_status == status::handling); event_status = status::complete; }

        void cancel() { event_status = status::cancelled; }

    protected:
        id event_id;
        status event_status;
    };

    typedef std::shared_ptr<event> event_ptr;
}
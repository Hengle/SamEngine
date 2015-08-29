#pragma once

#include "core/assert.h"
#include "core/class.h"
#include "core/types.h"

#define gen_request_id(i) (i << event::request_id_offset & event::request_id_mask)
#define gen_response_id(i) (i << event::response_id_offset & event::response_id_mask)
#define gen_notify_id(i) (i << event::notify_id_offset & event::notify_id_mask)

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

        typedef uint32 id;

        typedef uint32 type;

        static const id invalid_id = static_cast<id>(0);

        static const uint32 request_id_mask = 0x00000fff;

        static const uint32 request_id_offset = 0;

        static const uint32 response_id_mask = 0x00fff000;

        static const uint32 response_id_offset = 12;

        static const uint32 notify_id_mask = 0xff000000;

        static const uint32 notify_id_offset = 24;

        static uint32 request_id_to_idx(id i) { return (i & request_id_mask) >> request_id_offset; }

        static uint32 response_id_to_idx(id i) { return (i & response_id_mask) >> response_id_offset; }

        static uint32 notify_id_to_idx(id i) { return (i & notify_id_mask) >> notify_id_offset; }

        static bool id_is_request(uint32 i) { return (i & request_id_mask) != 0; }

        static bool id_is_response(uint32 i) { return (i & response_id_mask) != 0; }

        static bool id_is_notify(uint32 i) { return (i & notify_id_mask) != 0; }

        CREATE_FUNC_DECLARE(event)

        event() {}

        explicit event(id event_id) : event_id(event_id) {}

        virtual ~event() { s_assert(event_status == status::complete || event_status == status::cancelled); }

        virtual bool is_type_of(type t) { return false; }

        bool is_request() const { return (event_id & request_id_mask) != 0; }

        bool is_response() const { return (event_id & response_id_mask) != 0; }

        bool is_notify() const { return (event_id & notify_id_mask) != 0; }

        id get_id() const { return event_id; }

        status get_status() const { return event_status; }

        void set_handling() { s_assert(event_status == status::pending || is_notify()); event_status = status::handling; }

        void set_completed() { s_assert(event_status == status::handling || is_notify()); event_status = status::complete; }

        void set_cancelled() { event_status = status::cancelled; }

    protected:
        id event_id = invalid_id;
        status event_status = status::pending;
    };

    typedef std::shared_ptr<event> event_ptr;
}
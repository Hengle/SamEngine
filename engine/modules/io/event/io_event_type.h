#pragma once

#include "event/event.h"

namespace sam
{
    class io_event_type
    {
    public:
        static const event::type type = 'I';

		static const event::id request_location = gen_request_id(1);
		static const int32 request_invalid = 2;

		static const event::id response_location = gen_response_id(1);
		static const int32 response_invalid = 2;

		static const event::id notify_new_filesystem = gen_notify_id(1);
		static const event::id notify_replace_filesystem = gen_notify_id(2);
		static const event::id notify_delete_filesystem = gen_notify_id(3);
		static const int32 notify_invalid = 4;
    };
}
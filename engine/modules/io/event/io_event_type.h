#pragma once

#include "event/event.h"

namespace sam
{
    class io_event_type
    {
    public:
        static const event::type type = 'I';

		static const event::id request_url = gen_request_id(0);
		static const int32 request_count = 1;

		static const int32 response_count = 0;

		static const event::id notify_new_filesystem = gen_notify_id(0);
		static const event::id notify_replace_filesystem = gen_notify_id(1);
		static const event::id notify_delete_filesystem = gen_notify_id(2);
		static const int32 notify_count = 3;
    };
}
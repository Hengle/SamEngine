#pragma once

#include "io_event_type.h"

#include "io/filesystem/location.h"

#include "core/class.h"

#include "event/event.h"

namespace sam
{
    class io_request_location_event : public event
    {
    public:
        CREATE_FUNC_DECLARE(io_request_location_event)

		io_request_location_event() : event(id) {}

        virtual ~io_request_location_event() {}

		bool is_type_of(type t) override { return t == io_event_type::type; }

        static const id id = io_event_type::request_location;

		const location &get_location() const { return location; }

		void set_location(const location &value) { location = value; }

	private:
		location location;
    };

    typedef std::shared_ptr<io_request_location_event> io_request_location_event_ptr;
}
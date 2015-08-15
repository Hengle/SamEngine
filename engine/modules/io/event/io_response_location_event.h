#pragma once

#include "io_event_type.h"

#include "io/filesystem/location.h"

#include "core/class.h"
#include "core/data.h"

#include "event/event.h"

namespace sam
{
    class io_response_location_event : public event
    {
	public:
		CREATE_FUNC_DECLARE(io_response_location_event)

		io_response_location_event() {}

		virtual ~io_response_location_event() {}

		bool is_type_of(type t) override { return t == io_event_type::type; }

		static const id id = io_event_type::response_location;

		const location &get_location() const { return location; }

		void set_location(const location &value) { location = value; }

		const data_ptr &get_data() const { return data; };

		void set_data(const data_ptr &value) { data = value; }

	private:
		location location;
		data_ptr data;
    };

	typedef std::shared_ptr<io_response_location_event> io_response_location_event_ptr;
}
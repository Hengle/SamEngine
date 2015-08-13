#pragma once

#include "io_event_type.h"

#include "io/filesystem/url.h"

#include "core/class.h"

#include "event/event.h"

namespace sam
{
    class io_request_url_event : public event
    {
    public:
        CREATE_FUNC_DECLARE(io_request_url_event)

        io_request_url_event() : event(id) {}

        virtual ~io_request_url_event() {}

		bool is_type_of(type t) override { return t == io_event_type::type; }

        static const id id = io_event_type::request_url;

		const url &get_url() const { return url; }

		void set_url(const url &value) { url = value; }

	private:
		url url;
    };

    typedef std::shared_ptr<io_request_url_event> io_request_url_event_ptr;
}
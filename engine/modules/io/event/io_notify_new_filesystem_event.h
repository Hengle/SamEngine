#pragma once

#include "io_event_type.h"

#include <core/class.h>
#include <event/event.h>

namespace sam
{
    class io_notify_new_filesystem_event : public event
    {
    public:
        CREATE_FUNC_DECLARE(io_notify_new_filesystem_event)

        io_notify_new_filesystem_event() : event(id) {}

        virtual bool is_type_of(type t) override { return t == io_event_type::type; }

        static const id id = io_event_type::notify_new_filesystem;

        const std::string &get_filesystem() const { return filesystem; }

        void set_filesystem(const std::string &value) { filesystem = value; }

    private:
        std::string filesystem;
    };

    typedef std::shared_ptr<io_notify_new_filesystem_event> io_notify_new_filesystem_event_ptr;
}
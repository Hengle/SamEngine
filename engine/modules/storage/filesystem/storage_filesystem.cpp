#include "storage_filesystem.h"

#include "storage/storage.h"

#include <io/event/io_event_type.h>
#include <io/event/io_request_read_event.h>
#include <io/event/io_request_write_event.h>

namespace sam
{
    storage_filesystem::storage_filesystem()
    {
    }

    storage_filesystem::~storage_filesystem()
    {
    }

    bool storage_filesystem::handle(const event_ptr &e)
    {
        if (e->get_id() == io_event_type::request_read)
        {
            auto read_event = std::dynamic_pointer_cast<io_request_read_event>(e);
            read_event->set_data(storage::read(read_event->get_location().get_path()));
        }
        else if (e->get_id() == io_event_type::request_write)
        {
            auto write_event = std::dynamic_pointer_cast<io_request_write_event>(e);
            storage::write(write_event->get_location().get_path(), write_event->get_data());
        }
        else
        {
            s_error("storage filesystem: invalid event!\n");
        }
        e->set_completed();
        return true;
    }
}
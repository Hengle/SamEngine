#include "http_filesystem.h"
#include "http/http.h"

#include <io/event/io_event_type.h>
#include <io/event/io_request_read_event.h>

namespace sam
{
    bool http_filesystem::handle(const event_ptr &e)
    {
        if (e->get_id() == io_event_type::request_read)
        {
            auto read_event = std::static_pointer_cast<io_request_read_event>(e);
            read_event->set_data(http::read(read_event->get_location().get_raw()));
        }
        else
        {
            s_error("storage filesystem: invalid event!\n");
        }
        e->set_completed();
        return true;
    }
}
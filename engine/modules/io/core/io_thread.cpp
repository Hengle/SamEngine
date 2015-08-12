#include "io_thread.h"

#include "io/event/io_event_type.h"

#include "event/dispatcher.h"

namespace sam
{
    io_thread::io_thread()
    {
        set_wait_time(100);
    }

    io_thread::~io_thread()
    {
    }

    void io_thread::enter_thread()
    {
        threading_handler::enter_thread();
        auto event_dispatcher = dispatcher<io_event_type>::create();
        event_dispatcher->reg<io_request_event>(std::bind(&io_thread::handle_request_event, this, std::placeholders::_1));
        dst_handler = event_dispatcher;
    }

    void io_thread::leave_thread()
    {
        dst_handler.reset();
        threading_handler::leave_thread();
    }

    void io_thread::forward_handle()
    {
        threading_handler::forward_handle();
    }

    void io_thread::handle_request_event(io_request_event_ptr &e)
    {

    }
}
#pragma once

#include "io/event/io_request_event.h"

#include "event/threading_handler.h"

namespace sam
{
    class io_thread : public threading_handler
    {
    public:
        CREATE_FUNC_DECLARE(io_thread)

        io_thread();

        virtual ~io_thread();

    protected:
        virtual void enter_thread() override;

        virtual void leave_thread() override;

        virtual void forward_handle() override;

    private:
        void handle_request_event(io_request_event_ptr &e);
    };

    typedef std::shared_ptr<io_thread> io_thread_ptr;
}
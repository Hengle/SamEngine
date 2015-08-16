#include "io_thread.h"

#include "io/io.h"

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
        event_dispatcher->reg<io_request_location_event>(std::bind(&io_thread::handle_request_location_event, this, std::placeholders::_1));
		event_dispatcher->reg<io_notify_new_filesystem_event>(std::bind(&io_thread::handle_notify_new_filesystem_event, this, std::placeholders::_1));
		event_dispatcher->reg<io_notify_replace_filesystem_event>(std::bind(&io_thread::handle_notify_replace_filesystem_event, this, std::placeholders::_1));
		event_dispatcher->reg<io_notify_delete_filesystem_event>(std::bind(&io_thread::handle_notify_delete_filesystem_event, this, std::placeholders::_1));
        dst_handler = event_dispatcher;
    }

    void io_thread::leave_thread()
    {
        dst_handler.reset();
		filesystems.clear();
        threading_handler::leave_thread();
    }

    void io_thread::forward_handle()
    {
        threading_handler::forward_handle();
		for (auto i : filesystems)
		{
			i.second->handle();
		}
    }

    void io_thread::handle_request_location_event(io_request_location_event_ptr &e)
    {
        auto iterator = filesystems.find(e->get_location().get_filesystem());
		if (iterator != filesystems.end())
		{
			auto fs = iterator->second;
			s_assert(fs != nullptr);
			if (fs->dispatch(e))
			{
				e->handle();
			}
		}
    }

	void io_thread::handle_notify_new_filesystem_event(io_notify_new_filesystem_event_ptr &e)
	{
		auto name = e->get_filesystem();
		auto creator = io::get_filesystem(name);
		s_assert(creator != nullptr);
		s_assert(filesystems.find(e->get_filesystem()) == filesystems.end());
		filesystems.insert(std::make_pair(name, creator()));
	}

	void io_thread::handle_notify_replace_filesystem_event(io_notify_replace_filesystem_event_ptr &e)
	{
		auto name = e->get_filesystem();
		auto creator = io::get_filesystem(name);
		s_assert(creator != nullptr);
		s_assert(filesystems.find(e->get_filesystem()) != filesystems.end());
		filesystems[name] = creator();
	}

	void io_thread::handle_notify_delete_filesystem_event(io_notify_delete_filesystem_event_ptr &e)
	{
		auto name = e->get_filesystem();
		s_assert(filesystems.find(e->get_filesystem()) != filesystems.end());
		filesystems.erase(name);
	}
}
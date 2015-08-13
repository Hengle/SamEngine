#include "io.h"

#include "core/core.h"

namespace sam
{
    io::state *io::io_state = nullptr;

    io::state::state(const param &p)
    {
        threads.reserve(static_cast<size_t>(p.thread_count));
        for (auto i = 0; i < p.thread_count; ++i)
        {
            auto t = io_thread::create();
            t->start();
            threads.push_back(t);
        }
    }

    io::state::~state()
    {
        for (auto &t : threads)
        {
            t = io_thread::create();
            t->stop();
        }
        threads.clear();
    }

    void io::initialize(const param &p)
    {
        s_assert(!available());
        io_state = new state(p);
        io_state->func_group_id = core::before_frame_func_group->add(std::bind(io::main_loop));
    }

    void io::finalize()
    {
        s_assert(available());
        core::before_frame_func_group->remove(io_state->func_group_id);
        delete io_state;
        io_state = nullptr;
    }

    bool io::available()
    {
        return io_state != nullptr;
    }

	io_request_url_event_ptr io::load(const url &file)
    {
		s_assert(available());
		auto e = io_request_url_event::create();
		e->set_url(file);
		io_state->threads[++io_state->current_thread]->dispatch(e);
		return e;
    }

    void io::dispatch(const io_request_url_event_ptr &e)
    {
		s_assert(available());
		io_state->threads[++io_state->current_thread]->dispatch(e);
    }

	void io::set_filesystem(const std::string &name, filesystem_creator func)
	{
		s_assert(available());
		if (get_filesystem(name) != nullptr)
		{
			if (func == nullptr)
			{
				io_state->fs_registry.erase(name);
				auto e = io_notify_delete_filesystem_event::create();
				for (auto &t : io_state->threads)
				{
					t->dispatch(e);
				}
			}
			else
			{
				io_state->fs_registry[name] = func;
				auto e = io_notify_replace_filesystem_event::create();
				for (auto &t : io_state->threads)
				{
					t->dispatch(e);
				}
			}
		}
		else if (func != nullptr)
		{
			io_state->fs_registry.insert(std::make_pair(name, func));
			auto e = io_notify_new_filesystem_event::create();
			for (auto &t : io_state->threads)
			{
				t->dispatch(e);
			}
		}
	}

	filesystem_creator io::get_filesystem(const std::string &name)
	{
		s_assert(available());
		auto iterator = io_state->fs_registry.find(name);
		if (iterator != io_state->fs_registry.end())
		{
			return iterator->second;
		}
		return nullptr;
	}

	void io::main_loop()
    {
        s_assert(available());
        for (auto &t : io_state->threads)
        {
            t->handle();
        }
    }
}
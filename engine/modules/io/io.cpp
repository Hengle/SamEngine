#include "io.h"

#include "core/core.h"

namespace sam
{
    io::state *io::io_state = nullptr;

    io::state::state(const param &p) :
		current_thread(0),
		router(nullptr),
		func_group_id(func_group::invalid_id)
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
        io_state->func_group_id = core::get_before_frame_func_group()->add(std::bind(io::main_loop));
    }

    void io::finalize()
    {
        s_assert(available());
        core::get_before_frame_func_group()->remove(io_state->func_group_id);
        delete io_state;
        io_state = nullptr;
    }

    bool io::available()
    {
        return io_state != nullptr;
    }

	void io::load(const location &file, callback_func func)
    {
		s_assert(available());
		for (auto i : io_state->loading)
		{
			auto e = i.first;
			if (e->get_location() == file)
			{
				auto v = i.second;
				v.push_back(func);
				return;
			}
		}
		auto e = io_request_location_event::create();
		e->set_location(file);
		if (io_state->router)
		{
			io_state->threads[io_state->router(e, io_state->threads.size())]->dispatch(e);
		}
		else
		{
			io_state->threads[++io_state->current_thread % io_state->threads.size()]->dispatch(e);
		}
		std::vector<callback_func> v;
		v.push_back(func);
		io_state->loading.insert(std::make_pair(e, v));
    }

	void io::set_filesystem(const std::string &name, filesystem::creator func)
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

	filesystem::creator io::get_filesystem(const std::string &name)
	{
		s_assert(available());
		auto iterator = io_state->fs_registry.find(name);
		if (iterator != io_state->fs_registry.end())
		{
			return iterator->second;
		}
		return nullptr;
	}

	void io::set_router(route_func func)
	{
		io_state->router = func;
	}

	io::route_func io::get_router()
	{
		return io_state->router;
	}

	void io::main_loop()
    {
        s_assert(available());
        for (auto &t : io_state->threads)
        {
            t->handle();
        }
		auto i = io_state->loading.begin();
		while (i != io_state->loading.end())
		{
			auto e = i->first;
			if (e->get_status() == event::status::complete)
			{
				auto v = i->second;
				for (auto f : v)
				{
					f(e);
				}
				io_state->loading.erase(i);
			}
			else
			{
				++i;
			}
		}
    }
}

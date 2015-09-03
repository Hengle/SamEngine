#include "io.h"

#include <core/core.h>

namespace sam
{
    io::state *io::io_state = nullptr;

    io::state::state(const io_config &config)
    {
        threads.resize(static_cast<size_t>(config.thread_count));
        for (auto i = 0; i < config.thread_count; ++i)
        {
            threads[i] = io_thread::create();
            threads[i]->start();
        }
        valid = true;
    }

    io::state::~state()
    {
        valid = false;
        for (auto &t : threads)
        {
            t->stop();
        }
        threads.clear();
        for (auto &i : handling)
        {
            auto e = i.first;
            auto f = i.second;
            e->set_cancelled();
            if (f != nullptr)
            {
                f(e);
            }
        }
    }

    void io::initialize(const io_config &config)
    {
        s_assert(!available());
        io_state = new state(config);
        io_state->func_id = core::get_before_frame_func_group()->add(std::bind(io::main_loop));
    }

    void io::finalize()
    {
        s_assert(available());
        core::get_before_frame_func_group()->remove(io_state->func_id);
        delete io_state;
        io_state = nullptr;
    }

    bool io::available()
    {
        return io_state != nullptr && io_state->valid;
    }

    void io::read(const location &file, callback_func func)
    {
        s_assert(available());
        auto e = io_request_read_event::create();
        e->set_location(file);
        handle(e, func);
    }

    void io::write(const location &file, const data_ptr &data, callback_func func)
    {
        s_assert(available());
        auto e = io_request_write_event::create();
        e->set_location(file);
        e->set_data(data);
        handle(e, func);
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
                e->set_filesystem(name);
                for (auto &t : io_state->threads)
                {
                    t->handle(e);
                }
            }
            else
            {
                io_state->fs_registry[name] = func;
                auto e = io_notify_replace_filesystem_event::create();
                e->set_filesystem(name);
                for (auto &t : io_state->threads)
                {
                    t->handle(e);
                }
            }
        }
        else if (func != nullptr)
        {
            io_state->fs_registry.insert(std::make_pair(name, func));
            auto e = io_notify_new_filesystem_event::create();
            e->set_filesystem(name);
            for (auto &t : io_state->threads)
            {
                t->handle(e);
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
            t->dispatch();
        }
        auto i = io_state->handling.begin();
        while (i != io_state->handling.end())
        {
            auto e = i->first;
            if (e->get_status() != event::status::handling)
            {
                auto f = i->second;
                if (f != nullptr)
                {
                    f(e);
                }
                io_state->handling.erase(i++);
            }
            else
            {
                ++i;
            }
        }
    }

    void io::handle(const event_ptr &e, callback_func func)
    {
        if (io_state->router)
        {
            io_state->threads[io_state->router(e, io_state->threads.size())]->handle(e);
        }
        else
        {
            io_state->threads[++io_state->current_thread % io_state->threads.size()]->handle(e);
        }
        io_state->handling.insert(std::make_pair(e, func));
    }
}

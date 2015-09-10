#include "io.h"

#include <core/core.h>

#include <deque>

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
        handling.clear();
        for (auto &i : event2callback)
        {
            auto e = i.first;
            auto f = i.second;
            e->set_cancelled();
            if (f != nullptr)
            {
                f(e);
            }
        }
        event2callback.clear();
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

    void io::read(const std::string &file, callback_func func)
    {
        s_assert(available());
        auto location = file;
        auto e = io_request_read_event::create();
        for (auto pair : io_state->loacation_replacement)
        {
            if (location.find(pair.first) == 0)
            {
                location.replace(0, pair.first.length() + 1, pair.second);
                break;
            }
        }
        e->set_location(location);
        handle(e, func);
    }

    void io::write(const std::string &file, const data_ptr &data, callback_func func)
    {
        s_assert(available());
        auto location = file;
        auto e = io_request_write_event::create();
        for (auto pair : io_state->loacation_replacement)
        {
            if (location.find(pair.first) == 0)
            {
                location.replace(0, pair.first.length() + 1, pair.second);
                break;
            }
        }
        e->set_location(location);
        e->set_data(data);
        handle(e, func);
    }

    void io::set_location_replacement(const std::string &original, const std::string replacement)
    {
        s_assert(available());
        io_state->loacation_replacement.insert_or_assign(original, replacement);
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
            io_state->fs_registry.insert({ name, func });
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
        std::deque<event_ptr> finished;
        for (auto i = io_state->handling.rbegin(); i != io_state->handling.rend();)
        {
            auto e = *i;
            if (e->get_status() != event::status::handling)
            {
                finished.push_front(e);
                i = std::vector<event_ptr>::reverse_iterator(io_state->handling.erase(std::next(i).base()));
            }
            else
            {
                ++i;
            }
        }
        for (auto &e : finished)
        {
            auto i = io_state->event2callback.find(e);
            if (i != io_state->event2callback.end())
            {
                auto f = i->second;
                if (f != nullptr)
                {
                    f(e);
                }
                io_state->event2callback.erase(i);
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
        io_state->handling.push_back(e);
        io_state->event2callback.insert({ e, func });
    }
}

#include "threading_handler.h"

#include "core/core.h"

#include <chrono>

namespace sam
{
    threading_handler::threading_handler() :
        wait_ms(0),
        dst_handler(nullptr),
        current(status::waiting)
    {
        parent = std::this_thread::get_id();
    }

    threading_handler::~threading_handler()
    {
        s_assert(std::this_thread::get_id() == parent);
        s_assert(current == status::stopped);
    }

    bool threading_handler::dispatch(const event_ptr &e)
    {
        s_assert(std::this_thread::get_id() == parent);
        s_assert(current == status::running);
        comming_events.push(e);
        return true;
    }

    void threading_handler::handle()
    {
        s_assert(std::this_thread::get_id() == parent);
        s_assert(current == status::running);
        while (!comming_events.empty())
        {
            queue_lock.lock();
            if (waiting_events.empty())
            {
                waiting_events = std::move(comming_events);
            }
            else
            {
                while (!comming_events.empty())
                {
                    waiting_events.push(comming_events.front());
                    comming_events.pop();
                }
            }
            queue_lock.unlock();
        }
        condition_variable.notify_one();
    }

    void threading_handler::start()
    {
        s_assert(std::this_thread::get_id() == parent);
        s_assert(current == status::waiting);
        worker = std::thread(main_loop, this);
        current = status::running;
    }

    void threading_handler::stop()
    {
        s_assert(current == status::running);
        current = status::stopping;
        condition_variable.notify_one();
        worker.join();
        current = status::stopped;
    }

    void threading_handler::enter_thread()
    {
        core::enter_thread();
    }

    void threading_handler::leave_thread()
    {
        core::leave_thread();
    }

    void threading_handler::forward_notify(const event_ptr &e)
    {
        dst_handler->dispatch(e);
    }

    void threading_handler::forward_handle()
    {
        dst_handler->handle();
    }

    void threading_handler::main_loop(threading_handler *self)
    {
        self->child = std::this_thread::get_id();
        self->enter_thread();
        while (self->current == status::running)
        {
            std::unique_lock<std::mutex> lock(self->mutex);
            if (self->wait_ms == 0)
            {
                self->condition_variable.wait(lock);
            }
            else
            {
                self->condition_variable.wait_for(lock, std::chrono::milliseconds(self->wait_ms));
            }
            lock.unlock();
            s_assert(std::this_thread::get_id() == self->child);
            s_assert(self->forwarding_events.empty());
            self->queue_lock.lock();
            self->forwarding_events = std::move(self->waiting_events);
            self->queue_lock.unlock();
            while (!self->forwarding_events.empty())
            {
                self->forward_notify(self->forwarding_events.front());
                self->forwarding_events.pop();
            }
            self->forward_handle();
        }
        self->leave_thread();
    }
}
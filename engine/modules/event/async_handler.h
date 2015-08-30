#pragma once

#include "handler.h"

#include <queue>

namespace sam
{
    class async_handler : public handler
    {
    public:
        async_handler() {};

        virtual ~async_handler() {};

        virtual bool handle(const event_ptr &e) override
        {
            e->set_handling();
            cache.push(e);
            return true;
        }

        void dispatch()
        {
            if (worker != nullptr)
            {
                while (!cache.empty())
                {
                    worker->handle(cache.front());
                    cache.pop();
                }
            }
        }

        const handler_ptr &get_worker() const
        {
            return worker;
        }

        void set_worker(const handler_ptr &value)
        {
            worker = value;
        }

    private:
        handler_ptr worker{nullptr};
        std::queue<event_ptr> cache;
    };
}
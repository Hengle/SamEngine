#pragma once

#include "handler.h"

#include <queue>

namespace sam
{
    class async_handler : public handler
    {
    public:
        async_handler() : dst_handler(nullptr) {};

        virtual ~async_handler() {};

        virtual bool dispatch(const event_ptr &e) override
        {
            cache.push(e);
            return true;
        }

        virtual void handle() override
        {
            if (dst_handler != nullptr)
            {
                dst_handler->handle();
            }
        }

        void forward()
        {
            if (dst_handler != nullptr)
            {
                while (!cache.empty())
                {
                    dst_handler->dispatch(cache.front());
                    cache.pop();
                }
            }
        }

        const handler_ptr &get_dst_handler() const
        {
            return dst_handler;
        }

        void set_dst_handler(const handler_ptr &value)
        {
            dst_handler = value;
        }

    private:
        handler_ptr dst_handler;
        std::queue<event_ptr> cache;
    };
}
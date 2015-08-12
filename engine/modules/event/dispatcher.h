#pragma once

#include "handler.h"

namespace sam
{
    template <class TYPES>
    class dispatcher : public handler
    {
    public:
        typedef std::function<void(const event_ptr &)> handle_func;

        CREATE_FUNC_DECLARE(dispatcher)

        dispatcher() {}

        virtual ~dispatcher() {}

        virtual bool notify(const event_ptr &e) override;

        template <class EVENT>
        void reg(handle_func func);

        template <class EVENT>
        void unreg();

    private:
        handle_func registry[TYPES::count];
    };

    template <class TYPES>
    bool dispatcher::notify(const event_ptr &e)
    {
        if (e->is_type_of(TYPES::type))
        {
            auto event_id = e->get_id();
            s_assert(event_id >= (int32) event::invalid_id && event_id < TYPES::count);
            if (registry[event_id])
            {
                registry[event_id](e);
                return true;
            }
        }
        return false;
    }

    template <class TYPES> template<class EVENT>
    void dispatcher::reg(dispatcher::handle_func func)
    {
        const event::id event_id = EVENT::id;
        s_assert(event_id >= (int32) event::invalid_id && event_id < TYPES::count);
        registry[event_id] = func;
    }

    template <class TYPES> template<class EVENT>
    void dispatcher::unreg()
    {
        const event::id event_id = EVENT::id;
        s_assert(event_id >= (int32) event::invalid_id && event_id < TYPES::count);
        registry[event_id] = nullptr;
    }
}
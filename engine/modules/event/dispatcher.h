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

        virtual ~dispatcher() {}

        virtual bool handle(const event_ptr &e) override;

        template <class EVENT>
        void reg(std::function<void(std::shared_ptr<EVENT> &)> func);

        template <class EVENT>
        void unreg();

    private:
        handle_func request_registry[TYPES::request_invalid];
        handle_func response_registry[TYPES::response_invalid];
        handle_func notify_registry[TYPES::notify_invalid];
    };

    template <class TYPES>
    bool dispatcher<TYPES>::handle(const event_ptr &e)
    {
        if (e->is_type_of(TYPES::type))
        {
            auto event_id = e->get_id();
            if (e->is_request())
            {
                auto index = event::request_id_to_idx(event_id);
                s_assert_range(index, event::invalid_id, TYPES::request_invalid);
                if (request_registry[index])
                {
                    request_registry[index](e);
                    return true;
                }
            }
            else if (e->is_response())
            {
                auto index = event::response_id_to_idx(event_id);
                s_assert_range(index, event::invalid_id, TYPES::response_invalid);
                if (response_registry[index])
                {
                    response_registry[index](e);
                    return true;
                }
            }
            else if (e->is_notify())
            {
                auto index = event::notify_id_to_idx(event_id);
                s_assert_range(index, event::invalid_id, TYPES::notify_invalid);
                if (notify_registry[index])
                {
                    notify_registry[index](e);
                    return true;
                }
            }
            else
            {
                log::error("invalid event id %d\n", e->get_id());
                return false;
            }
        }
        return false;
    }

    template <class TYPES> template<class EVENT>
    void dispatcher<TYPES>::reg(std::function<void(std::shared_ptr<EVENT> &)> func)
    {
        const event::id event_id = EVENT::id;
        s_assert(sizeof(handle_func) == sizeof(func));
        if (event::id_is_request(event_id))
        {
            auto index = event::request_id_to_idx(event_id);
            s_assert_range(index, event::invalid_id, TYPES::request_invalid);
            request_registry[index] = *reinterpret_cast<handle_func *>(&func);
        }
        else if (event::id_is_response(event_id))
        {
            auto index = event::response_id_to_idx(event_id);
            s_assert_range(index, event::invalid_id, TYPES::response_invalid);
            response_registry[index] = *reinterpret_cast<handle_func *>(&func);
        }
        else if (event::id_is_notify(event_id))
        {
            auto index = event::notify_id_to_idx(event_id);
            s_assert_range(index, event::invalid_id, TYPES::notify_invalid);
            notify_registry[index] = *reinterpret_cast<handle_func *>(&func);
        }
        else
        {
            log::error("invalid event id %d\n", event_id);
        }
    }

    template <class TYPES> template<class EVENT>
    void dispatcher<TYPES>::unreg()
    {
        const event::id event_id = EVENT::id;
        if (event::id_is_request(event_id))
        {
            auto index = event::request_id_to_idx(event_id);
            s_assert_range(index, event::invalid_id, TYPES::request_invalid);
            request_registry[index] = nullptr;
        }
        else if (event::id_is_response(event_id))
        {
            auto index = event::response_id_to_idx(event_id);
            s_assert_range(index, event::invalid_id, TYPES::response_invalid);
            response_registry[index] = nullptr;
        }
        else if (event::id_is_notify(event_id))
        {
            auto index = event::notify_id_to_idx(event_id);
            s_assert_range(index, event::invalid_id, TYPES::notify_invalid);
            notify_registry[index] = nullptr;
        }
        else
        {
            log::error("invalid event id %d\n", event_id);
        }
    }
}
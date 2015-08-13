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

        virtual bool dispatch(const event_ptr &e) override;

        template <class EVENT>
        void reg(std::function<void(std::shared_ptr<EVENT> &)> func);

        template <class EVENT>
        void unreg();

    private:
        handle_func request_registry[TYPES::request_count + 1];
		handle_func response_registry[TYPES::response_count + 1];
		handle_func notify_registry[TYPES::notify_count + 1];
    };

    template <class TYPES>
    bool dispatcher<TYPES>::dispatch(const event_ptr &e)
    {
        if (e->is_type_of(TYPES::type))
        {
            auto event_id = e->get_id();
			if (e->is_request())
			{
				s_assert(event_id >= 0 && event_id < TYPES::request_count);
				if (request_registry[event_id])
				{
					request_registry[event_id](e);
					return true;
				}
			}
			else if (e->is_response())
			{
				s_assert(event_id >= 0 && event_id < TYPES::response_count);
				if (response_registry[event_id])
				{
					response_registry[event_id](e);
					return true;
				}
			}
			else if (e->is_notify())
			{
				s_assert(event_id >= 0 && event_id < TYPES::notify_count);
				if (notify_registry[event_id])
				{
					notify_registry[event_id](e);
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
			s_assert(event_id >= 0 && event_id < TYPES::request_count);
			request_registry[event_id] = *reinterpret_cast<handle_func *>(&func);
		}
		else if (event::id_is_response(event_id))
		{
			s_assert(event_id >= 0 && event_id < TYPES::response_count);
			response_registry[event_id] = *reinterpret_cast<handle_func *>(&func);
		}
		else if (event::id_is_notify(event_id))
		{
			s_assert(event_id >= 0 && event_id < TYPES::notify_count);
			notify_registry[event_id] = *reinterpret_cast<handle_func *>(&func);
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
        s_assert(event_id >= static_cast<int32>(event::invalid_id) && event_id < TYPES::count);
		if (event::id_is_request(event_id))
		{
			s_assert(event_id >= 0 && event_id < TYPES::request_count);
			request_registry[event_id] = nullptr;
		}
		else if (event::id_is_response(event_id))
		{
			s_assert(event_id >= 0 && event_id < TYPES::response_count);
			response_registry[event_id] = nullptr;
		}
		else if (event::id_is_notify(event_id))
		{
			s_assert(event_id >= 0 && event_id < TYPES::notify_count);
			notify_registry[event_id] = nullptr;
		}
		else
		{
			log::error("invalid event id %d\n", event_id);
		}
    }
}
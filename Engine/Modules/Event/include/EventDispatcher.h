#pragma once

#include "IEventHandler.h"

#include <CoreModule.h>

namespace SamEngine
{
    typedef std::function<void(const EventPtr)> EventDispatherFunction;

    template <class TYPES>
    class EventDispatcher : public IEventHandler
    {
    public:
        CREATE_FUNC_DECLARE(EventDispatcher)

        bool Handle(const EventPtr event) override;

        template <class EVENT>
        void Register(std::function<void(std::shared_ptr<EVENT>)> function);

        template <class EVENT>
        void Unregister();

    private:
        EventDispatherFunction mRequestRegistry[TYPES::RequestEventCount + 1];
        EventDispatherFunction mResponseRegistry[TYPES::ResponseEventCount + 1];
        EventDispatherFunction mNotifyRegistry[TYPES::NotifyEventCount + 1];
    };

    template <class TYPES>
    bool EventDispatcher<TYPES>::Handle(const EventPtr event)
    {
        if (event->IsTypeOf(TYPES::TypeID))
        {
            auto id = event->GetID();
            if (event->IsRequest())
            {
                s_assert_range(id, InvalidEventID + 1, TYPES::InvalidRequestEventID - 1);
                auto index = GetRequestIndexOfEventID(id);
                if (mRequestRegistry[index])
                {
                    mRequestRegistry[index](event);
                    return true;
                }
            }
            else if (event->IsResponse())
            {
                s_assert_range(id, InvalidEventID + 1, TYPES::InvalidResponseEventID - 1);
                auto index = GetResponseIndexOfEventID(id);
                if (mResponseRegistry[index])
                {
                    mResponseRegistry[index](event);
                    return true;
                }
            }
            else if (event->IsNotify())
            {
                s_assert_range(id, InvalidEventID + 1, TYPES::InvalidNotifyEventID - 1);
                auto index = GetNotifyIndexOfEventID(id);
                if (mNotifyRegistry[index])
                {
                    mNotifyRegistry[index](event);
                    return true;
                }
            }
            else
            {
                GetLog().Error("[Dispather] invalid event id %d\n", id);
                return false;
            }
        }
        return false;
    }

    template <class TYPES>
    template <class EVENT>
    void EventDispatcher<TYPES>::Register(std::function<void(std::shared_ptr<EVENT>)> function)
    {
        const auto id = EVENT::ID;
        s_assert(sizeof(EventDispatherFunction) == sizeof(function));
        if (IsRequestEventID(id))
        {
            s_assert_range(id, InvalidEventID + 1, TYPES::InvalidRequestEventID - 1);
            mRequestRegistry[GetRequestIndexOfEventID(id)] = *reinterpret_cast<EventDispatherFunction *>(&function);
        }
        else if (IsResponseEventID(id))
        {
            s_assert_range(id, InvalidEventID + 1, TYPES::InvalidResponseEventID - 1);
            mResponseRegistry[GetResponseIndexOfEventID(id)] = *reinterpret_cast<EventDispatherFunction *>(&function);
        }
        else if (IsNotifyEventID(id))
        {
            s_assert_range(id, InvalidEventID + 1, TYPES::InvalidNotifyEventID - 1);
            mNotifyRegistry[GetNotifyIndexOfEventID(id)] = *reinterpret_cast<EventDispatherFunction *>(&function);
        }
        else
        {
            GetLog().Error("[Dispather] invalid event id %d\n", id);
        }
    }

    template <class TYPES>
    template <class EVENT>
    void EventDispatcher<TYPES>::Unregister()
    {
        const auto id = EVENT::ID;
        if (IsRequestEventID(id))
        {
            s_assert_range(id, InvalidEventID + 1, TYPES::InvalidRequestEventID - 1);
            mRequestRegistry[GetRequestIndexOfEventID(id)] = nullptr;
        }
        else if (IsResponseEventID(id))
        {
            s_assert_range(id, InvalidEventID + 1, TYPES::InvalidResponseEventID - 1);
            mResponseRegistry[GetResponseIndexOfEventID(id)] = nullptr;
        }
        else if (IsNotifyEventID(id))
        {
            s_assert_range(id, InvalidEventID + 1, TYPES::InvalidNotifyEventID - 1);
            mNotifyRegistry[GetNotifyIndexOfEventID(id)] = nullptr;
        }
        else
        {
            GetLog().Error("[Dispather] invalid event id %d\n", id);
        }
    }
}
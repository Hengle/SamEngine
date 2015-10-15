#pragma once

#include <CoreModule.h>

#define RequestEventIDOfIndex(index) (index << RequestOffsetOfEventID & RequestMaskOfEventID)
#define ResponseEventIDOfIndex(index) (index << ResponseOffsetOfEventID & ResponseMaskOfEventID)
#define NotifyEventIDOfIndex(index) (index << NotifyOffsetOfEventID & NotifyMaskOfEventID)

namespace SamEngine
{
    enum class EventStatus : uint8
    {
        PENDING,
        HANDLING,
        COMPLETE,
        CANCELLED,
    };

    typedef uint32 EventID;

    typedef uint32 EventType;

    static const EventID InvalidEventID{ 0 };

    enum
    {
        RequestMaskOfEventID = 0x00000fff,
        RequestOffsetOfEventID = 0,

        ResponseMaskOfEventID = 0x00fff000,
        ResponseOffsetOfEventID = 12,

        NotifyMaskOfEventID = 0xff000000,
        NotifyOffsetOfEventID = 24,
    };

    inline uint32 GetRequestIndexOfEventID(EventID id) { return (id & RequestMaskOfEventID) >> RequestOffsetOfEventID; }

    inline uint32 GetResponseIndexOfEventID(EventID id) { return (id & ResponseMaskOfEventID) >> ResponseOffsetOfEventID; }

    inline uint32 GetNotifyIndexOfEventID(EventID id) { return (id & NotifyMaskOfEventID) >> NotifyOffsetOfEventID; }

    inline bool IsRequestEventID(uint32 id) { return (id & RequestMaskOfEventID) != 0; }

    inline bool IsResponseEventID(uint32 id) { return (id & ResponseMaskOfEventID) != 0; }

    inline bool IsNotifyEventID(uint32 id) { return (id & NotifyMaskOfEventID) != 0; }

    class EVENT_API Event
    {
    public:
        CREATE_FUNC_DECLARE(Event)

        explicit Event(EventID id) : mEventID(id) {}

        virtual ~Event() { s_assert(mEventStatus == EventStatus::COMPLETE || mEventStatus == EventStatus::CANCELLED); }

        virtual bool IsTypeOf(EventType type) { return false; }

        bool IsRequest() const { return IsRequestEventID(mEventID); }

        bool IsResponse() const { return IsResponseEventID(mEventID); }

        bool IsNotify() const { return IsNotifyEventID(mEventID); }

        EventID GetID() const { return mEventID; }

        EventStatus GetStatus() const { return mEventStatus; }

        void SetHandling() { s_assert(mEventStatus == EventStatus::PENDING || IsNotify()); mEventStatus = EventStatus::HANDLING; }

        void SetCompleted() { s_assert(mEventStatus == EventStatus::HANDLING || IsNotify()); mEventStatus = EventStatus::COMPLETE; }

        void SetCancelled() { mEventStatus = EventStatus::CANCELLED; }

    protected:
        EventID mEventID{ InvalidEventID };
        EventStatus mEventStatus{ EventStatus::PENDING };
    };

    typedef std::shared_ptr<Event> EventPtr;
}
#pragma once

#include "IOEventType.h"

namespace SamEngine
{
    class IO_API IONotifyDeleteFilesystemEvent : public Event
    {
    public:
        CREATE_FUNC_DECLARE(IONotifyDeleteFilesystemEvent)

        IONotifyDeleteFilesystemEvent() : Event(ID) {}

        bool IsTypeOf(EventType type) override { return type == IOEventType::TypeID; }

        static const EventID ID = IOEventType::NotifyDeleteFilesystemEventID;

        const std::string &GetFilesystemName() const { return mFilesystemName; }

        void SetFilesystemName(const std::string &value) { mFilesystemName = value; }

    private:
        std::string mFilesystemName;
    };

    typedef std::shared_ptr<IONotifyDeleteFilesystemEvent> IONotifyDeleteFilesystemEventPtr;
}
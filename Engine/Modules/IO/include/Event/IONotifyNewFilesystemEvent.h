#pragma once

#include "IOEventType.h"

namespace SamEngine
{
    class IO_API IONotifyNewFilesystemEvent : public Event
    {
    public:
        CREATE_FUNC_DECLARE(IONotifyNewFilesystemEvent)

        IONotifyNewFilesystemEvent() : Event(ID) {}

        virtual bool IsTypeOf(EventType type) override { return type == IOEventType::TypeID; }

        static const EventID ID = IOEventType::NotifyNewFilesystemEventID;

        const std::string &GetFilesystemName() const { return mFilesystemName; }

        void SetFilesystemName(const std::string &value) { mFilesystemName = value; }

    private:
        std::string mFilesystemName;
    };

    typedef std::shared_ptr<IONotifyNewFilesystemEvent> IONotifyNewFilesystemEventPtr;
}
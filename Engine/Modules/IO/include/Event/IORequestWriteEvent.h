#pragma once

#include "IOEventType.h"
#include "Filesystem/Location.h"

namespace SamEngine
{
    class IO_API IORequestWriteEvent : public Event
    {
    public:
        CREATE_FUNC_DECLARE(IORequestWriteEvent)

        IORequestWriteEvent() : Event(ID) {}

        bool IsTypeOf(EventType type) override { return type == IOEventType::TypeID; }

        static const EventID ID = IOEventType::RequestWriteEventID;

        const Location &GetLocation() const { return mLocation; }

        void SetLocation(const Location &value) { mLocation = value; }

        DataPtr GetData() const { return mData; }

        void SetData(DataPtr value) { mData = value; }

    private:
        Location mLocation;
        DataPtr mData;
    };

    typedef std::shared_ptr<IORequestWriteEvent> IORequestWriteEventPtr;
}
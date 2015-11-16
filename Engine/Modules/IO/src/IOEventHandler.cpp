#include "IOEventHandler.h"

#include "IIO.h"

namespace SamEngine
{
    IOEventHandler::IOEventHandler()
    {
        mEventDispather = EventDispatcher<IOEventType>::Create();
        mEventDispather->Register<IORequestReadEvent>(std::bind(&IOEventHandler::HandleRequestReadEvent, this, std::placeholders::_1));
        mEventDispather->Register<IORequestWriteEvent>(std::bind(&IOEventHandler::HandleRequestWriteEvent, this, std::placeholders::_1));
        mEventDispather->Register<IONotifyNewFilesystemEvent>(std::bind(&IOEventHandler::HandleNotifyNewFilesystemEvent, this, std::placeholders::_1));
        mEventDispather->Register<IONotifyReplaceFilesystemEvent>(std::bind(&IOEventHandler::HandleNotifyReplaceFilesystemEvent, this, std::placeholders::_1));
        mEventDispather->Register<IONotifyDeleteFilesystemEvent>(std::bind(&IOEventHandler::HandleNotifyDeleteFilesystemEvent, this, std::placeholders::_1));
    }

    bool IOEventHandler::Handle(EventPtr event)
    {
        event->SetHandling();
        return mEventDispather->Handle(event);
    }

    void IOEventHandler::HandleRequestReadEvent(IORequestReadEventPtr event)
    {
        auto iterator = mFilesystems.find(event->GetLocation().GetFilesystemName());
        if (iterator != mFilesystems.end())
        {
            auto filesystem = iterator->second;
            s_assert(filesystem != nullptr);
            filesystem->Handle(event);
        }
    }

    void IOEventHandler::HandleRequestWriteEvent(IORequestWriteEventPtr event)
    {
        auto iterator = mFilesystems.find(event->GetLocation().GetFilesystemName());
        if (iterator != mFilesystems.end())
        {
            auto filesystem = iterator->second;
            s_assert(filesystem != nullptr);
            filesystem->Handle(event);
        }
    }

    void IOEventHandler::HandleNotifyNewFilesystemEvent(IONotifyNewFilesystemEventPtr event)
    {
        auto name = event->GetFilesystemName();
        auto creator = GetIO().GetFilesystemCreator(name);
        s_assert(creator != nullptr);
        s_assert(mFilesystems.find(event->GetFilesystemName()) == mFilesystems.end());
        mFilesystems.insert({ name, creator() });
        event->SetCompleted();
    }

    void IOEventHandler::HandleNotifyReplaceFilesystemEvent(IONotifyReplaceFilesystemEventPtr event)
    {
        auto name = event->GetFilesystemName();
        auto creator = GetIO().GetFilesystemCreator(name);
        s_assert(creator != nullptr);
        s_assert(mFilesystems.find(event->GetFilesystemName()) != mFilesystems.end());
        mFilesystems[name] = creator();
        event->SetCompleted();
    }

    void IOEventHandler::HandleNotifyDeleteFilesystemEvent(IONotifyDeleteFilesystemEventPtr event)
    {
        auto name = event->GetFilesystemName();
        s_assert(mFilesystems.find(event->GetFilesystemName()) != mFilesystems.end());
        mFilesystems.erase(name);
        event->SetCompleted();
    }
}
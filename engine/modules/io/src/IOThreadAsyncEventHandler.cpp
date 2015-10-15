#include "IOThreadAsyncEventHandler.h"

#include "IIO.h"

namespace SamEngine
{
    IOThreadAsyncEventHandler::IOThreadAsyncEventHandler()
    {
        SetWaitTime(100);
    }

    void IOThreadAsyncEventHandler::EnterThread()
    {
        ThreadAsyncEventHandler::EnterThread();
        auto eventDispatcher = EventDispatcher<IOEventType>::Create();
        eventDispatcher->Register<IORequestReadEvent>(std::bind(&IOThreadAsyncEventHandler::HandleRequestReadEvent, this, std::placeholders::_1));
        eventDispatcher->Register<IORequestWriteEvent>(std::bind(&IOThreadAsyncEventHandler::HandleRequestWriteEvent, this, std::placeholders::_1));
        eventDispatcher->Register<IONotifyNewFilesystemEvent>(std::bind(&IOThreadAsyncEventHandler::HandleNotifyNewFilesystemEvent, this, std::placeholders::_1));
        eventDispatcher->Register<IONotifyReplaceFilesystemEvent>(std::bind(&IOThreadAsyncEventHandler::HandleNotifyReplaceFilesystemEvent, this, std::placeholders::_1));
        eventDispatcher->Register<IONotifyDeleteFilesystemEvent>(std::bind(&IOThreadAsyncEventHandler::HandleNotifyDeleteFilesystemEvent, this, std::placeholders::_1));
        mWorker = eventDispatcher;
    }

    void IOThreadAsyncEventHandler::ExitThread()
    {
        mWorker.reset();
        mFilesystems.clear();
        ThreadAsyncEventHandler::ExitThread();
    }

    void IOThreadAsyncEventHandler::HandleRequestReadEvent(IORequestReadEventPtr &event)
    {
        auto iterator = mFilesystems.find(event->GetLocation().GetFilesystemName());
        if (iterator != mFilesystems.end())
        {
            auto filesystem = iterator->second;
            s_assert(filesystem != nullptr);
            filesystem->Handle(event);
        }
    }

    void IOThreadAsyncEventHandler::HandleRequestWriteEvent(IORequestWriteEventPtr &event)
    {
        auto iterator = mFilesystems.find(event->GetLocation().GetFilesystemName());
        if (iterator != mFilesystems.end())
        {
            auto filesystem = iterator->second;
            s_assert(filesystem != nullptr);
            filesystem->Handle(event);
        }
    }

    void IOThreadAsyncEventHandler::HandleNotifyNewFilesystemEvent(IONotifyNewFilesystemEventPtr &event)
    {
        auto name = event->GetFilesystemName();
        auto creator = GetIO().GetFilesystemCreator(name);
        s_assert(creator != nullptr);
        s_assert(mFilesystems.find(event->GetFilesystemName()) == mFilesystems.end());
        mFilesystems.insert({ name, creator() });
        event->SetCompleted();
    }

    void IOThreadAsyncEventHandler::HandleNotifyReplaceFilesystemEvent(IONotifyReplaceFilesystemEventPtr &event)
    {
        auto name = event->GetFilesystemName();
        auto creator = GetIO().GetFilesystemCreator(name);
        s_assert(creator != nullptr);
        s_assert(mFilesystems.find(event->GetFilesystemName()) != mFilesystems.end());
        mFilesystems[name] = creator();
        event->SetCompleted();
    }

    void IOThreadAsyncEventHandler::HandleNotifyDeleteFilesystemEvent(IONotifyDeleteFilesystemEventPtr &event)
    {
        auto name = event->GetFilesystemName();
        s_assert(mFilesystems.find(event->GetFilesystemName()) != mFilesystems.end());
        mFilesystems.erase(name);
        event->SetCompleted();
    }
}
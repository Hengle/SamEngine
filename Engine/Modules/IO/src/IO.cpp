#include "IO.h"

#include <deque>

namespace SamEngine
{
    void IO::Initialize(int32 threadCount)
    {
        s_assert(!Available());
        mEventHandler = IOEventHandler::Create();
        mAsyncEventHandlers.resize(static_cast<size_t>(threadCount));
        for (auto i = 0; i < threadCount; ++i)
        {
            mAsyncEventHandlers[i] = IOThreadAsyncEventHandler::Create();
            mAsyncEventHandlers[i]->Start();
        }
        mValid = true;
        mTickID = GetThread().GetTicker().Add(this);
    }

    void IO::Finalize()
    {
        s_assert(Available());
        GetThread().GetTicker().Remove(mTickID);
        mValid = false;
        for (auto &thread : mAsyncEventHandlers)
        {
            thread->Stop();
        }
        mAsyncEventHandlers.clear();
        mHandlingEvents.clear();
        for (auto &iterator : mEvent2Callback)
        {
            auto event = iterator.first;
            auto callback = iterator.second;
            event->SetCancelled();
            if (callback != nullptr)
            {
                callback(event);
            }
        }
        mEvent2Callback.clear();
    }

    bool IO::Available()
    {
        return mValid;
    }

    DataPtr IO::Read(const std::string &file)
    {
        s_assert(Available());
        auto event = IORequestReadEvent::Create();
        event->SetLocation(ResolveLocation(file));
        mEventHandler->Handle(event);
        return event->GetData();
    }

    void IO::Write(const std::string &file, DataPtr data)
    {
        s_assert(Available());
        auto event = IORequestWriteEvent::Create();
        event->SetLocation(ResolveLocation(file));
        event->SetData(data);
        mEventHandler->Handle(event);
    }

    void IO::AsyncRead(const std::string &file, IOCallbackFunction callback)
    {
        s_assert(Available());
        auto event = IORequestReadEvent::Create();
        event->SetLocation(ResolveLocation(file));
        AsyncHandle(event, callback);
    }

    void IO::AsyncWrite(const std::string &file, DataPtr data, IOCallbackFunction callback)
    {
        s_assert(Available());
        auto event = IORequestWriteEvent::Create();
        event->SetLocation(ResolveLocation(file));
        event->SetData(data);
        AsyncHandle(event, callback);
    }

    void IO::SetLocationPlaceholder(const std::string &original, const std::string &replacement)
    {
        s_assert(Available());
        mLocationPlaceholder.insert({ original, replacement });
    }

    void IO::SetFilesystemCreator(const std::string &name, Filesystem::Creator function)
    {
        s_assert(Available());
        if (GetFilesystemCreator(name) != nullptr)
        {
            if (function == nullptr)
            {
                mFilesystemCreatorRegistery.erase(name);
                auto event = IONotifyDeleteFilesystemEvent::Create();
                event->SetFilesystemName(name);
                mEventHandler->Handle(event);
                for (auto &thread : mAsyncEventHandlers)
                {
                    thread->Handle(event);
                }
            }
            else
            {
                mFilesystemCreatorRegistery[name] = function;
                auto event = IONotifyReplaceFilesystemEvent::Create();
                event->SetFilesystemName(name);
                mEventHandler->Handle(event);
                for (auto &thread : mAsyncEventHandlers)
                {
                    thread->Handle(event);
                }
            }
        }
        else if (function != nullptr)
        {
            mFilesystemCreatorRegistery.insert({ name, function });
            auto event = IONotifyNewFilesystemEvent::Create();
            event->SetFilesystemName(name);
            mEventHandler->Handle(event);
            for (auto &thread : mAsyncEventHandlers)
            {
                thread->Handle(event);
            }
        }
    }

    Location IO::ResolveLocation(const std::string &file)
    {
        auto location = file;
        for (auto pair : mLocationPlaceholder)
        {
            if (location.find(pair.first) == 0)
            {
                location.replace(0, pair.first.length() + 1, pair.second);
                break;
            }
        }
        return location;
    }

    Filesystem::Creator IO::GetFilesystemCreator(const std::string &name)
    {
        s_assert(Available());
        auto iterator = mFilesystemCreatorRegistery.find(name);
        if (iterator != mFilesystemCreatorRegistery.end())
        {
            return iterator->second;
        }
        return nullptr;
    }

    void IO::SetRouterFunction(IORouterFunction function)
    {
        mRouterFunction = function;
    }

    IORouterFunction IO::GetRouterFunction()
    {
        return mRouterFunction;
    }

    void IO::Tick(TickCount now, TickCount delta)
    {
        s_assert(Available());
        for (auto &thread : mAsyncEventHandlers)
        {
            thread->Dispatch();
        }
        std::deque<EventPtr> finished;
        for (auto iterator = mHandlingEvents.rbegin(); iterator != mHandlingEvents.rend();)
        {
            auto event = *iterator;
            if (event->GetStatus() != EventStatus::HANDLING)
            {
                finished.push_front(event);
                iterator = std::vector<EventPtr>::reverse_iterator(mHandlingEvents.erase(std::next(iterator).base()));
            }
            else
            {
                ++iterator;
            }
        }
        for (auto &event : finished)
        {
            auto iterator = mEvent2Callback.find(event);
            if (iterator != mEvent2Callback.end())
            {
                auto callback = iterator->second;
                if (callback != nullptr)
                {
                    callback(event);
                }
                mEvent2Callback.erase(iterator);
            }
        }
    }

    void IO::AsyncHandle(EventPtr event, IOCallbackFunction function)
    {
        if (mRouterFunction)
        {
            mAsyncEventHandlers[mRouterFunction(event, mAsyncEventHandlers.size())]->Handle(event);
        }
        else
        {
            mAsyncEventHandlers[++mCurrentThread % mAsyncEventHandlers.size()]->Handle(event);
        }
        mHandlingEvents.push_back(event);
        mEvent2Callback.insert({ event, function });
    }

    IO_API IIO &GetIO()
    {
        static IO instance;
        return instance;
    }
}

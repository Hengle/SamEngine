#include "IO.h"

#include <deque>

namespace SamEngine
{
    void IO::Initialize(int32 threadCount)
    {
        s_assert(!Available());
        mThreads.resize(static_cast<size_t>(threadCount));
        for (auto i = 0; i < threadCount; ++i)
        {
            mThreads[i] = IOThreadAsyncEventHandler::Create();
            mThreads[i]->Start();
        }
        mValid = true;
        mTickID = GetThread().GetTicker().Add(this);
    }

    void IO::Finalize()
    {
        s_assert(Available());
        GetThread().GetTicker().Remove(mTickID);
        mValid = false;
        for (auto &thread : mThreads)
        {
            thread->Stop();
        }
        mThreads.clear();
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

    void IO::Read(const std::string &file, IOCallbackFunction callback)
    {
        s_assert(Available());
        auto location = file;
        auto event = IORequestReadEvent::Create();
        for (auto pair : mLocationPlaceholder)
        {
            if (location.find(pair.first) == 0)
            {
                location.replace(0, pair.first.length() + 1, pair.second);
                break;
            }
        }
        event->SetLocation(location);
        Handle(event, callback);
    }

    void IO::Write(const std::string &file, const DataPtr &data, IOCallbackFunction callback)
    {
        s_assert(Available());
        auto location = file;
        auto event = IORequestWriteEvent::Create();
        for (auto pair : mLocationPlaceholder)
        {
            if (location.find(pair.first) == 0)
            {
                location.replace(0, pair.first.length() + 1, pair.second);
                break;
            }
        }
        event->SetLocation(location);
        event->SetData(data);
        Handle(event, callback);
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
                for (auto &thread : mThreads)
                {
                    thread->Handle(event);
                }
            }
            else
            {
                mFilesystemCreatorRegistery[name] = function;
                auto event = IONotifyReplaceFilesystemEvent::Create();
                event->SetFilesystemName(name);
                for (auto &thread : mThreads)
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
            for (auto &thread : mThreads)
            {
                thread->Handle(event);
            }
        }
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
        for (auto &thread : mThreads)
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

    void IO::Handle(const EventPtr &event, IOCallbackFunction function)
    {
        if (mRouterFunction)
        {
            mThreads[mRouterFunction(event, mThreads.size())]->Handle(event);
        }
        else
        {
            mThreads[++mCurrentThread % mThreads.size()]->Handle(event);
        }
        mHandlingEvents.push_back(event);
        mEvent2Callback.insert({ event, function });
    }
}

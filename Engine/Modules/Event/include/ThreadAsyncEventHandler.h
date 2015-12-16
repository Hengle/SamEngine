#pragma once

#include "IEventHandler.h"

#include <condition_variable>
#include <thread>
#include <mutex>
#include <queue>

namespace SamEngine
{
    enum class ThreadAsyncEventHandlerStatus
    {
        WAITING,
        RUNNING,
        STOPPING,
        STOPPED,
    };

    class EVENT_API ThreadAsyncEventHandler : public IEventHandler
    {
    public:
        ThreadAsyncEventHandler();

        virtual ~ThreadAsyncEventHandler();

        virtual bool Handle(const EventPtr event) override;

        void Dispatch();

        void Start();

        void Stop();

        void SetWaitTime(int32 value) { mWaitTime = value; }

        int32 GetWaitTime() const { return mWaitTime; }

    protected:
        virtual void EnterThread();

        virtual void ExitThread();

        virtual void WorkerHandle(const EventPtr event);

    private:
        static void MainLoop(ThreadAsyncEventHandler *self);

    protected:
        int32 mWaitTime{ 0 };
        IEventHandlerPtr mWorker{ nullptr };

    private:
        ThreadAsyncEventHandlerStatus mCurrentStatus{ ThreadAsyncEventHandlerStatus::WAITING };
        ThreadID mParentThreadID;
        ThreadID mChildThreadID;
        std::thread mThread;
        std::mutex mMutex;
        std::mutex mQueueLock;
        std::condition_variable mConditionVariable;
        std::queue<EventPtr> mCommingEvents;
        std::queue<EventPtr> mWaitingEvents;
        std::queue<EventPtr> mForwardingEvents;
    };
}
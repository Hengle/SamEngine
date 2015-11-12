#include "ThreadAsyncEventHandler.h"

#include <chrono>

namespace SamEngine
{
    ThreadAsyncEventHandler::ThreadAsyncEventHandler()
    {
        mParentThreadID = std::this_thread::get_id();
    }

    ThreadAsyncEventHandler::~ThreadAsyncEventHandler()
    {
        s_assert(std::this_thread::get_id() == mParentThreadID);
        s_assert(mCurrentStatus == ThreadAsyncEventHandlerStatus::STOPPED);
    }

    bool ThreadAsyncEventHandler::Handle(const EventPtr &event)
    {
        s_assert(std::this_thread::get_id() == mParentThreadID);
        s_assert(mCurrentStatus == ThreadAsyncEventHandlerStatus::RUNNING);
        event->SetHandling();
        mCommingEvents.push(event);
        return true;
    }

    void ThreadAsyncEventHandler::Dispatch()
    {
        s_assert(std::this_thread::get_id() == mParentThreadID);
        s_assert(mCurrentStatus == ThreadAsyncEventHandlerStatus::RUNNING);
        while (!mCommingEvents.empty())
        {
            mQueueLock.lock();
            if (mWaitingEvents.empty())
            {
                mWaitingEvents = std::move(mCommingEvents);
            }
            else
            {
                while (!mCommingEvents.empty())
                {
                    mWaitingEvents.push(mCommingEvents.front());
                    mCommingEvents.pop();
                }
            }
            mQueueLock.unlock();
        }
        mConditionVariable.notify_one();
    }

    void ThreadAsyncEventHandler::Start()
    {
        s_assert(std::this_thread::get_id() == mParentThreadID);
        s_assert(mCurrentStatus == ThreadAsyncEventHandlerStatus::WAITING);
        mCurrentStatus = ThreadAsyncEventHandlerStatus::RUNNING;
        mThread = std::thread(MainLoop, this);
    }

    void ThreadAsyncEventHandler::Stop()
    {
        s_assert(mCurrentStatus == ThreadAsyncEventHandlerStatus::RUNNING);
        mCurrentStatus = ThreadAsyncEventHandlerStatus::STOPPED;
        mConditionVariable.notify_one();
        mThread.join();
        mCurrentStatus = ThreadAsyncEventHandlerStatus::STOPPED;
    }

    void ThreadAsyncEventHandler::EnterThread()
    {
        GetThread().Enter();
    }

    void ThreadAsyncEventHandler::ExitThread()
    {
        GetThread().Exit();
    }

    void ThreadAsyncEventHandler::WorkerHandle(const EventPtr &event)
    {
        mWorker->Handle(event);
    }

    void ThreadAsyncEventHandler::MainLoop(ThreadAsyncEventHandler *self)
    {
        self->mChildThreadID = std::this_thread::get_id();
        self->EnterThread();
        while (self->mCurrentStatus == ThreadAsyncEventHandlerStatus::RUNNING)
        {
            std::unique_lock<std::mutex> lock(self->mMutex);
            if (self->mWaitTime == 0)
            {
                self->mConditionVariable.wait(lock);
            }
            else
            {
                self->mConditionVariable.wait_for(lock, std::chrono::milliseconds(self->mWaitTime));
            }
            lock.unlock();
            s_assert(std::this_thread::get_id() == self->mChildThreadID);
            s_assert(self->mForwardingEvents.empty());
            self->mQueueLock.lock();
            self->mForwardingEvents = std::move(self->mWaitingEvents);
            self->mQueueLock.unlock();
            while (!self->mForwardingEvents.empty())
            {
                self->WorkerHandle(self->mForwardingEvents.front());
                self->mForwardingEvents.pop();
            }
        }
        self->ExitThread();
    }
}
#include "Thread.h"

#include <atomic>

namespace SamEngine
{
    static ThreadID mMainThreadID;

    void Thread::Enter()
    {
        if (mMainThreadID == ThreadID())
        {
            mMainThreadID = std::this_thread::get_id();
        }
        mThreadID = std::this_thread::get_id();
    }

    void Thread::Exit()
    {
    }

    bool Thread::IsMainThread()
    {
        return mThreadID == mMainThreadID;
    }

    ThreadID Thread::GetThreadID()
    {
        return mThreadID;
    }

    ITicker &Thread::GetTicker()
    {
        return mTicker;
    }

    CORE_API IThread &GetThread()
    {
        static thread_local std::atomic<Thread *> instance{ nullptr };
        if (instance.load() == nullptr)
        {
            instance.store(new Thread());
        }
        return *instance;
    }
}
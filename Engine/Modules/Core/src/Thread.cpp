#include "Thread.h"

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
}
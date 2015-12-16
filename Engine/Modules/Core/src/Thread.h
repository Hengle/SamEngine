#pragma once

#include "IThread.h"
#include "Ticker.h"

#if SAM_OSX
#   define thread_local __thread
#endif

namespace SamEngine
{
    class Thread : public IThread
    {
    public:
        virtual void Enter() override;

        virtual void Exit() override;

        virtual bool IsMainThread() override;

        virtual ThreadID GetThreadID() override;

        virtual ITicker &GetTicker() override;

    private:
        ThreadID mThreadID;
        
        Ticker mTicker;
    };
}
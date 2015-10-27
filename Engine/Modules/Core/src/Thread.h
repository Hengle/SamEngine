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
        void Enter() override;

        void Exit() override;

        bool IsMainThread() override;

        ThreadID GetThreadID() override;

        ITicker &GetTicker() override;

    private:
        ThreadID mThreadID;
        
        Ticker mTicker;
    };
}
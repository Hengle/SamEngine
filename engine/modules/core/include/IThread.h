#pragma once

#include "ITicker.h"

#include <thread>

namespace SamEngine
{
    typedef std::thread::id ThreadID;

    class CORE_API IThread
    {
    public:
        virtual ~IThread() {}

        virtual void Enter() = 0;

        virtual void Exit() = 0;

        virtual bool IsMainThread() = 0;

        virtual ThreadID GetThreadID() = 0;

        virtual ITicker &GetTicker() = 0;
    };

    extern CORE_API IThread &GetThread();
}
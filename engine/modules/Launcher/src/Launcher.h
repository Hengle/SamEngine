#pragma once

#include "ILauncher.h"

#include <CoreModule.h>

#include <atomic>
#include <chrono>

namespace SamEngine
{
    class Launcher : public ILauncher
    {
    public:
        virtual ~Launcher() {}

        void SetApplication(IApplication *application) override;

        void Run() override;

    protected:
        void calculateTime();

    private:
        IApplication *mApplication{ nullptr };
        ApplicationState mApplicationState{ ApplicationState::INITIALIZE };
        TickCount mTotalTickCount{ 0 };
        TickCount mDeltaTickCount{ 0 };
    };

    inline void Launcher::calculateTime()
    {
        static std::atomic_flag initialFlag{ false };
        static TickCount base;
        if (!initialFlag.test_and_set())
        {
            base = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        }
        auto now = std::chrono::high_resolution_clock::now().time_since_epoch().count() - base;
        mDeltaTickCount = now - mTotalTickCount;
        mTotalTickCount = now;
    }

    inline LAUNCHER_API ILauncher &GetLauncher()
    {
        static Launcher instance;
        return instance;
    }
}
#pragma once

#if SAM_USE_LUA

#include "ILuaLauncher.h"

#include <CoreModule.h>

#include <lua.hpp>
#include <LuaIntf.h>

#include <functional>

using namespace LuaIntf;

namespace SamEngine
{
    class LuaLogRecorder : public ILogRecorder
    {
    public:
        LOG_RECORDER_CREAE_FUNC_DECLARE(LuaLogRecorder)

        LuaLogRecorder();

        ~LuaLogRecorder();

        virtual void Assert(const char *condition, const char *message, const char *filename, int32 line, const char *function) override;

        virtual void Record(LogLevel mask, const char *message, va_list args) override;

    private:
        FILE *mFile{ nullptr };
    };

    class LuaLauncher : public ILuaLauncher, public ITick
    {
    public:
        virtual void Create(const std::string &initialize, const std::string &finalize, const std::string &draw, const std::string &tick, int32 width, int32 height, const std::string &title) override;

        virtual ApplicationState Initialize() override;

        virtual ApplicationState Running() override;

        virtual ApplicationState Finalize() override;

        virtual void Tick(TickCount now, TickCount delta) override;

        virtual void Run(const std::string &file) override;

    private:
        LuaState mLuaState;
        TickID mTickID{ InvalidTickID };
        int32 mWidth{ 0 };
        int32 mHeight{ 0 };
        std::string mTitle;
        std::string mLuaInitialize;
        std::string mLuaFinalize;
        std::string mLuaDraw;
        std::string mLuaTick;
        LuaRef mLuaInitializeFunction;
        LuaRef mLuaFinalizeFunction;
        LuaRef mLuaDrawFunction;
        LuaRef mLuaTickFunction;
    };
}

#endif
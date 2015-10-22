#pragma once

#include "ILuaLauncher.h"

#include <CoreModule.h>

#include <lua.hpp>

#include <functional>

namespace SamEngine
{
    class LuaLauncher : public ILuaLauncher, public ITick
    {
    public:
        void Create(const std::string &main, const std::string &initialize, const std::string &finalize, const std::string &update, const std::string &tick, int32 width, int32 height, const std::string &title) override;

        void Destroy() override;

        ApplicationState Initialize() override;

        ApplicationState Running() override;

        ApplicationState Finalize() override;

        void Tick(TickCount now, TickCount delta) override;

        void Run(const std::string &file) override;

    protected:
        void ProtectedLuaCall(lua_CFunction function = nullptr, int32 argc = 0, int32 result = 0);

    private:
        static LuaLauncher *self;
        lua_State *mLuaState{ nullptr };
        TickID mTickID{ InvalidTickID };
        TickCount mNow{ 0 };
        TickCount mDelta{ 0 };
        int32 mWidth{ 0 };
        int32 mHeight{ 0 };
        std::string mTitle;
        std::string mLuaMain;
        std::string mLuaInitialize;
        std::string mLuaFinalize;
        std::string mLuaUpdate;
        std::string mLuaTick;
    };

    inline LAUNCHER_API ILuaLauncher &GetLuaLauncher()
    {
        static LuaLauncher instance;
        return instance;
    }
}
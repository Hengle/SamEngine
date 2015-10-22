#include "LuaLauncher.h"

#include <LuaCoreModule.h>
#include <HTTPModule.h>
#include <IOModule.h>
#include <GraphicsModule.h>
#include <WindowModule.h>

#include <LuaIntf.h>

using namespace LuaIntf;

namespace SamEngine
{
    LuaLauncher *LuaLauncher::self = nullptr;

    void LuaLauncher::Create(const std::string &main, const std::string &initialize, const std::string &finalize, const std::string &update, const std::string &tick, int32 width, int32 height, const std::string &title)
    {
        self = this;
        mLuaMain = main;
        mLuaInitialize = initialize;
        mLuaFinalize = finalize;
        mLuaUpdate = update;
        mLuaTick = tick;
        mWidth = width;
        mHeight = height;
        mTitle = title;
        mLuaState = luaL_newstate();
        s_assert(mLuaState != nullptr);
        luaL_openlibs(mLuaState);
        auto function = [](lua_State *L) -> int32
        {
            OpenCoreModule(L);
            return 0;
        };
        ProtectedLuaCall(function);
    }

    void LuaLauncher::Destroy()
    {
        self = nullptr;
        lua_close(mLuaState);
    }

    ApplicationState LuaLauncher::Initialize()
    {
        mTickID = GetThread().GetTicker().Add(this);
        GetWindow().Initialize(WindowConfig::ForWindow(mWidth, mHeight, mTitle));
        GetGraphics().Initialize(GraphicsConfig());
        GetHTTP().Initialize();
        GetIO().Initialize();
        auto function = [](lua_State *L) -> int32
        {
            LuaState lua = L;
            lua.getGlobal(self->mLuaMain.c_str());
            if (lua.isTable(-1))
            {
                lua.getField(-1, self->mLuaInitialize.c_str());
                if (lua.isFunction(-1))
                {
                    self->ProtectedLuaCall();
                }
            }
            lua.pop();
            return 0;
        };
        ProtectedLuaCall(function);
        return ApplicationState::RUNNING;
    }

    ApplicationState LuaLauncher::Running()
    {
        auto function = [](lua_State *L) -> int32
        {
            LuaState lua = L;
            lua.getGlobal(self->mLuaMain.c_str());
            if (lua.isTable(-1))
            {
                lua.getField(-1, self->mLuaUpdate.c_str());
                if (lua.isFunction(-1))
                {
                    self->ProtectedLuaCall();
                }
            }
            lua.pop();
            return 0;
        };
        ProtectedLuaCall(function);
        GetWindow().Present();
        return GetWindow().ShouldClose() ? ApplicationState::FINALIZE : ApplicationState::RUNNING;
    }

    ApplicationState LuaLauncher::Finalize()
    {
        auto function = [](lua_State *L) -> int32
        {
            LuaState lua = L;
            lua.getGlobal(self->mLuaMain.c_str());
            if (lua.isTable(-1))
            {
                lua.getField(-1, self->mLuaFinalize.c_str());
                if (lua.isFunction(-1))
                {
                    self->ProtectedLuaCall();
                }
            }
            lua.pop();
            return 0;
        };
        ProtectedLuaCall(function);
        GetThread().GetTicker().Remove(mTickID);
        GetIO().Finalize();
        GetHTTP().Finalize();
        GetGraphics().Finalize();
        GetWindow().Finalize();
        return ApplicationState::EXIT;
    }

    void LuaLauncher::Tick(TickCount now, TickCount delta)
    {
        mNow = now;
        mDelta = delta;
        auto function = [](lua_State *L) -> int32
        {
            LuaState lua = L;
            lua.getGlobal(self->mLuaMain.c_str());
            if (lua.isTable(-1))
            {
                lua.getField(-1, self->mLuaTick.c_str());
                if (lua.isFunction(-1))
                {
                    lua.push(self->mNow);
                    lua.push(self->mDelta);
                    self->ProtectedLuaCall(nullptr, 2);
                }
            }
            lua.pop();
            return 0;
        };
        ProtectedLuaCall(function);
    }

    void LuaLauncher::Run(const std::string &file)
    {
        LuaState lua = mLuaState;
        auto error = lua.loadFile(file.c_str());
        switch (error)
        {
        case LUA_OK:
            ProtectedLuaCall();
            break;
        case LUA_ERRSYNTAX:
            s_error("[Lua] load main.lua, syntax error.\n");
            break;
        case LUA_ERRMEM:
            s_error("[Lua] load main.lua error, no enough memory.\n");
            break;
        case LUA_ERRGCMM:
            s_error("[Lua] load main.lua, gc error.\n");
            break;
        default:
            s_error("[Lua] load main.lua, unknown error.\n");
            break;
        }
    }

    void LuaLauncher::ProtectedLuaCall(lua_CFunction function, int32 argc, int32 result)
    {
        LuaState lua = mLuaState;
        if (function != nullptr)
        {
            lua.pushCFunction(function);
        }
        auto error = lua.pcall(argc, result, 0, 0);
        switch (error)
        {
        case LUA_OK:
            break;
        case LUA_ERRRUN:
            s_error("[Lua] lua runtime error: %s.\n", lua.toString(-1));
            break;
        case LUA_ERRMEM:
            s_error("[Lua] lua memory error.\n");
            break;
        case LUA_ERRERR:
            s_error("[Lua] lua error.\n");
            break;
        case LUA_ERRGCMM:
            s_error("[Lua] lua gc error.\n");
            break;
        default:
            s_error("[Lua] lua unknown error.\n");
            break;
        };
    }
}
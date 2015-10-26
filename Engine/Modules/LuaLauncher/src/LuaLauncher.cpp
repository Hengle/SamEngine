#include "LuaLauncher.h"

#include <LuaAssetModule.h>
#include <LuaCoreModule.h>
#include <HTTPModule.h>
#include <LuaIOModule.h>
#include <LuaGraphicsModule.h>
#include <StorageModule.h>
#include <WindowModule.h>

namespace SamEngine
{
    void LuaLauncher::Create(const std::string &initialize, const std::string &finalize, const std::string &draw, const std::string &tick, int32 width, int32 height, const std::string &title)
    {
        mLuaInitialize = initialize;
        mLuaFinalize = finalize;
        mLuaDraw = draw;
        mLuaTick = tick;
        mWidth = width;
        mHeight = height;
        mTitle = title;
        mLuaState = LuaState::newState();
        s_assert(mLuaState != nullptr);
        luaL_openlibs(mLuaState);
        OpenCoreModule(mLuaState);
        OpenGraphicsModule(mLuaState);
        OpenAssetModule(mLuaState);
        OpenIOModule(mLuaState);
    }

    void LuaLauncher::Destroy()
    {
        mLuaState.close();
    }

    ApplicationState LuaLauncher::Initialize()
    {
        mTickID = GetThread().GetTicker().Add(this);
        GetWindow().Initialize(WindowConfig::ForWindow(mWidth, mHeight, mTitle));
        GetGraphics().Initialize(GraphicsConfig());
        GetHTTP().Initialize();
        GetIO().Initialize();
        GetIO().SetFilesystemCreator("http", GetHTTPFilesystemCreator());
        GetIO().SetFilesystemCreator("storage", GetStorageFilesystemCreator());
        ProtectedLuaCall(mLuaInitialize);
        return ApplicationState::RUNNING;
    }

    ApplicationState LuaLauncher::Running()
    {
        static ClearState clearState;
        GetGraphics().GetRenderer().ApplyTarget();
        GetGraphics().GetRenderer().ApplyClearState(clearState);
        ProtectedLuaCall(mLuaDraw);
        GetWindow().Present();
        return GetWindow().ShouldClose() ? ApplicationState::FINALIZE : ApplicationState::RUNNING;
    }

    ApplicationState LuaLauncher::Finalize()
    {
        ProtectedLuaCall(mLuaFinalize);
        GetThread().GetTicker().Remove(mTickID);
        GetHTTP().Finalize();
        GetIO().Finalize();
        GetGraphics().Finalize();
        GetWindow().Finalize();
        return ApplicationState::EXIT;
    }

    void LuaLauncher::Tick(TickCount now, TickCount delta)
    {
        ProtectedLuaCall(mLuaTick, now, delta);
    }

    void LuaLauncher::Run(const std::string &file)
    {
        auto error = mLuaState.loadFile(file.c_str());
        if (error == LUA_OK)
        {
            error = mLuaState.pcall(0, 0, 0, 0);
        }
        switch (error)
        {
        case LUA_OK:
            break;
        case LUA_ERRSYNTAX:
            s_error("[Lua] syntax error.\n");
            break;
        case LUA_ERRRUN:
            s_error("[Lua] lua runtime error: %s.\n", mLuaState.toString(-1));
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
            s_error("[Lua] unknown error.\n");
            break;
        }
    }
}
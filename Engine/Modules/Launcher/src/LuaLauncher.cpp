#if SAM_USE_LUA

#include "LuaLauncher.h"

#include <LuaAssetModule.h>
#include <LuaCoreModule.h>
#include <HTTPModule.h>
#include <LuaIOModule.h>
#include <LuaGraphicsModule.h>
#include <LuaResourceModule.h>
#include <LuaStorageModule.h>
#include <LuaWindowModule.h>

#include <ctime>

namespace SamEngine
{
    LuaLogRecorder::LuaLogRecorder()
    {
        mFile = std::fopen("./engine.log", "a");
    }

    LuaLogRecorder::~LuaLogRecorder()
    {
        fclose(mFile);
    }

    void LuaLogRecorder::Assert(const char *condition, const char *message, const char *filename, int32 line, const char *function)
    {
        auto now = std::time(nullptr);
        auto tm = std::localtime(&now);
        std::fprintf(mFile, "[%04d-%02d-%02d %02d:%02d:%02d] ", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
        std::fprintf(mFile, "engine assert: \n\tcondition: %s\n\tmessage: %s\n\tfilename: %s\n\tline: %d\n\tfunction: %s\n'", condition, message, filename, line, function);
        fflush(mFile);
    }

    void LuaLogRecorder::Record(LogLevel mask, const char *message, va_list args)
    {
        auto now = std::time(nullptr);
        auto tm = std::localtime(&now);
        std::fprintf(mFile, "[%04d-%02d-%02d %02d:%02d:%02d] ", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
        std::vfprintf(mFile, message, args);
        fflush(mFile);
    }

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
        OpenCoreLuaModule(mLuaState);
        OpenGraphicsLuaModule(mLuaState);
        OpenAssetLuaModule(mLuaState);
        OpenIOLuaModule(mLuaState);
        OpenResourceLuaModule(mLuaState);
        OpenStorageLuaModule(mLuaState);
        OpenWindowLuaModule(mLuaState);
        GetLog().AddLogRecorder(LuaLogRecorder::Create());
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
        DefaultShader::Initialize();
        ImageBatcher::Initialize();
        mLuaInitializeFunction.call();
        return ApplicationState::RUNNING;
    }

    ApplicationState LuaLauncher::Running()
    {
        GetGraphics().GetRenderer().ApplyTarget();
        mLuaDrawFunction.call();
        ImageBatcher::Flush();
        GetGraphics().GetRenderer().Render();
        GetWindow().Present();
        return GetWindow().ShouldClose() ? ApplicationState::FINALIZE : ApplicationState::RUNNING;
    }

    ApplicationState LuaLauncher::Finalize()
    {
        mLuaFinalizeFunction.call();
        mLuaInitializeFunction = LuaRef();
        mLuaFinalizeFunction = LuaRef();
        mLuaDrawFunction = LuaRef();
        mLuaTickFunction = LuaRef();
        mLuaState.close();
        ImageBatcher::Finalize();
        DefaultShader::Finalize();
        GetThread().GetTicker().Remove(mTickID);
        GetHTTP().Finalize();
        GetIO().Finalize();
        GetGraphics().Finalize();
        GetWindow().Finalize();
        return ApplicationState::EXIT;
    }

    void LuaLauncher::Tick(TickCount now, TickCount delta)
    {
        mLuaTickFunction.call(now, delta);
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
        case LUA_ERRFILE:
            s_error("[Lua] can not load lua file %s.\n", file.c_str());
            break;
        default:
            s_error("[Lua] unknown error.\n");
            break;
        }
        mLuaInitializeFunction = LuaRef(mLuaState, mLuaInitialize.c_str());
        mLuaFinalizeFunction = LuaRef(mLuaState, mLuaFinalize.c_str());
        mLuaDrawFunction = LuaRef(mLuaState, mLuaDraw.c_str());
        mLuaTickFunction = LuaRef(mLuaState, mLuaTick.c_str());
        s_assert(mLuaInitializeFunction.isFunction());
        s_assert(mLuaFinalizeFunction.isFunction());
        s_assert(mLuaDrawFunction.isFunction());
        s_assert(mLuaTickFunction.isFunction());
    }

    LAUNCHER_API ILuaLauncher &GetLuaLauncher()
    {
        static LuaLauncher instance;
        return instance;
    }
}

#endif
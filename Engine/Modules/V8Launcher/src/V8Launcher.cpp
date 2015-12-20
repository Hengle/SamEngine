#include "V8Launcher.h"

#include <AssetModule.h>
#include <HTTPModule.h>
#include <StorageModule.h>

#include <ctime>
#include <fstream>

namespace SamEngine
{
    V8LogRecorder::V8LogRecorder()
    {
        mFile = std::fopen("./engine.log", "a");
    }

    V8LogRecorder::~V8LogRecorder()
    {
        fclose(mFile);
    }

    void V8LogRecorder::Assert(const char *condition, const char *message, const char *filename, int32 line, const char *function)
    {
        auto now = std::time(nullptr);
        auto tm = std::localtime(&now);
        std::fprintf(mFile, "[%04d-%02d-%02d %02d:%02d:%02d] ", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
        std::fprintf(mFile, "engine assert: \n\tcondition: %s\n\tmessage: %s\n\tfilename: %s\n\tline: %d\n\tfunction: %s\n'", condition, message, filename, line, function);
        fflush(mFile);
    }

    void V8LogRecorder::Record(LogLevel mask, const char *message, va_list args)
    {
        auto now = std::time(nullptr);
        auto tm = std::localtime(&now);
        std::fprintf(mFile, "[%04d-%02d-%02d %02d:%02d:%02d] ", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
        std::vfprintf(mFile, message, args);
        fflush(mFile);
    }

    void V8Launcher::Create(const std::string &initialize, const std::string &finalize, const std::string &draw, const std::string &tick, int32 width, int32 height, const std::string &title)
    {
        mWidth = width;
        mHeight = height;
        mTitle = title;
        mV8Helper = new V8Helper(initialize, finalize, draw, tick);
        GetLog().AddLogRecorder(V8LogRecorder::Create());
    }

    ApplicationState V8Launcher::Initialize()
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
        mV8Helper->Initialize();
        return ApplicationState::RUNNING;
    }

    ApplicationState V8Launcher::Running()
    {
        GetGraphics().GetRenderer().ApplyTarget();
        mV8Helper->Draw();
        ImageBatcher::Flush();
        GetGraphics().GetRenderer().Render();
        GetWindow().Present();
        return GetWindow().ShouldClose() ? ApplicationState::FINALIZE : ApplicationState::RUNNING;
    }

    ApplicationState V8Launcher::Finalize()
    {
        mV8Helper->Finalize();
        delete mV8Helper;
        ImageBatcher::Finalize();
        DefaultShader::Finalize();
        GetThread().GetTicker().Remove(mTickID);
        GetHTTP().Finalize();
        GetIO().Finalize();
        GetGraphics().Finalize();
        GetWindow().Finalize();
        return ApplicationState::EXIT;
    }

    void V8Launcher::Tick(TickCount now, TickCount delta)
    {
        mV8Helper->Tick(now, delta);
    }

    void V8Launcher::Run(const std::string &file)
    {
        mV8Helper->Run(file);
    }

    V8_LAUNCHER_API IV8Launcher &GetV8Launcher()
    {
        static V8Launcher instance;
        return instance;
    }
}
#include "V8Launcher.h"

#include <V8AssetModule.h>
#include <V8CoreModule.h>
#include <HTTPModule.h>
#include <V8IOModule.h>
#include <V8GraphicsModule.h>
#include <V8ResourceModule.h>
#include <StorageModule.h>
#include <V8WindowModule.h>

#include <ctime>

namespace SamEngine
{
    class ArrayBufferAllocator : public v8::ArrayBuffer::Allocator
    {
    public:
        virtual void *Allocate(size_t length)
        {
            auto data = AllocateUninitialized(length);
            return data == nullptr ? data : memset(data, 0, length);
        }

        virtual void *AllocateUninitialized(size_t length)
        {
            return malloc(length);
        }

        virtual void Free(void *data, size_t)
        {
            free(data);
        }
    };

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
        mV8Initialize = initialize;
        mV8Finalize = finalize;
        mV8Draw = draw;
        mV8Tick = tick;
        mWidth = width;
        mHeight = height;
        mTitle = title;
        v8::V8::InitializeICU();
        mPlatform = v8::platform::CreateDefaultPlatform();
        v8::V8::InitializePlatform(mPlatform);
        v8::V8::Initialize();
        mAllocator = new ArrayBufferAllocator;
        v8::Isolate::CreateParams params;
        params.array_buffer_allocator = mAllocator;
        mIsolate = v8::Isolate::New(params);
        s_assert(mIsolate != nullptr);
        OpenCoreV8Module(mIsolate);
        OpenGraphicsV8Module(mIsolate);
        OpenAssetV8Module(mIsolate);
        OpenIOV8Module(mIsolate);
        OpenResourceV8Module(mIsolate);
        OpenWindowV8Module(mIsolate);
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
        ProtectedV8Call(mV8Finalize);
        return ApplicationState::RUNNING;
    }

    ApplicationState V8Launcher::Running()
    {
        GetGraphics().GetRenderer().ApplyTarget();
        ProtectedV8Call(mV8Finalize);
        ImageBatcher::Flush();
        GetGraphics().GetRenderer().Render();
        GetWindow().Present();
        return GetWindow().ShouldClose() ? ApplicationState::FINALIZE : ApplicationState::RUNNING;
    }

    ApplicationState V8Launcher::Finalize()
    {
        ProtectedV8Call(mV8Finalize);
        mIsolate->Dispose();
        mIsolate = nullptr;
        v8::V8::Dispose();
        v8::V8::ShutdownPlatform();
        delete mPlatform;
        mPlatform = nullptr;
        delete mAllocator;
        mAllocator = nullptr;
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
        ProtectedV8Call(mV8Finalize, now, delta);
    }

    void V8Launcher::Run(const std::string &file)
    {

    }

    V8_LAUNCHER_API IV8Launcher &GetV8Launcher()
    {
        static V8Launcher instance;
        return instance;
    }
}
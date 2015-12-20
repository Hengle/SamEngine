#include "V8Helper.h"

#include <V8AssetModule.h>
#include <V8CoreModule.h>
#include <V8IOModule.h>
#include <V8GraphicsModule.h>
#include <V8ResourceModule.h>
#include <V8StorageModule.h>
#include <V8WindowModule.h>

#include <fstream>

namespace SamEngine
{
    V8Helper::V8Helper(const std::string &initialize, const std::string &finalize, const std::string &draw, const std::string &tick) :
        mV8Initialize(initialize),
        mV8Finalize(finalize),
        mV8Draw(draw),
        mV8Tick(tick)
    {
        InitializeV8();
        InitializeGlobal();
        InitializeModule();
    }

    V8Helper::~V8Helper()
    {
        mIsolate->Exit();
        mIsolate->Dispose();
        v8::V8::Dispose();
        v8::V8::ShutdownPlatform();
        delete mPlatform;
        delete mAllocator;
    }

    void V8Helper::Initialize()
    {
        v8::HandleScope scope(mIsolate);
        v8::TryCatch tryCatch;
        mV8InitializeFunction.Get(mIsolate)->Call(mIsolate->GetCurrentContext()->Global(), 0, nullptr);
        CheckException(tryCatch);
    }

    void V8Helper::Finalize()
    {
        v8::HandleScope scope(mIsolate);
        v8::TryCatch tryCatch;
        mV8FinalizeFunction.Get(mIsolate)->Call(mIsolate->GetCurrentContext()->Global(), 0, nullptr);
        CheckException(tryCatch);
    }

    void V8Helper::Draw()
    {
        v8::HandleScope scope(mIsolate);
        v8::TryCatch tryCatch;
        mV8DrawFunction.Get(mIsolate)->Call(mIsolate->GetCurrentContext()->Global(), 0, nullptr);
        CheckException(tryCatch);
    }

    void V8Helper::Tick(TickCount now, TickCount delta)
    {
        v8::HandleScope scope(mIsolate);
        v8::Local<v8::Value> argv[] = { v8::Number::New(mIsolate, now), v8::Number::New(mIsolate, delta) };
        v8::TryCatch tryCatch;
        mV8TickFunction.Get(mIsolate)->Call(mIsolate->GetCurrentContext()->Global(), 2, argv);
        CheckException(tryCatch);
    }

    void V8Helper::Run(const std::string &file)
    {
        mRoot = file.substr(0, file.rfind("/"));
        ExecuteScriptFromFile(file.substr(file.rfind("/") + 1));
        InitializeFunction(mV8InitializeFunction, mV8Initialize);
        InitializeFunction(mV8FinalizeFunction, mV8Finalize);
        InitializeFunction(mV8DrawFunction, mV8Draw);
        InitializeFunction(mV8TickFunction, mV8Tick);
    }

    void V8Helper::ExecuteScriptFromFile(const std::string &relatedPath)
    {
        auto fullPath = mRoot + "/" + relatedPath;
        std::ifstream file(fullPath);
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        v8::HandleScope scope(mIsolate);
        v8::TryCatch tryCatch;
        auto contentString = v8::String::NewFromUtf8(mIsolate, content.c_str());
        v8::ScriptOrigin origin(contentString);
        auto script = v8::Script::Compile(contentString, &origin);
        script->Run();
        CheckException(tryCatch);
    }

    void V8Helper::InitializeV8()
    {
        v8::V8::InitializeICU();
        mPlatform = v8::platform::CreateDefaultPlatform();
        v8::V8::InitializePlatform(mPlatform);
        v8::V8::Initialize();
        mAllocator = new ArrayBufferAllocator;
        v8::Isolate::CreateParams params;
        params.array_buffer_allocator = mAllocator;
        mIsolate = v8::Isolate::New(params);
        mIsolate->Enter();
    }

    void V8Helper::InitializeGlobal()
    {
        v8::HandleScope scope(mIsolate);
        v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New(mIsolate);
        v8::Handle<v8::Context> context = v8::Context::New(mIsolate, nullptr, global);
        context->Enter();
    }

    void V8Helper::InitializeModule()
    {
        v8::HandleScope scope(mIsolate);
        auto global = mIsolate->GetCurrentContext()->Global();
        v8pp::module module(mIsolate);
        OpenCoreV8Module(module);
        OpenGraphicsV8Module(module);
        OpenAssetV8Module(module);
        OpenIOV8Module(module);
        OpenResourceV8Module(module);
        OpenStorageV8Module(module);
        OpenWindowV8Module(module);
        global->Set(v8::String::NewFromUtf8(mIsolate, "SamEngine"), module.new_instance());
    }

    void V8Helper::InitializeFunction(v8::Persistent<v8::Function> &persistent, const std::string &name)
    {
        v8::HandleScope scope(mIsolate);
        auto maybeFunction = mIsolate->GetCurrentContext()->Global()->Get(v8::String::NewFromUtf8(mIsolate, name.c_str()));
        s_assert(!maybeFunction.IsEmpty() && maybeFunction != v8::Undefined(mIsolate));
        auto function = maybeFunction.As<v8::Function>();
        s_assert(!function.IsEmpty() && function != v8::Undefined(mIsolate));
        persistent.Reset(mIsolate, function);
    }

    void V8Helper::CheckException(v8::TryCatch &tryCatch)
    {
        v8::HandleScope scope(mIsolate);
        if (tryCatch.HasCaught())
        {
            v8::String::Utf8Value exception(tryCatch.Exception());
            v8::Local<v8::Message> message = tryCatch.Message();
            if (message.IsEmpty())
            {
                GetLog().Error("[V8Error] %s\n", *exception);
                SAM_TRAP();
            }
            else
            {
                v8::String::Utf8Value filename(message->GetScriptOrigin().ResourceName());
                auto lineNum = message->GetLineNumber();
                GetLog().Info("[V8Exception] %s:%i: %s\n", *filename, lineNum, *exception);
                v8::String::Utf8Value sourceLine(message->GetSourceLine());
                GetLog().Info("[V8Exception] %s\n", *sourceLine);
                v8::String::Utf8Value stack_trace(tryCatch.StackTrace());
                if (stack_trace.length() > 0)
                {
                    GetLog().Info("[V8Exception] %s\n", *stack_trace);
                }
                GetLog().Error("\n");
                SAM_TRAP();
            }
        }
    }
}
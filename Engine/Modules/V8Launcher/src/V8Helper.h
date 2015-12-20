#pragma once

#include <CoreModule.h>

#include <cstdlib>
#include <string>

#include <v8.h>
#include <libplatform/libplatform.h>

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

    class V8Helper final
    {
    public:
        V8Helper(const std::string &initialize, const std::string &finalize, const std::string &draw, const std::string &tick);

        ~V8Helper();

        void Initialize();

        void Finalize();

        void Draw();

        void Tick(TickCount now, TickCount delta);

        void Run(const std::string &file);

    private:
        void ExecuteScriptFromFile(const std::string &relatedPath);

        void InitializeV8();

        void InitializeGlobal();

        void InitializeModule();

        void InitializeFunction(v8::Persistent<v8::Function> &persistent, const std::string &name);

        void CheckException(v8::TryCatch &tryCatch);

    private:
        v8::Isolate *mIsolate{ nullptr };
        v8::Platform *mPlatform{ nullptr };
        v8::ArrayBuffer::Allocator *mAllocator{ nullptr };
        std::string mV8Initialize;
        std::string mV8Finalize;
        std::string mV8Draw;
        std::string mV8Tick;
        std::string mRoot;
        v8::Persistent<v8::Function> mV8InitializeFunction;
        v8::Persistent<v8::Function> mV8FinalizeFunction;
        v8::Persistent<v8::Function> mV8DrawFunction;
        v8::Persistent<v8::Function> mV8TickFunction;
    };
}
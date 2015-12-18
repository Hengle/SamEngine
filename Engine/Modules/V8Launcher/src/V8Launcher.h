#pragma once

#include "IV8Launcher.h"

#include <CoreModule.h>

#include <v8.h>
#include <libplatform/libplatform.h>
#include <v8pp/class.hpp>
#include <v8pp/module.hpp>

#include <functional>

namespace SamEngine
{
    class V8LogRecorder : public ILogRecorder
    {
    public:
        LOG_RECORDER_CREAE_FUNC_DECLARE(V8LogRecorder)

        V8LogRecorder();

        ~V8LogRecorder();

        virtual void Assert(const char *condition, const char *message, const char *filename, int32 line, const char *function) override;

        virtual void Record(LogLevel mask, const char *message, va_list args) override;

    private:
        FILE *mFile{ nullptr };
    };

    class V8Launcher : public IV8Launcher, public ITick
    {
    public:
        virtual void Create(const std::string &initialize, const std::string &finalize, const std::string &draw, const std::string &tick, int32 width, int32 height, const std::string &title) override;

        virtual ApplicationState Initialize() override;

        virtual ApplicationState Running() override;

        virtual ApplicationState Finalize() override;

        virtual void Tick(TickCount now, TickCount delta) override;

        virtual void Run(const std::string &file) override;

    protected:
        template<typename RETURN = void, typename ... ARGUMENTS>
        RETURN ProtectedV8Call(const std::string &name, ARGUMENTS &&... args);

    private:
        v8::Isolate *mIsolate{ nullptr };
        v8::Platform *mPlatform{ nullptr };
        v8::ArrayBuffer::Allocator *mAllocator{ nullptr };
        TickID mTickID{InvalidTickID};
        int32 mWidth{0};
        int32 mHeight{0};
        std::string mTitle;
        std::string mV8Initialize;
        std::string mV8Finalize;
        std::string mV8Draw;
        std::string mV8Tick;
    };

    template<typename RETURN, typename ... ARGUMENTS>
    RETURN V8Launcher::ProtectedV8Call(const std::string &name, ARGUMENTS &&... args)
    {

    }
}
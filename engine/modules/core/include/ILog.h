#pragma once

#include "Types.h"

#include <memory>

#ifdef ERROR
#   undef ERROR
#endif

#if SAM_WINDOWS
#    define SAM_TRAP __debugbreak
#else
#    define SAM_TRAP __builtin_trap
#endif

#if !__GNUC__
#    define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

#if SAM_DEBUG
#    define s_assert(condition) do { if (!(condition)) { SamEngine::GetLog().Assert(#condition, nullptr, __FILE__, __LINE__, __PRETTY_FUNCTION__); SAM_TRAP(); } } while(0)
#    define s_assert_msg(condition, message) do { if (!(condition)) { SamEngine::GetLog().Assert(#condition, message, __FILE__, __LINE__, __PRETTY_FUNCTION__); SAM_TRAP(); } } while(0)
#    define s_assert_range(value, min, max) s_assert_msg((value >= min) && (value <= max), "out of range")
#    define s_static_assert(condition) static_assert((condition))
#    define s_static_assert_range(value, min, max) s_static_assert((value >= min) && (value <= max))
#    define s_error(...) do { SamEngine::GetLog().Error(__VA_ARGS__); SAM_TRAP(); } while(0)
#else
#    define s_assert(condition) ((void)0)
#    define s_assert_msg(condition, message) ((void)0)
#    define s_assert_range(value, min, max) ((void)0)
#    define s_static_assert(condition) ((void)0)
#    define s_static_assert_range(value, min, max) ((void)0)
#    define s_error(...) do { exit(-1); } while(0)
#endif

namespace SamEngine
{
    enum class LogLevel : int32
    {
        ERROR,
        WARNING,
        INFO,
        DEBUG,
    };

    class CORE_API ILogRecorder
    {
    public:
        virtual ~ILogRecorder() {}

        virtual void Assert(const char *condition, const char *message, const char *filename, int32 line, const char *function) = 0;

        virtual void Record(LogLevel mask, const char *message, va_list args) = 0;
    };

    class CORE_API ILog
    {
    public:
        virtual ~ILog() {}

        virtual void AddLogRecorder(std::shared_ptr<ILogRecorder> &recorder) = 0;

        virtual void SetLogLevel(LogLevel value) = 0;

        virtual LogLevel GetLogLevel() const = 0;

        virtual void Error(const char *message, ...) = 0;

        virtual void Warning(const char *message, ...) = 0;

        virtual void Info(const char *message, ...) = 0;

        virtual void Debug(const char *message, ...) = 0;

        virtual void Assert(const char *condition, const char *message, const char *filename, int32 line, const char *function) = 0;
    };

    extern CORE_API ILog &GetLog();
}
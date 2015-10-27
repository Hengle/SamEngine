#include "Log.h"

#include <cstdarg>

#if SAM_WINDOWS
#   include <Windows.h>
#   define LOG_BUFFER_SIZE 1024
#endif

namespace SamEngine
{
    void Log::AddLogRecorder(ILogRecorderPtr recorder)
    {
        if (recorder)
        {
            mLock.LockWrite();
            mLogRecorders.push_back(recorder);
            mLock.UnlockWrite();
        }
    }

    void Log::SetLogLevel(LogLevel value)
    {
        mLogLevel = value;
    }

    LogLevel Log::GetLogLevel() const
    {
        return mLogLevel;
    }

    void Log::Error(const char *message, ...)
    {
        if (mLogLevel >= LogLevel::FATAL)
        {
            va_list args;
            va_start(args, message);
            Record(LogLevel::FATAL, message, args);
            va_end(args);
        }
    }

    void Log::Warning(const char *message, ...)
    {
        if (mLogLevel >= LogLevel::WARNING)
        {
            va_list args;
            va_start(args, message);
            Record(LogLevel::WARNING, message, args);
            va_end(args);
        }
    }

    void Log::Info(const char *message, ...)
    {
        if (mLogLevel >= LogLevel::INFO)
        {
            va_list args;
            va_start(args, message);
            Record(LogLevel::INFO, message, args);
            va_end(args);
        }
    }

    void Log::Debug(const char *message, ...)
    {
        if (mLogLevel >= LogLevel::DEBUG)
        {
            va_list args;
            va_start(args, message);
            Record(LogLevel::DEBUG, message, args);
            va_end(args);
        }
    }

    void Log::Assert(const char *condition, const char *message, const char *filename, int32 line, const char *function)
    {
        mLock.LockRead();
        if (mLogRecorders.empty())
        {
            printf("engine assert: \n\tcondition: %s\n\tmessage: %s\n\tfilename: %s\n\tline: %d\n\tfunction: %s\n'", condition, message, filename, line, function);

            #if SAM_WINDOWS
            char buffer[LOG_BUFFER_SIZE];
            std::snprintf(buffer, sizeof(buffer), "engine assert: \n\tcondition: %s\n\tmessage: %s\n\tfilename: %s\n\tline: %d\n\tfunction: %s\n'", condition, message, filename, line, function);
            buffer[LOG_BUFFER_SIZE - 1] = '\0';
            OutputDebugString(buffer);
            #endif
        }
        else
        {
            for (auto recoder : mLogRecorders)
            {
                recoder->Assert(condition, message, filename, line, function);
            }
        }
        mLock.UnlockRead();
    }

    void Log::Record(LogLevel mask, const char *message, va_list args)
    {
        mLock.LockRead();
        if (mLogRecorders.empty())
        {
            #if SAM_WINDOWS
            va_list argsCopy;
            va_copy(argsCopy, args);
            #endif

            vprintf(message, args);

            #if SAM_WINDOWS
            char buffer[LOG_BUFFER_SIZE];
            std::vsnprintf(buffer, sizeof(buffer), message, argsCopy);
            buffer[LOG_BUFFER_SIZE - 1] = '\0';
            OutputDebugString(buffer);
            #endif
        }
        else
        {
            for (auto recoder : mLogRecorders)
            {
                recoder->Record(mask, message, args);
            }
        }
        mLock.UnlockRead();
    }

    CORE_API ILog &GetLog()
    {
        static Log instance;
        return instance;
    }
}
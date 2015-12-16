#pragma once

#include "ILog.h"
#include "RWLock.h"

#include <vector>

namespace SamEngine
{
    class Log : public ILog
    {
    public:
        virtual void AddLogRecorder(ILogRecorderPtr recorder) override;

        virtual void SetLogLevel(LogLevel value) override;

        virtual LogLevel GetLogLevel() const override;

        virtual void Error(const char *message, ...) override;

        virtual void Warning(const char *message, ...) override;

        virtual void Info(const char *message, ...) override;

        virtual void Debug(const char *message, ...) override;

        virtual void Assert(const char *condition, const char *message, const char *filename, int32 line, const char *function) override;

    protected:
        void Record(LogLevel mask, const char *message, va_list args);

    private:
        LogLevel mLogLevel{ LogLevel::DEBUG };
        RWLock mLock;
        std::vector<std::shared_ptr<ILogRecorder>> mLogRecorders;
    };
}
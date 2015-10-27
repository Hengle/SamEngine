#pragma once

#include "ILog.h"
#include "RWLock.h"

#include <vector>

namespace SamEngine
{
    class Log : public ILog
    {
    public:
        void AddLogRecorder(ILogRecorderPtr recorder) override;

        void SetLogLevel(LogLevel value) override;

        LogLevel GetLogLevel() const override;

        void Error(const char *message, ...) override;

        void Warning(const char *message, ...) override;

        void Info(const char *message, ...) override;

        void Debug(const char *message, ...) override;

        void Assert(const char *condition, const char *message, const char *filename, int32 line, const char *function) override;

    protected:
        void Record(LogLevel mask, const char *message, va_list args);

    private:
        LogLevel mLogLevel{ LogLevel::DEBUG };
        RWLock mLock;
        std::vector<std::shared_ptr<ILogRecorder>> mLogRecorders;
    };
}
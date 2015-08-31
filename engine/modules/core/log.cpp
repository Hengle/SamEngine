#include "log.h"

#include <cstdarg>

#if defined(SAM_WINDOWS)
#   include <Windows.h>
#   define LOG_BUFFER_SIZE 1024
#endif

namespace sam
{
    log::level log::log_level = level::debug;

    rwlock log::lock;

    std::vector<std::shared_ptr<logger>> log::loggers;

    void log::add_logger(std::shared_ptr<logger> &logger)
    {
        if (logger)
        {
            lock.lock_write();
            loggers.push_back(logger);
            lock.unlock_write();
        }
    }

    void log::set_level(log::level value)
    {
        log_level = value;
    }

    log::level log::get_level()
    {
        return log_level;
    }

    void log::error(const char *message, ...)
    {
        if (log_level >= level::error)
        {
            va_list args;
            va_start(args, message);
            record(level::error, message, args);
            va_end(args);
        }
    }

    void log::warning(const char *message, ...)
    {
        if (log_level >= level::warning)
        {
            va_list args;
            va_start(args, message);
            record(level::warning, message, args);
            va_end(args);
        }
    }

    void log::info(const char *message, ...)
    {
        if (log_level >= level::info)
        {
            va_list args;
            va_start(args, message);
            record(level::info, message, args);
            va_end(args);
        }
    }

    void log::debug(const char *message, ...)
    {
        if (log_level >= level::debug)
        {
            va_list args;
            va_start(args, message);
            record(level::debug, message, args);
            va_end(args);
        }
    }

    void log::assert(const char *condition, const char *message, const char *filename, int32 line, const char *function)
    {
        lock.lock_read();
        if (loggers.empty())
        {
            printf("engine assert: \n\tcondition: %s\n\tmessage: %s\n\tfilename: %s\n\tline: %d\n\tfunction: %s\n'", condition, message, filename, line, function);

            #if defined(SAM_WINDOWS)
            char buffer[LOG_BUFFER_SIZE];
            std::snprintf(buffer, sizeof(buffer), "engine assert: \n\tcondition: %s\n\tmessage: %s\n\tfilename: %s\n\tline: %d\n\tfunction: %s\n'", condition, message, filename, line, function);
            buffer[LOG_BUFFER_SIZE - 1] = '\0';
            OutputDebugString(buffer);
            #endif
        }
        else
        {
            for (std::shared_ptr<logger> logger : loggers)
            {
                logger->assert(condition, message, filename, line, function);
            }
        }
        lock.unlock_read();
    }

    void log::record(log::level mask, const char *message, va_list args)
    {
        lock.lock_read();
        if (loggers.empty())
        {
            #if defined(SAM_WINDOWS)
            va_list argsCopy;
            va_copy(argsCopy, args);
            #endif

            vprintf(message, args);

            #if defined(SAM_WINDOWS)
            char buffer[LOG_BUFFER_SIZE];
            std::vsnprintf(buffer, sizeof(buffer), message, argsCopy);
            buffer[LOG_BUFFER_SIZE - 1] = '\0';
            OutputDebugString(buffer);
            #endif
        }
        else
        {
            for (std::shared_ptr<logger> logger : loggers)
            {
                logger->record(mask, message, args);
            }
        }
        lock.unlock_read();
    }
}
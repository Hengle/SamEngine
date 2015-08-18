#pragma once

#include "class.h"
#include "rwlock.h"
#include "types.h"

#include <vector>
#include <memory>

namespace sam
{
    class logger;

    class log
    {
    public:
        enum class level : int32
        {
            error,
            warning,
            info,
            debug,
        };

        static void add_logger(std::shared_ptr<logger> &logger);

        static void set_level(level value);

        static level get_level();

        static void error(const char *message, ...);

        static void warning(const char *message, ...);

        static void info(const char *message, ...);

        static void debug(const char *message, ...);

        static void assert(const char *condition, const char *message, const char *filename, int32 line, const char *function);

        static void record(level mask, const char *message, va_list args);

    private:
        static level log_level;
        static rwlock lock;
        static std::vector<std::shared_ptr<logger>> loggers;
    };

    class logger
    {
    public:
        CREATE_FUNC_DECLARE(logger)

        virtual ~logger() {}

        virtual void assert(const char *condition, const char *message, const char *filename, int32 line, const char *function) {}

        virtual void record(log::level mask, const char *message, va_list args) {}
    };
}
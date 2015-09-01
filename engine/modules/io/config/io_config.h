#pragma once

#include <core/types.h>

namespace sam
{
    class io_config
    {
    public:
        io_config(int32 thread_count = 4) : thread_count(thread_count) {}

        int32 thread_count;
    };
}
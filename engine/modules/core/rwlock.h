#pragma once

#include "types.h"

#include <atomic>

namespace sam
{
    class rwlock
    {
    public:
        void lock_write();

        void unlock_write();

        void lock_read();

        void unlock_read();

    private:
        std::atomic_bool write_lock{ false };
        std::atomic_int read_count{ 0 };
    };
}
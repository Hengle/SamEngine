#pragma once

#include "types.h"

#include <atomic>

namespace sam
{
    class rwlock
    {
    public:
        rwlock();

        void lock_write();

        void unlock_write();

        void lock_read();

        void unlock_read();

    private:
        std::atomic_bool write_lock;
        std::atomic_int read_count;
    };
}
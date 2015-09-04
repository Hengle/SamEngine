#include "rwlock.h"

namespace sam
{
    void rwlock::lock_write()
    {
        while (write_lock.exchange(true, std::memory_order_acquire));
    }

    void rwlock::unlock_write()
    {
        write_lock.exchange(false, std::memory_order_release);
        while (read_count > 0);
    }

    void rwlock::lock_read()
    {
        while (write_lock);
        ++read_count;
    }

    void rwlock::unlock_read()
    {
        --read_count;
    }
}
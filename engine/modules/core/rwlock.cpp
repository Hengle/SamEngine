#include "rwlock.h"

namespace sam
{
    rwlock::rwlock() :
            write_lock(false),
            read_count(0)
    {
    }

    void rwlock::lock_write()
    {
        write_lock = true;
    }

    void rwlock::unlock_write()
    {
        write_lock = false;
    }

    void rwlock::lock_read()
    {
        while (write_lock) {}
        ++read_count;
    }

    void rwlock::unlock_read()
    {
        --read_count;
    }
}
#pragma once

#include <atomic>

namespace SamEngine
{
    class CORE_API RWLock
    {
    public:
        void LockWrite();

        void UnlockWrite();

        void LockRead();

        void UnlockRead();

    private:
        std::atomic_bool mWriteLock{ false };
        std::atomic_int mReadCount{ 0 };
    };

    inline void RWLock::LockWrite()
    {
        while (mWriteLock.exchange(true, std::memory_order_acquire));
    }

    inline void RWLock::UnlockWrite()
    {
        mWriteLock.exchange(false, std::memory_order_release);
        while (mReadCount > 0) {}
    }

    inline void RWLock::LockRead()
    {
        while (mWriteLock) {}
        ++mReadCount;
    }

    inline void RWLock::UnlockRead()
    {
        --mReadCount;
    }
}
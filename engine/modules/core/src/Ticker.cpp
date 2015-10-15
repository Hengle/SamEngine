#include "Ticker.h"
#include "ILog.h"

#include <algorithm>

namespace SamEngine
{
    TickID Ticker::Add(ITick *value)
    {
        auto new_id = ++mCurrentID;
        mAddCache.insert({ new_id, value });
        return new_id;
    }

    void Ticker::Remove(TickID value)
    {
        s_assert(std::find(mRemoveCache.begin(), mRemoveCache.end(), value) == mRemoveCache.end());
        s_assert(mTicks.find(value) != mTicks.end() || mAddCache.find(value) != mAddCache.end());
        mRemoveCache.push_back(value);
    }

    bool Ticker::Contain(TickID value) const
    {
        return mTicks.find(value) != mTicks.end() || mAddCache.find(value) != mAddCache.end();
    }

    void Ticker::Execute(TickCount now, TickCount delta)
    {
        RealRemove();
        RealAdd();
        for (auto &pair : mTicks)
        {
            pair.second->Tick(now, delta);
        }
        RealRemove();
        RealAdd();
    }

    void Ticker::RealAdd()
    {
        for (auto &pair : mAddCache)
        {
            mTicks.insert({ pair.first, pair.second });
        }
        mAddCache.clear();
    }

    void Ticker::RealRemove()
    {
        for (auto &value : mRemoveCache)
        {
            if (mTicks.find(value) != mTicks.end())
            {
                mTicks.erase(value);
            }
            else if (mAddCache.find(value) != mAddCache.end())
            {
                mAddCache.erase(value);
            }
        }
        mRemoveCache.clear();
    }
}

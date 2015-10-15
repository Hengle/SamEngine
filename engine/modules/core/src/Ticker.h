#pragma once

#include "ITicker.h"

#include <map>
#include <vector>

namespace SamEngine
{
    class Ticker : public ITicker
    {
    public:
        TickID Add(ITick *value) override;

        void Remove(TickID value) override;

        bool Contain(TickID value) const override;

        void Execute(TickCount now, TickCount delta) override;

    protected:
        void RealAdd();

        void RealRemove();

    private:
        TickID mCurrentID{ InvalidTickID };
        std::map<TickID, ITick *> mTicks;
        std::map<TickID, ITick *> mAddCache;
        std::vector<TickID> mRemoveCache;
    };
}
#pragma once

#include "Types.h"

#include <memory>

namespace SamEngine
{
    typedef int32 TickID;

    static const TickID InvalidTickID{ 0 };

    class CORE_API ITick
    {
    public:
        virtual ~ITick() {}

        virtual void Tick(TickCount now, TickCount delta) = 0;
    };

    class CORE_API ITicker
    {
    public:
        virtual ~ITicker() {}

        virtual TickID Add(ITick *value) = 0;

        virtual void Remove(TickID value) = 0;

        virtual bool Contain(TickID value) const = 0;

        virtual void Execute(TickCount now, TickCount delta) = 0;
    };
}
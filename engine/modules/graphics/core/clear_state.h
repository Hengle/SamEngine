#pragma once

#include "define.h"

#include "core/types.h"

namespace sam
{
    class clear_state
    {
    public:
        enum class type : uint8
        {
            none = 0,
            color = 1 << 0,
            depth = 1 << 1,
            stencil = 1 << 2,

            depth_and_stencil = depth | stencil,
            all = color | depth_and_stencil,
        };

        color color;

        float32 depth = 1.0f;

        uint8 stencil = 0;

        type action = type::all;
    };
}
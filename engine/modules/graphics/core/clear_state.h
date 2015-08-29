#pragma once

#include "define.h"

#include "core/types.h"

namespace sam
{
    class clear_state
    {
    public:
        static const uint8 clear_none = 0;
        static const uint8 clear_color = 1 << 0;
        static const uint8 clear_depth = 1 << 1;
        static const uint8 clear_stencil = 1 << 2;

        static const uint8 clear_depth_and_stencil = clear_depth | clear_stencil;
        static const uint8 clear_all = clear_color | clear_depth_and_stencil;

        color color;

        float32 depth = 1.0f;

        uint8 stencil = 0;

        uint8 action = clear_all;
    };
}
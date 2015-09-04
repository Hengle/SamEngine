#pragma once

#include "graphics/core/define.h"

namespace sam
{
    class draw_call_attribute
    {
    public:
        draw_type type{ draw_type::inlvalid };

        int32 first{ 0 };

        int32 count{ 0 };
    };
}
#pragma once

#include "graphics/core/define.h"
#include "graphics/config/graphics_config.h"

namespace sam
{
    class draw_call_attribute
    {
    public:
        draw_type draws[graphics_config::max_draw_count];

        int32 draw_count{ 0 };
    };
}
#pragma once

#include "graphics/core/define.h"

namespace sam
{
    class texture_attribute
    {
    public:
        texture_type type{ texture_type::invalid };

        pixel_format color_format{ pixel_format::none };

        pixel_format depth_format{ pixel_format::none };

        buffer_usage texture_usage{ buffer_usage::invalid };

        int32 width{ 0 };

        int32 height{ 0 };

        int32 depth{ 0 };

        int32 mipmap_count{ 1 };

        bool is_render_target{ false };
    };
}
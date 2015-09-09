#pragma once

#include "graphics/core/define.h"

namespace sam
{
    class texture_attribute
    {
    public:
        texture_type type{ texture_type::texture_2d };

        pixel_format color_format{ pixel_format::rgba8 };

        pixel_format depth_format{ pixel_format::none };

        int32 width{ 0 };

        int32 height{ 0 };

        int32 depth{ 0 };

        int32 mipmap_count{ 1 };

        bool is_render_target{ false };
    };
}
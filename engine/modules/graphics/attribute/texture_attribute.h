#pragma once

#include "graphics/core/define.h"

#include <string>

namespace sam
{
    class texture_attribute
    {
    public:
        std::string location{ "" };

        texture_type type{ texture_type::invalid };

        pixel_format color_format{ pixel_format::NONE };

        pixel_format depth_format{ pixel_format::NONE };

        resource_usage texture_usage{ resource_usage::invalid };

        int32 width{ 0 };

        int32 height{ 0 };

        int32 depth{ 0 };

        int32 mipmap_count{ 1 };

        bool is_render_target{ false };
    };
}
#pragma once

#include "core/types.h"

#include "graphics/core/define.h"

#include <string>

namespace sam
{
    class render_target_attribute
    {
    public:
        int32 width = 0;

        int32 height = 0;

        int32 position_x = 0;

        int32 position_y = 0;

        int32 frame_buffer_width = 0;

        int32 frame_buffer_height = 0;

        pixel_format color_format = pixel_format::RGB8;

        pixel_format depth_format = pixel_format::D24S8;

        int32 sample_count = 1;

        bool is_fullscreen = false;

        int32 swap_interval = 1;

        std::string title = "SamEngine";
    };
}
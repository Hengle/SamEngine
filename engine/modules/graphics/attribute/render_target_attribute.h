#pragma once

#include <core/types.h>

#include <window/config/window_config.h>

namespace sam
{
    class render_target_attribute
    {
    public:
        static render_target_attribute from_window_config(const window_config &config);

        int32 width{ 0 };

        int32 height{ 0 };

        int32 position_x{ 0 };

        int32 position_y{ 0 };

        int32 frame_buffer_width{ 0 };

        int32 frame_buffer_height{ 0 };

        pixel_format color_format{ pixel_format::rgb8 };

        pixel_format depth_format{ pixel_format::d24s8 };
    };

    inline render_target_attribute render_target_attribute::from_window_config(const window_config &config)
    {
        render_target_attribute attribute;
        attribute.width = config.width;
        attribute.height = config.height;
        attribute.position_x = 0;
        attribute.position_y = 0;
        attribute.frame_buffer_width = config.width;
        attribute.frame_buffer_height = config.height;
        attribute.color_format = config.color_format;
        attribute.depth_format = config.depth_format;
        return attribute;
    }
}
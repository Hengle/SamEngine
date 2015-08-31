#pragma once

#include "graphics/attribute/render_target_attribute.h"

#include "core/types.h"

#include <string>

namespace sam
{
    class graphics_config
    {
    public:
        static graphics_config window(int32 width, int32 height, const char *title);

        static graphics_config full_screen(const char *title);

        render_target_attribute get_render_target_attribute() const;

        int32 width{ 1024 };

        int32 height{ 768 };

        pixel_format color_format{ pixel_format::RGB8 };

        pixel_format depth_format{ pixel_format::D24S8 };

        int32 sample_count{ 1 };

        bool is_full_screen{ false };

        int32 swap_interval{ 1 };

        std::string title{ "SamEngine" };

        int32 registry_size{ 256 };

        int32 texture_pool_size{ 256 };
    };

    inline graphics_config graphics_config::window(int32 width, int32 height, const char *title)
    {
        graphics_config config;
        config.width = width;
        config.height = height;
        config.is_full_screen = false;
        config.title = title;
        return config;
    }

    inline graphics_config graphics_config::full_screen(const char *title)
    {
        graphics_config config;
        config.is_full_screen = true;
        config.title = title;
        return config;
    }

    inline render_target_attribute graphics_config::get_render_target_attribute() const
    {
        render_target_attribute attribute;
        attribute.width = width;
        attribute.height = height;
        attribute.position_x = 0;
        attribute.position_y = 0;
        attribute.frame_buffer_width = width;
        attribute.frame_buffer_height = height;
        attribute.color_format = color_format;
        attribute.depth_format = depth_format;
        attribute.sample_count = sample_count;
        attribute.is_fullscreen = is_full_screen;
        attribute.swap_interval = swap_interval;
        attribute.title = title;
        return attribute;
    }
}
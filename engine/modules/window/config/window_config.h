#pragma once

#include "window/core/define.h"

#include <core/types.h>

#include <string>

namespace sam
{
    class window_config
    {
    public:
        static window_config window(int32 width, int32 height, const char *title);

        static window_config full_screen(const char *title);

        int32 width{ 1024 };

        int32 height{ 768 };

        pixel_format color_format{ pixel_format::rgb8 };

        pixel_format depth_format{ pixel_format::d24s8 };

        int32 sample_count{ 1 };

        bool is_full_screen{ false };

        int32 swap_interval{ 1 };

        std::string title{ "SamEngine" };
    };

    inline window_config window_config::window(int32 width, int32 height, const char *title)
    {
        window_config config;
        config.width = width;
        config.height = height;
        config.is_full_screen = false;
        config.title = title;
        return config;
    }

    inline window_config window_config::full_screen(const char *title)
    {
        window_config config;
        config.is_full_screen = true;
        config.title = title;
        return config;
    }
}
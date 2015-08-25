#pragma once

#include "core/types.h"

#include <string>

namespace sam
{
    class graphics_config
    {
    public:
        static graphics_config window(int32 width, int32 height, const char *title);

        static graphics_config fullscreen(const char *title);

        int32 width = 1024;

        int32 height = 768;

        bool is_fullscreen = false;

        std::string title = "SamEngine";

        int32 registery_size = 256;

        int32 texture_pool_size = 256;
    };

    inline graphics_config graphics_config::window(int32 width, int32 height, const char *title)
    {
        graphics_config config;
        config.width = width;
        config.height = height;
        config.is_fullscreen = false;
        config.title = title;
        return config;
    }

    inline graphics_config graphics_config::fullscreen(const char *title)
    {
        graphics_config config;
        config.is_fullscreen = true;
        config.title = title;
        return config;
    }
}
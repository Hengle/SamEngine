#pragma once

#include "WindowDefine.h"

#include <CoreModule.h>

#include <string>

namespace SamEngine
{
    struct WINDOW_API WindowConfig
    {
        static WindowConfig ForWindow(int32 width, int32 height, const char *title);

        static WindowConfig ForFullScreen(const char *title);

        int32 Width{ 1024 };

        int32 Height{ 768 };

        PixelFormat ColorFormat{ PixelFormat::RGB8 };

        PixelFormat DepthFormat{ PixelFormat::D24S8 };

        int32 SampleCount{ 1 };

        bool IsFullScreen{ false };

        int32 SwapInterval{ 1 };

        std::string Title{ "SamEngine" };
    };

    inline WindowConfig WindowConfig::ForWindow(int32 width, int32 height, const char *title)
    {
        WindowConfig config;
        config.Width = width;
        config.Height = height;
        config.IsFullScreen = false;
        config.Title = title;
        return config;
    }

    inline WindowConfig WindowConfig::ForFullScreen(const char *title)
    {
        WindowConfig config;
        config.IsFullScreen = true;
        config.Title = title;
        return config;
    }
}
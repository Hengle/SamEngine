#pragma once

namespace sam
{
    class renderer_base;

    class window_base;

    class graphics_attribute
    {
    public:
        renderer_base *renderer{ nullptr };

        window_base *window{ nullptr };
    };
}
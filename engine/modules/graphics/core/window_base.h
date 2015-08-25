#pragma once

#include "graphics/config/graphics_config.h"

#include "core/types.h"

#include <string>

namespace sam
{
    class window_base
    {
    public:
        window_base() :
            width(0),
            height(0),
            title("") {}

        virtual ~window_base() {}

        virtual void initialize(const graphics_config &config)
        {
            width = config.width;
            height = config.height;
            title = config.title;
        }

        virtual void finalize() {}

        virtual bool available() { return false; }

        virtual bool should_close() { return true; }

        virtual void handle_event() {}

        virtual void present() {}

    protected:
        int32 width;
        int32 height;
        std::string title;
    };
};
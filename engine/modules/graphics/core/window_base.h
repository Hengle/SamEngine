#pragma once

#include "core/types.h"

#include <string>

namespace sam
{
    class window_base
    {
    public:
        window_base(int32 width, int32 height, const std::string &title) :
            width(width),
            height(height),
            title(title) {}

        virtual ~window_base() {}

        virtual void open() {}

        virtual void close() {}

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
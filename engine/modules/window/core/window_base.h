#pragma once

#include "window/config/window_config.h"

namespace sam
{
    class window_base
    {
    public:
        virtual ~window_base() {}

        virtual void initialize(const window_config &config) = 0;

        virtual void finalize() = 0;

        virtual bool available() = 0;

        virtual bool should_close() = 0;

        virtual void handle_event() = 0;

        virtual void present() = 0;
    };
};
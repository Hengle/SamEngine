#pragma once

#include "config/window_config.h"

#include <core/assert.h>
#include <core/func_group.h>

#if defined(SAM_WINDOWS) || defined(SAM_OSX) || defined(SAM_MINGW)
#    include "window/glfw/glfw_window.h"
#endif

namespace sam
{
    class window
    {
    public:
        static void initialize(const window_config &config);

        static void finalize();

        static bool available();

        static bool should_close();

        static void handle_event();

        static void present();

        static const window_config &get_config();

    private:
        static class state
        {
        public:
            window_config config;

            func_group::id func_id{ func_group::invalid_id };

            #if defined(SAM_WINDOWS) || defined(SAM_OSX) || defined(SAM_MINGW)
            glfw_window window;
            #endif
        } *window_state;
    };

    inline const window_config &window::get_config()
    {
        s_assert(available());
        return window_state->config;
    }
}
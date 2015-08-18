#pragma once

#include "window.h"

#include "core/func_group.h"
#include "core/types.h"

#include <string>

namespace sam
{
    class graphics
    {
    public:
        class param
        {
        public:
            static param window(int32 width, int32 height, const char *title);

            static param fullscreen(const char *title);

            int32 width, height;

            bool is_fullscreen;

            std::string title;
        };

        static void initialize(const param &p);

        static void finalize();

        static bool available();

        static bool should_quit();

        static void present();

    protected:
        static void main_loop();

    private:
        static class state
        {
        public:
            explicit state(const param &p);

            ~state();

            window window;

            func_group::id func_id;
        } *graphics_state;
    };
}
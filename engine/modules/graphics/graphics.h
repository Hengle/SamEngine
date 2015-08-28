#pragma once

#include "config/graphics_config.h"
#include "resource/graphics_resource_manager.h"
#include "renderer/renderer.h"
#include "window/window.h"

#include "core/func_group.h"

namespace sam
{
    class graphics
    {
    public:
        static void initialize(const graphics_config &config);

        static void finalize();

        static bool available();

        static bool should_quit();

        static void present();

        static resource::id create(const texture_config &config);

        static void apply_default_target(const clear_state &state);

    protected:
        static void main_loop();

    private:
        static class state
        {
        public:
            explicit state(const graphics_config &config);

            ~state();

            window window;

            renderer renderer;

            graphics_resource_manager graphics_resource_manager;

            func_group::id func_id;
        } *graphics_state;
    };
}
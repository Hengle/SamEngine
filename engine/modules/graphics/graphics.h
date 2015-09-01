#pragma once

#include "config/graphics_config.h"
#include "resource/graphics_resource_manager.h"
#include "renderer/renderer.h"

namespace sam
{
    class graphics
    {
    public:
        static void initialize(const graphics_config &config);

        static void finalize();

        static bool available();

        static void render();

        static resource::id create(const texture_config &config);

        static void apply_default_target(const clear_state &state);

    private:
        static class state
        {
        public:
            renderer renderer;

            graphics_resource_manager graphics_resource_manager;
        } *graphics_state;
    };
}
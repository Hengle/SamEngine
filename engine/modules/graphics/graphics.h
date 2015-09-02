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

        template <class CONFIG>
        static resource::id create(const CONFIG &config, data_ptr data);

        static void apply_default_target(const clear_state &state);

    private:
        static class state
        {
        public:
            renderer renderer;

            graphics_resource_manager graphics_resource_manager;
        } *graphics_state;
    };

    template <class CONFIG>
    resource::id graphics::create(const CONFIG &config, data_ptr data)
    {
        s_assert(available());
        return graphics_state->graphics_resource_manager.create(config, data);
    }
}
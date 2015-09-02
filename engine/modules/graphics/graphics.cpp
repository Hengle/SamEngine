#include "graphics.h"
#include "attribute/graphics_attribute.h"

#include <core/assert.h>
#include <core/core.h>
#include <window/window.h>

namespace sam
{
    graphics::state *graphics::graphics_state = nullptr;

    void graphics::initialize(const graphics_config &config)
    {
        s_assert(window::available());
        s_assert(!available());
        graphics_state = new state();

        graphics_attribute attribute;
        attribute.renderer = &graphics_state->renderer;
        attribute.mesh_pool = &graphics_state->graphics_resource_manager.mesh_pool;
        attribute.shader_pool = &graphics_state->graphics_resource_manager.shader_pool;
        attribute.texture_pool = &graphics_state->graphics_resource_manager.texture_pool;
        attribute.draw_state_pool = &graphics_state->graphics_resource_manager.draw_state_pool;

        graphics_state->renderer.initialize(config, attribute);
        graphics_state->graphics_resource_manager.initialize(config, attribute);
    }

    void graphics::finalize()
    {
        s_assert(available());
        graphics_state->renderer.finalize();
        graphics_state->graphics_resource_manager.finalize();
        delete graphics_state;
        graphics_state = nullptr;
    }

    bool graphics::available()
    {
        return graphics_state != nullptr;
    }

    void graphics::render()
    {
        s_assert(available());
        graphics_state->renderer.render();
    }

    void graphics::apply_default_target(const clear_state &state)
    {
        s_assert(available());
        return graphics_state->renderer.apply_target(nullptr, state);
    }
}
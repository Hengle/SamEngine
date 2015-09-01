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

    resource::id graphics::create(const texture_config &config)
    {
        s_assert(available());
        return graphics_state->graphics_resource_manager.create(config);
    }

    void graphics::apply_default_target(const clear_state &state)
    {
        s_assert(available());
        return graphics_state->renderer.apply_target(nullptr, state);
    }
}
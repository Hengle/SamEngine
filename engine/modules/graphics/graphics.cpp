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
        attribute.mesh_pool = &graphics_state->resource.mesh_pool;
        attribute.shader_pool = &graphics_state->resource.shader_pool;
        attribute.texture_pool = &graphics_state->resource.texture_pool;
        attribute.draw_state_pool = &graphics_state->resource.draw_state_pool;

        graphics_state->renderer.initialize(config, attribute);
        graphics_state->resource.initialize(config, attribute);
    }

    void graphics::finalize()
    {
        s_assert(available());
        graphics_state->renderer.finalize();
        graphics_state->resource.finalize();
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

    resource::label graphics::push_resource_label()
    {
        s_assert(available());
        return graphics_state->resource.push_label();
    }

    void graphics::push_resource_label(resource::label label)
    {
        s_assert(available());
        graphics_state->resource.push_label(label);
    }

    void graphics::pop_resource_label()
    {
        s_assert(available());
        graphics_state->resource.pop_label();
    }

    resource::id graphics::find_resource(const resource_name &name)
    {
        s_assert(available());
        return graphics_state->resource.find(name);
    }

    void graphics::destroy_resource(resource::label label)
    {
        s_assert(available());
        graphics_state->resource.destroy(label);
    }

    void graphics::apply_default_target(const clear_state &state)
    {
        s_assert(available());
        return graphics_state->renderer.apply_target(nullptr, state);
    }

    void graphics::apply_render_target(resource::id target, const clear_state &state)
    {
        s_assert(available());
        auto texture = graphics_state->resource.texture_pool.find_resource(target);
        s_assert(texture != nullptr);
        graphics_state->renderer.apply_target(texture, state);
    }

    void graphics::apply_view_port(int32 x, int32 y, int32 width, int32 height)
    {
        s_assert(available());
        graphics_state->renderer.apply_view_port(x, y, width, height);
    }

    void graphics::apply_scissor(int32 x, int32 y, int32 width, int32 height)
    {
        s_assert(available());
        graphics_state->renderer.apply_scissor(x, y, width, height);
    }

    void graphics::apply_draw_state(resource::id state)
    {
        s_assert(available());
        auto draw_state = graphics_state->resource.draw_state_pool.find_resource(state);
        graphics_state->renderer.apply_draw_state(draw_state);
    }

    void graphics::draw(int32 index)
    {
        s_assert(available());
        graphics_state->renderer.draw(index);
    }

    void graphics::draw(const draw_call_attribute &attribute)
    {
        s_assert(available());
        graphics_state->renderer.draw(attribute);
    }

    void graphics::reset()
    {
        s_assert(available());
        graphics_state->renderer.reset();
    }
}
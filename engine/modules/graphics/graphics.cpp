#include "graphics.h"

#include "core/assert.h"
#include "core/core.h"

namespace sam
{

    graphics::state::state(const graphics_config &config) :
        func_id(func_group::invalid_id)
    {
        window.initialize(config);
        graphics_resource_manager.initialize(config);
    }

    graphics::state::~state()
    {
        window.finalize();
        graphics_resource_manager.finalize();
    }

    graphics::state *graphics::graphics_state = nullptr;

    void graphics::initialize(const graphics_config &config)
    {
        s_assert(!available());
        graphics_state = new state(config);
        graphics_state->func_id = core::get_before_frame_func_group()->add(main_loop);
    }

    void graphics::finalize()
    {
        s_assert(available());
        core::get_before_frame_func_group()->remove(graphics_state->func_id);
        delete graphics_state;
        graphics_state = nullptr;
    }

    bool graphics::available()
    {
        return graphics_state != nullptr;
    }

    bool graphics::should_quit()
    {
        s_assert(available());
        return graphics_state->window.should_close();
    }

    void graphics::present()
    {
        s_assert(available());
        graphics_state->window.present();
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

    void graphics::main_loop()
    {
        s_assert(available());
        graphics_state->window.handle_event();
    }
}
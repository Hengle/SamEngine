#include "window.h"

#include <core/core.h>

namespace sam
{
    window::state *window::window_state = nullptr;

    void window::initialize(const window_config& config)
    {
        s_assert(!available());
        window_state = new state();
        window_state->window.initialize(config);
        window_state->func_id = core::get_before_frame_func_group()->add(handle_event);
    }

    void window::finalize()
    {
        s_assert(available());
        core::get_before_frame_func_group()->remove(window_state->func_id);
        window_state->window.finalize();
        delete window_state;
        window_state = nullptr;
    }

    bool window::available()
    {
        return window_state != nullptr;
    }

    bool window::should_close()
    {
        s_assert(available());
        return window_state->window.should_close();
    }

    void window::handle_event()
    {
        s_assert(available());
        return window_state->window.handle_event();
    }

    void window::present()
    {
        s_assert(available());
        return window_state->window.present();
    }
}
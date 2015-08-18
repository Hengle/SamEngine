#include "graphics.h"

#include "core/assert.h"
#include "core/core.h"

namespace sam
{
    graphics::param graphics::param::window(int32 width, int32 height, const char *title)
    {
        param p;
        p.width = width;
        p.height = height;
        p.is_fullscreen = false;
        p.title = title;
        return p;
    }

    graphics::param graphics::param::fullscreen(const char *title)
    {
        param p;
        p.is_fullscreen = true;
        p.title = title;
        return p;
    }

    graphics::state::state(const param &p) :
        window(p.width, p.height, p.title),
        func_id(func_group::invalid_id)
    {
        window.open();
    }

    graphics::state::~state()
    {
        window.close();
    }

    graphics::state *graphics::graphics_state = nullptr;

    void graphics::initialize(const param &p)
    {
        s_assert(!available());
        graphics_state = new state(p);
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

    void graphics::main_loop()
    {
        s_assert(available());
        graphics_state->window.handle_event();
    }
}
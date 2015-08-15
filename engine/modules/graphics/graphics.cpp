#include "graphics.h"

#include "core/assert.h"

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

    graphics::state::state(const param &p)
    {

    }

    graphics::state::~state()
    {
    }

    graphics::state *graphics::graphics_state = nullptr;

    void graphics::initialize(const param &p)
    {
        s_assert(!available());
        graphics_state = new state(p);
    }

    void graphics::finalize()
    {
        s_assert(available());
        delete graphics_state;
        graphics_state = nullptr;
    }

    bool graphics::available()
    {
        return graphics_state != nullptr;
    }
}
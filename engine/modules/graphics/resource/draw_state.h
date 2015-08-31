#pragma once

#include <memory>

#if defined(SAM_WINDOWS) || defined(SAM_OSX) || defined(SAM_MINGW)
#    include "graphics/gl/gl_draw_state.h"
namespace sam
{
    typedef gl_draw_state draw_state;
}
#endif

namespace sam
{
    typedef std::shared_ptr<draw_state> draw_state_ptr;
}
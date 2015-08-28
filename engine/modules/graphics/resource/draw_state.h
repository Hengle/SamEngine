#pragma once

#if defined(SAM_WIN32) || defined(SAM_APPLE)
#    include "graphics/gl/gl_draw_state.h"
namespace sam
{
    typedef gl_draw_state draw_state;
}
#endif
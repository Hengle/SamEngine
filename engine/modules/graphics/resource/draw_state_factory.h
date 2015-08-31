#pragma once

#if defined(SAM_WINDOWS) || defined(SAM_OSX) || defined(SAM_MINGW)
#    include "graphics/gl/gl_draw_state_factory.h"
namespace sam
{
    typedef gl_draw_state_factory draw_state_factory;
}
#endif
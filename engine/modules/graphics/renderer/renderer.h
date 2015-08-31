#pragma once

#if defined(SAM_WINDOWS) || defined(SAM_OSX) || defined(SAM_MINGW)
#    include "graphics/gl/gl_renderer.h"
namespace sam
{
    typedef gl_renderer renderer;
}
#endif
#pragma once

#if defined(SAM_WIN32) || defined(SAM_APPLE)
#    include "graphics/gl/gl_renderer.h"
namespace sam
{
    typedef gl_renderer renderer;
}
#endif
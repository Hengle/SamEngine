#pragma once

#if defined(SAM_WIN32) || defined(SAM_APPLE)
#    include "graphics/gl/gl_shader.h"
namespace sam
{
    typedef gl_shader shader;
}
#endif
#pragma once

#if defined(SAM_WIN32) || defined(SAM_APPLE)
#    include "graphics/gl/gl_mesh.h"
namespace sam
{
    typedef gl_mesh mesh;
}
#endif
#pragma once

#include <memory>

#if defined(SAM_WINDOWS) || defined(SAM_OSX) || defined(SAM_MINGW)
#    include "graphics/gl/gl_mesh.h"
namespace sam
{
    typedef gl_mesh mesh;
}
#endif

namespace sam
{
    typedef std::shared_ptr<mesh> mesh_ptr;
}
#pragma once

#include <memory>

#if defined(SAM_WINDOWS) || defined(SAM_OSX) || defined(SAM_MINGW)
#    include "graphics/gl/gl_texture.h"
namespace sam
{
    typedef gl_texture texture;
}
#endif

namespace sam
{
    typedef std::shared_ptr<texture> texture_ptr;
}
#pragma once

#include <memory>

#if defined(SAM_WINDOWS) || defined(SAM_OSX) || defined(SAM_MINGW)
#    include "graphics/gl/gl_shader.h"
namespace sam
{
    typedef gl_shader shader;
}
#endif

namespace sam
{
    typedef std::shared_ptr<shader> shader_ptr;
}
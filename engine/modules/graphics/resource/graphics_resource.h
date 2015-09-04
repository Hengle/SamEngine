#pragma once

#include <memory>

#if defined(SAM_WINDOWS) || defined(SAM_OSX) || defined(SAM_MINGW)
#    include "graphics/gl/gl_mesh.h"
#    include "graphics/gl/gl_shader.h"
#    include "graphics/gl/gl_texture.h"
#    include "graphics/gl/gl_draw_state.h"
namespace sam
{
    typedef gl_mesh mesh;
    typedef gl_shader shader;
    typedef gl_texture texture;
    typedef gl_draw_state draw_state;
}
#endif

namespace sam
{
    typedef std::shared_ptr<mesh> mesh_ptr;
    typedef std::shared_ptr<shader> shader_ptr;
    typedef std::shared_ptr<texture> texture_ptr;
    typedef std::shared_ptr<draw_state> draw_state_ptr;
}
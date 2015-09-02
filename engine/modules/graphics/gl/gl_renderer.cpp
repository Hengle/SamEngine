#include "gl_renderer.h"
#include "gl.h"
#include "gl_texture.h"

namespace sam
{
    gl_renderer::gl_renderer()
    {
    }

    gl_renderer::~gl_renderer()
    {
    }

    void gl_renderer::initialize(const graphics_config &config, const graphics_attribute &attribute)
    {
        renderer_base::initialize(config, attribute);
        if (gladLoadGL() == 0)
        {
            s_error("OpenGL init error!\n");
        }
        reset_depth_stencil_state();
        reset_blend_state();
        reset_rasterizer_state();
        reset_mesh_state();
        reset_shader_state();
        reset_texture_state();
    }

    void gl_renderer::finalize()
    {
        reset_mesh_state();
        reset_shader_state();
        reset_texture_state();
        renderer_base::finalize();
    }

    void gl_renderer::apply_target(texture_ptr texture, const clear_state &state)
    {
        renderer_base::apply_target(texture, state);
        if (target != texture)
        {
            if (texture == nullptr)
            {
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            }
            else
            {
                glBindFramebuffer(GL_FRAMEBUFFER, texture->texture);
            }
        }
        target = texture;

        apply_view_port(0, 0, target_attribute.frame_buffer_width, target_attribute.frame_buffer_height);

        if (cache.rasterizer_state_cache.is_scissor_test_enable)
        {
            cache.rasterizer_state_cache.is_scissor_test_enable = false;
            glDisable(GL_SCISSOR_TEST);
        }

        GLbitfield clear_mask = 0;

        if (state.action & clear_state::clear_color)
        {
            clear_mask |= GL_COLOR_BUFFER_BIT;
            glClearColor(state.color.r, state.color.g, state.color.b, state.color.a);
            if (cache.blend_state_cache.color_mask != pixel_channel_type::rgba)
            {
                cache.blend_state_cache.color_mask = pixel_channel_type::rgba;
                glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
            }
        }

        if (state.action & clear_state::clear_depth)
        {
            clear_mask |= GL_DEPTH_BUFFER_BIT;
            glClearDepth(state.depth);
            if (!cache.depth_stencil_state_cache.is_depth_enable)
            {
                cache.depth_stencil_state_cache.is_depth_enable = true;
                glDepthMask(GL_TRUE);
            }
        }

        if (state.action & clear_state::clear_stencil)
        {
            clear_mask |= GL_STENCIL_BUFFER_BIT;
            glClearStencil(state.stencil);
            if (cache.depth_stencil_state_cache.stencil_write_mask != 0xff)
            {
                cache.depth_stencil_state_cache.stencil_write_mask = 0xff;
                glStencilMask(0xff);
            }
        }

        if (clear_mask != 0)
        {
            glClear(clear_mask);
        }

        s_check_gl_error();
    }

    void gl_renderer::apply_view_port(int32 x, int32 y, int32 width, int32 height)
    {
        if (cache.view_port_x != x || cache.view_port_y != y || cache.view_port_width != width || cache.view_port_height != height)
        {
            cache.view_port_x = x;
            cache.view_port_y = y;
            cache.view_port_width = width;
            cache.view_port_height = height;
            glViewport(x, y, width, height);
        }
    }

    void gl_renderer::apply_scissor(int32 x, int32 y, int32 width, int32 height)
    {
        if (cache.scissor_x != x || cache.scissor_y != y || cache.scissor_width != width || cache.scissor_height != height)
        {
            cache.scissor_x = x;
            cache.scissor_y = y;
            cache.scissor_width = width;
            cache.scissor_height = height;
            glScissor(x, y, width, height);
        }
    }

    void gl_renderer::reset_mesh_state()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        s_check_gl_error();
        cache.vertex_buffer = 0;
        cache.index_buffer = 0;
        std::memset(cache.vertex_attribute, 0, sizeof(cache.vertex_attribute));
//        std::memset(cache.gl_vertex_attribute, 0, sizeof(cache.gl_vertex_attribute));
    }

    void gl_renderer::reset_shader_state()
    {
        glUseProgram(0);
        s_check_gl_error();
        cache.program = 0;
    }

    void gl_renderer::reset_texture_state()
    {
        std::memset(cache.texture_2d, 0, sizeof(cache.texture_2d));
        std::memset(cache.texture_cube, 0, sizeof(cache.texture_cube));
    }

    void gl_renderer::bind_vertex_buffer(GLuint buffer)
    {
        if (buffer != cache.vertex_buffer)
        {
            cache.vertex_buffer = buffer;
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            s_check_gl_error();
        }
    }

    void gl_renderer::bind_index_buffer(GLuint buffer)
    {
        if (buffer != cache.index_buffer)
        {
            cache.index_buffer = buffer;
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
            s_check_gl_error();
        }
    }

    void gl_renderer::bind_program(GLuint program)
    {
        if (program != cache.program)
        {
            cache.program = program;
            glUseProgram(program);
            s_check_gl_error();
        }
    }

    void gl_renderer::bind_texture(int32 index, GLenum target, GLuint texture)
    {
        s_assert_range(index, 0, graphics_config::max_texture_count);
        s_assert(target == GL_TEXTURE_2D || target == GL_TEXTURE_CUBE_MAP);

        auto *texture_cache = target == GL_TEXTURE_2D ? cache.texture_2d : cache.texture_cube;
        if (texture != texture_cache[index])
        {
            texture_cache[index] = texture;
            glActiveTexture(GL_TEXTURE0 + index);
            s_check_gl_error();
            glBindTexture(target, texture);
            s_check_gl_error();
        }
    }

    void gl_renderer::reset_blend_state()
    {
        cache.blend_state_cache = blend_state();
        glDisable(GL_BLEND);
        glBlendFuncSeparate(GL_ONE, GL_ZERO, GL_ONE, GL_ZERO);
        glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        cache.blend_color = color(1.0f, 1.0f, 1.0f, 1.0f);
        glBlendColor(1.0f, 1.0f, 1.0f, 1.0f);
        s_check_gl_error();
    }

    void gl_renderer::reset_depth_stencil_state()
    {
        cache.depth_stencil_state_cache = depth_stencil_state();
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);
        glDepthMask(GL_FALSE);
        glDisable(GL_STENCIL_TEST);
        glStencilFunc(GL_ALWAYS, 0, 0xFFFFFFFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        glStencilMask(0xFFFFFFFF);
        s_check_gl_error();
    }

    void gl_renderer::reset_rasterizer_state()
    {
        cache.rasterizer_state_cache = rasterizer_state();
        glDisable(GL_CULL_FACE);
        glFrontFace(GL_CW);
        glCullFace(GL_BACK);
        glDisable(GL_POLYGON_OFFSET_FILL);
        glDisable(GL_SCISSOR_TEST);
        glEnable(GL_DITHER);
        glEnable(GL_MULTISAMPLE);
        s_check_gl_error();
    }
}
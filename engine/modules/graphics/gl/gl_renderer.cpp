#include "gl_renderer.h"
#include "gl.h"

#include "graphics/core/define.h"

#include <window/core/define.h>

namespace sam
{
    void gl_renderer::initialize(const graphics_config &config, const graphics_attribute &attribute)
    {
        renderer_base::initialize(config, attribute);
        if (gladLoadGL() == 0)
        {
            s_error("OpenGL init error!\n");
        }
        glGenVertexArrays(1, &cache.vao);
        glBindVertexArray(cache.vao);
        reset();
    }

    void gl_renderer::finalize()
    {
        reset();
        glDeleteVertexArrays(1, &cache.vao);
        cache.vao = 0;
        renderer_base::finalize();
    }

    void gl_renderer::apply_target(texture *texture, const clear_state &state)
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
                glBindFramebuffer(GL_FRAMEBUFFER, texture->sampler);
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

    void gl_renderer::apply_draw_state(draw_state *draw_state)
    {
        renderer_base::apply_draw_state(draw_state);
        if (draw_state)
        {
            auto &config = draw_state->config;
            s_assert(config.blend_state.color_format == target_attribute.color_format);
            s_assert(config.blend_state.depth_format == target_attribute.depth_format);
            if (config.blend_colr != cache.blend_color)
            {
                cache.blend_color = config.blend_colr;
                glBlendColor(config.blend_colr.r, config.blend_colr.g, config.blend_colr.b, config.blend_colr.a);
                s_check_gl_error();
            }
            apply_depth_stencil_state(config.depth_stencil_state);
            apply_blend_state(config.blend_state);
            apply_rasterizer_state(config.rasterizer_state);
            apply_shader(draw_state->shader);
            apply_mesh(draw_state->mesh);
        }
    }

    void gl_renderer::draw(int32 index)
    {
        if (state != nullptr && index < state->mesh->config.draw_count)
        {
            draw(state->mesh->config.draws[index]);
        }
    }

    void gl_renderer::draw(const draw_call_attribute &attribute)
    {
        if (state != nullptr)
        {
            s_check_gl_error();
            auto &type = state->mesh->config.indices.type;
            if (type == index_type::none)
            {
                glDrawArrays(gl::from_draw_type(attribute.type), attribute.first, attribute.count);
            }
            else
            {
                glDrawElements(gl::from_draw_type(attribute.type), attribute.count, gl::from_index_type(type), reinterpret_cast<GLvoid *>(attribute.first * sizeof_index(type)));
            }
            s_check_gl_error();
        }
    }

    void gl_renderer::reset()
    {
        reset_mesh();
        reset_shader();
        reset_texture();
        reset_blend_state();
        reset_depth_stencil_state();
        reset_rasterizer_state();
    }

    void gl_renderer::apply_mesh(mesh *mesh)
    {
        s_assert(mesh != nullptr);

        s_check_gl_error();
        bind_index_buffer(mesh->index_buffer);
        for (auto i = 0; i < graphics_config::max_vertex_node_count; ++i)
        {
            auto &vertex_buffer = mesh->vertex_buffer[mesh->current_vertex_buffer];
            auto &attribute = mesh->vertex_attribute[i];
            if (vertex_buffer != cache.vertex_buffer || attribute != cache.gl_vertex_attribute[i])
            {
                if (attribute.enabled)
                {
                    bind_vertex_buffer(vertex_buffer);
                    glVertexAttribPointer(attribute.index, attribute.size, attribute.type, attribute.normalized, attribute.stride, attribute.offset);
                    s_check_gl_error();
                    if (!cache.gl_vertex_attribute[i].enabled)
                    {
                        glEnableVertexAttribArray(attribute.index);
                        s_check_gl_error();
                    }
                }
                else
                {
                    if (cache.gl_vertex_attribute[i].enabled)
                    {
                        glDisableVertexAttribArray(attribute.index);
                        s_check_gl_error();
                    }
                }
                // TODO divisor
                cache.vertex_buffer = vertex_buffer;
                cache.gl_vertex_attribute[i] = attribute;
            }
        }
        s_check_gl_error();
    }

    void gl_renderer::reset_mesh()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        s_check_gl_error();
        cache.vertex_buffer = 0;
        cache.index_buffer = 0;
        std::memset(cache.vertex_attribute, 0, sizeof(cache.vertex_attribute));
        std::memset(cache.gl_vertex_attribute, 0, sizeof(cache.gl_vertex_attribute));
    }
    
    void gl_renderer::apply_shader(shader *shader)
    {
        s_assert(shader != nullptr && shader->program != 0);
        bind_program(shader->program);
    }

    void gl_renderer::reset_shader()
    {
        glUseProgram(0);
        s_check_gl_error();
        cache.program = 0;
    }

    void gl_renderer::apply_texture(texture *texture)
    {
        s_assert(texture != nullptr && texture->sampler != 0);
        // TODO 
        bind_texture(0, texture->target, texture->sampler);
    }

    void gl_renderer::reset_texture()
    {
        std::memset(cache.texture_2d, 0, sizeof(cache.texture_2d));
        std::memset(cache.texture_cube, 0, sizeof(cache.texture_cube));
    }

    void gl_renderer::apply_blend_state(const blend_state &blend_state)
    {
        if (cache.blend_state_cache != blend_state)
        {
            if (blend_state.enabled != cache.blend_state_cache.enabled)
            {
                if (blend_state.enabled)
                {
                    glEnable(GL_BLEND);
                }
                else
                {
                    glDisable(GL_BLEND);
                }
            }
            if (blend_state.src_rgb_factor != cache.blend_state_cache.src_rgb_factor ||
                blend_state.dst_rgb_factor != cache.blend_state_cache.dst_rgb_factor ||
                blend_state.src_alpha_factor != cache.blend_state_cache.src_alpha_factor ||
                blend_state.dst_alpha_factor != cache.blend_state_cache.dst_alpha_factor)
            {
                glBlendFuncSeparate(gl::from_blend_factor(blend_state.src_rgb_factor),
                    gl::from_blend_factor(blend_state.dst_rgb_factor),
                    gl::from_blend_factor(blend_state.src_alpha_factor),
                    gl::from_blend_factor(blend_state.dst_alpha_factor));
                s_check_gl_error();
            }
            if (blend_state.rgb_operation != cache.blend_state_cache.rgb_operation ||
                blend_state.alpha_operation != cache.blend_state_cache.alpha_operation)
            {
                glBlendEquationSeparate(gl::from_blend_operation(blend_state.rgb_operation),
                    gl::from_blend_operation(blend_state.alpha_operation));
                s_check_gl_error();
            }
            if (blend_state.color_mask != cache.blend_state_cache.color_mask)
            {
                glColorMask((blend_state.color_mask & pixel_channel_type::red) != 0,
                    (blend_state.color_mask & pixel_channel_type::green) != 0,
                    (blend_state.color_mask & pixel_channel_type::blue) != 0,
                    (blend_state.color_mask & pixel_channel_type::alpha) != 0);
                s_check_gl_error();
            }
            cache.blend_state_cache = blend_state;
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

    void gl_renderer::apply_depth_stencil_state(const depth_stencil_state &depth_stencil_state)
    {
        if (cache.depth_stencil_state_cache != depth_stencil_state)
        {
            if (cache.depth_stencil_state_cache.value != depth_stencil_state.value)
            {
                if (depth_stencil_state.compare != cache.depth_stencil_state_cache.compare)
                {
                    glDepthFunc(gl::from_compare_func(depth_stencil_state.compare));
                    s_check_gl_error();
                }
                if (depth_stencil_state.is_depth_enable != cache.depth_stencil_state_cache.is_depth_enable)
                {
                    glDepthMask(depth_stencil_state.is_depth_enable);
                    s_check_gl_error();
                }
                if (depth_stencil_state.is_stencil_enable != cache.depth_stencil_state_cache.is_stencil_enable)
                {
                    if (depth_stencil_state.is_stencil_enable)
                    {
                        glEnable(GL_STENCIL_TEST);
                    }
                    else
                    {
                        glDisable(GL_STENCIL_TEST);
                    }
                    s_check_gl_error();
                }
            }
            if (cache.depth_stencil_state_cache.front != depth_stencil_state.front)
            {
                if (depth_stencil_state.front.compare != cache.depth_stencil_state_cache.compare ||
                    depth_stencil_state.stencil_value != cache.depth_stencil_state_cache.stencil_value ||
                    depth_stencil_state.stencil_read_mask != cache.depth_stencil_state_cache.stencil_read_mask)
                {
                    glStencilFuncSeparate(GL_FRONT,
                        gl::from_compare_func(depth_stencil_state.front.compare),
                        depth_stencil_state.stencil_value,
                        depth_stencil_state.stencil_read_mask);
                    s_check_gl_error();
                }
                if (depth_stencil_state.front.compare == cache.depth_stencil_state_cache.compare)
                {
                    glStencilOpSeparate(GL_FRONT,
                        gl::from_stencil_operation(depth_stencil_state.front.fail),
                        gl::from_stencil_operation(depth_stencil_state.front.depth_fail),
                        gl::from_stencil_operation(depth_stencil_state.front.pass));
                    s_check_gl_error();
                }
                if (depth_stencil_state.stencil_write_mask != cache.depth_stencil_state_cache.stencil_write_mask)
                {
                    glStencilMaskSeparate(GL_FRONT, depth_stencil_state.stencil_write_mask);
                    s_check_gl_error();
                }
            }
            if (cache.depth_stencil_state_cache.back != depth_stencil_state.back)
            {
                if (depth_stencil_state.back.compare != cache.depth_stencil_state_cache.compare ||
                    depth_stencil_state.stencil_value != cache.depth_stencil_state_cache.stencil_value ||
                    depth_stencil_state.stencil_read_mask != cache.depth_stencil_state_cache.stencil_read_mask)
                {
                    glStencilFuncSeparate(GL_BACK,
                        gl::from_compare_func(depth_stencil_state.back.compare),
                        depth_stencil_state.stencil_value,
                        depth_stencil_state.stencil_read_mask);
                    s_check_gl_error();
                }
                if (depth_stencil_state.back.compare == cache.depth_stencil_state_cache.compare)
                {
                    glStencilOpSeparate(GL_BACK,
                        gl::from_stencil_operation(depth_stencil_state.back.fail),
                        gl::from_stencil_operation(depth_stencil_state.back.depth_fail),
                        gl::from_stencil_operation(depth_stencil_state.back.pass));
                    s_check_gl_error();
                }
                if (depth_stencil_state.stencil_write_mask != cache.depth_stencil_state_cache.stencil_write_mask)
                {
                    glStencilMaskSeparate(GL_BACK, depth_stencil_state.stencil_write_mask);
                    s_check_gl_error();
                }
            }
            cache.depth_stencil_state_cache = depth_stencil_state;
        }
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

    void gl_renderer::apply_rasterizer_state(const rasterizer_state &rasterizer_state)
    {
        if (cache.rasterizer_state_cache != rasterizer_state)
        {
            auto enable_mask = 0;
            auto disable_mask = 0;
            if (rasterizer_state.is_cull_face_enable)
            {
                enable_mask |= GL_CULL_FACE;
            }
            else
            {
                disable_mask |= GL_CULL_FACE;
            }
            if (rasterizer_state.is_depth_offset_enable)
            {
                enable_mask |= GL_POLYGON_OFFSET_FILL;
            }
            else
            {
                disable_mask |= GL_POLYGON_OFFSET_FILL;
            }
            if (rasterizer_state.is_scissor_test_enable)
            {
                enable_mask |= GL_SCISSOR_TEST;
            }
            else
            {
                disable_mask |= GL_SCISSOR_TEST;
            }
            if (rasterizer_state.is_dither_enable)
            {
                enable_mask |= GL_DITHER;
            }
            else
            {
                disable_mask |= GL_DITHER;
            }
            if (rasterizer_state.is_alpha_to_coverage_enable)
            {
                enable_mask |= GL_SAMPLE_ALPHA_TO_COVERAGE;
            }
            else
            {
                disable_mask |= GL_SAMPLE_ALPHA_TO_COVERAGE;
            }
            if (rasterizer_state.sample > 1)
            {
                enable_mask |= GL_MULTISAMPLE;
            }
            else
            {
                disable_mask |= GL_MULTISAMPLE;
            }

            glDisable(disable_mask);
            s_check_gl_error();

            glEnable(enable_mask);
            s_check_gl_error();

            if (rasterizer_state.cull_face != cache.rasterizer_state_cache.cull_face)
            {
                if (rasterizer_state.is_cull_face_enable)
                {
                    glCullFace(gl::from_face_side(rasterizer_state.cull_face));
                    s_check_gl_error();
                }
            }
            cache.rasterizer_state_cache = rasterizer_state;
        }
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
}
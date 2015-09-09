#pragma once

#include "graphics/renderer/renderer_base.h"

namespace sam
{
    class gl_renderer : public renderer_base
    {
    public:
        virtual ~gl_renderer() {};

        virtual void initialize(const graphics_config& config, const graphics_attribute &attribute) override;

        virtual void finalize() override;

        virtual void apply_target(texture *texture, const clear_state& state) override;

        virtual void apply_view_port(int32 x, int32 y, int32 width, int32 height) override;

        virtual void apply_scissor(int32 x, int32 y, int32 width, int32 height) override;

        virtual void apply_draw_state(draw_state *draw_state) override;

        virtual void draw(int32 index) override;

        virtual void draw(const draw_call_attribute &attribute) override;

        virtual void reset() override;

        virtual void apply_mesh(mesh *mesh)override;

        virtual void reset_mesh()override;

        virtual void apply_shader(shader *shader)override;

        virtual void reset_shader()override;

        virtual void apply_texture(int32 index, texture *texture)override;

        virtual void reset_texture()override;

        virtual void apply_blend_state(const blend_state &blend_state)override;

        virtual void reset_blend_state()override;

        virtual void apply_depth_stencil_state(const depth_stencil_state &depth_stencil_state)override;

        virtual void reset_depth_stencil_state()override;

        virtual void apply_rasterizer_state(const rasterizer_state &rasterizer_state)override;

        virtual void reset_rasterizer_state()override;

        void bind_vertex_buffer(GLuint buffer);

        void bind_index_buffer(GLuint buffer);

        void bind_program(GLuint program);

        void bind_texture(int32 index, GLenum target, GLuint texture);

        #ifdef GLAD_DEBUG
        static void pre_opengl_callback(const char *name, void *funcptr, int len_args, ...);

        static void post_opengl_callback(const char *name, void *funcptr, int len_args, ...);
        #endif

    private:
        gl_cache cache;
    };
}
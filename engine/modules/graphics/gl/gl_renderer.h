#pragma once

#include "graphics/core/blend_state.h"
#include "graphics/core/rasterizer_state.h"
#include "graphics/core/depth_stencil_state.h"
#include "graphics/renderer/renderer_base.h"


namespace sam
{
    class gl_renderer : public renderer_base
    {
    public:
        gl_renderer();

        virtual ~gl_renderer();

        virtual void initialize(const graphics_config& config, const graphics_attribute &attribute) override;

        virtual void finalize() override;

        virtual void apply_target(texture_ptr texture, const clear_state& state) override;

        virtual void apply_view_port(int32 x, int32 y, int32 width, int32 height) override;

        virtual void reset_mesh_state() override;

        virtual void reset_shader_state() override;

        virtual void reset_texture_state() override;

        void bind_vertex_buffer(GLuint buffer);

        void bind_index_buffer(GLuint buffer);

        void use_program(GLuint program);

        void bind_texture(int32 index, GLenum target, GLuint texture);

    private:
        void reset_blend_state();

        void reset_depth_stencil_state();

        void reset_rasterizer_state();

    private:
        blend_state blend_state_cache;
        depth_stencil_state depth_stencil_state_cache;
        rasterizer_state rasterizer_state_cache;
        color blend_color;
    };
}
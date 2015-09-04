#pragma once

#include "graphics/core/clear_state.h"
#include "graphics/config/graphics_config.h"
#include "graphics/attribute/graphics_attribute.h"
#include "graphics/attribute/texture_attribute.h"
#include "graphics/attribute/render_target_attribute.h"
#include "graphics/resource/graphics_resource.h"

#include <window/window.h>

#include <memory>

namespace sam
{
    class renderer_base
    {
    public:
        virtual ~renderer_base() {}

        virtual void initialize(const graphics_config &config, const graphics_attribute &attribute);

        virtual void finalize();

        virtual void render();

        virtual void apply_target(texture *texture, const clear_state &state);

        virtual void apply_view_port(int32 x, int32 y, int32 width, int32 height) = 0;

        virtual void apply_scissor(int32 x, int32 y, int32 width, int32 height) = 0;

        virtual void apply_draw_state(draw_state *draw_state);

        virtual void draw(int32 index) = 0;

        virtual void draw(const draw_call_attribute &attribute) = 0;

        virtual void reset() = 0;

        virtual void apply_mesh(mesh *mesh) = 0;

        virtual void reset_mesh() = 0;

        virtual void apply_shader(shader *shader) = 0;

        virtual void reset_shader() = 0;

        virtual void apply_texture(texture *texture) = 0;

        virtual void reset_texture() = 0;

        virtual void apply_blend_state(const blend_state &blend_state) = 0;

        virtual void reset_blend_state() = 0;

        virtual void apply_depth_stencil_state(const depth_stencil_state &depth_stencil_state) = 0;

        virtual void reset_depth_stencil_state() = 0;

        virtual void apply_rasterizer_state(const rasterizer_state &rasterizer_state) = 0;

        virtual void reset_rasterizer_state() = 0;

        const render_target_attribute &get_target_attribute() const;

    protected:
        texture *target{ nullptr };
        draw_state *state{ nullptr };
        render_target_attribute target_attribute;
        graphics_attribute graphics_attribute_cache;
    };

    inline void renderer_base::initialize(const graphics_config &config, const graphics_attribute &attribute)
    {
        target = nullptr;
        graphics_attribute_cache = attribute;
    }

    inline void renderer_base::finalize()
    {
        target = nullptr;
        graphics_attribute_cache = graphics_attribute();
    }

    inline void renderer_base::render()
    {
        target = nullptr;
    }

    inline void renderer_base::apply_target(texture *texture, const clear_state &state)
    {
        if (texture == nullptr)
        {
            this->target_attribute = render_target_attribute::from_window_config(window::get_config());
        }
        else
        {
            auto &texture_attribute = texture->config.attribute;
            this->target_attribute.width = texture_attribute.width;
            this->target_attribute.height = texture_attribute.height;
            this->target_attribute.position_x = 0;
            this->target_attribute.position_y = 0;
            this->target_attribute.frame_buffer_width = texture_attribute.width;
            this->target_attribute.frame_buffer_height = texture_attribute.height;
            this->target_attribute.color_format = texture_attribute.color_format;
            this->target_attribute.depth_format = texture_attribute.depth_format;
        }
    }

    inline void renderer_base::apply_draw_state(draw_state *draw_state)
    {
        state = draw_state;
    }

    inline const render_target_attribute &renderer_base::get_target_attribute() const
    {
        return target_attribute;
    }
}
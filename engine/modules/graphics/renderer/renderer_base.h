#pragma once

#include "graphics/core/clear_state.h"
#include "graphics/config/graphics_config.h"
#include "graphics/attribute/graphics_attribute.h"
#include "graphics/attribute/texture_attribute.h"
#include "graphics/attribute/render_target_attribute.h"
#include "graphics/resource/texture.h"

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

        virtual void apply_target(texture_ptr texture, const clear_state &state);

        virtual void apply_view_port(int32 x, int32 y, int32 width, int32 height) = 0;

        virtual void apply_scissor(int32 x, int32 y, int32 width, int32 height) = 0;

        virtual void reset_mesh_state() = 0;

        virtual void reset_shader_state() = 0;

        virtual void reset_texture_state() = 0;

        const render_target_attribute &get_target_attribute() const;

    protected:
        texture_ptr target{ nullptr };
        render_target_attribute target_attribute;
        graphics_attribute graphics_attribute_cache;
    };

    inline void renderer_base::initialize(const graphics_config &config, const graphics_attribute &attribute)
    {
        target.reset();
        graphics_attribute_cache = attribute;
    }

    inline void renderer_base::finalize()
    {
        target.reset();
        graphics_attribute_cache = graphics_attribute();
    }

    inline void renderer_base::render()
    {
        target = nullptr;
    }

    inline void renderer_base::apply_target(texture_ptr texture, const clear_state &state)
    {
        if (texture == nullptr)
        {
            this->target_attribute = render_target_attribute::from_window_config(window::get_config());
        }
        else
        {
            auto &texture_attribute = texture->attribute;
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

    inline const render_target_attribute &renderer_base::get_target_attribute() const
    {
        return target_attribute;
    }
}
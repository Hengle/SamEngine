#pragma once

#include "clear_state.h"
#include "texture_base.h"
#include "window_base.h"

#include "graphics/config/graphics_config.h"
#include "graphics/attribute/graphics_attribute.h"
#include "graphics/attribute/texture_attribute.h"

#include <memory>

namespace sam
{
    class renderer_base
    {
    public:
        virtual ~renderer_base() {}

        virtual void initialize(const graphics_config &config, const graphics_attribute &attribute);

        virtual void finalize();

        virtual void present();

        virtual void apply_target(texture_base_ptr texture, const clear_state &state);

        virtual void apply_view_port(int32 x, int32 y, int32 width, int32 height) = 0;

        virtual void reset_mesh_state() = 0;

        virtual void reset_shader_state() = 0;

        virtual void reset_texture_state() = 0;

        const render_target_attribute &get_target_attribute() const;

    protected:
        std::shared_ptr<texture_base> target{nullptr};
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

    inline void renderer_base::present()
    {
        target = nullptr;
    }

    inline void renderer_base::apply_target(texture_base_ptr texture, const clear_state &state)
    {
        if (texture == nullptr)
        {
            this->target_attribute = this->graphics_attribute_cache.window->get_attribute();
        }
        else
        {
            auto &texture_attribute = texture->get_attribute();
            this->target_attribute.width = texture_attribute.width;
            this->target_attribute.height = texture_attribute.height;
            this->target_attribute.position_x = 0;
            this->target_attribute.position_y = 0;
            this->target_attribute.frame_buffer_width = texture_attribute.width;
            this->target_attribute.frame_buffer_height = texture_attribute.height;
            this->target_attribute.color_format = texture_attribute.color_format;
            this->target_attribute.depth_format = texture_attribute.depth_format;
            this->target_attribute.sample_count = 1;
            this->target_attribute.is_fullscreen = true;
            this->target_attribute.swap_interval = 1;
        }
    }

    inline const render_target_attribute &renderer_base::get_target_attribute() const
    {
        return target_attribute;
    }
}
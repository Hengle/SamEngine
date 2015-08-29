#pragma once

#include "graphics/attribute/graphics_attribute.h"
#include "graphics/attribute/render_target_attribute.h"
#include "graphics/config/graphics_config.h"

namespace sam
{
    class window_base
    {
    public:
        virtual ~window_base() {}

        virtual void initialize(const graphics_config &config, const graphics_attribute &attribute);

        virtual void finalize();

        virtual bool available() = 0;

        virtual bool should_close() = 0;

        virtual void handle_event() = 0;

        virtual void present() = 0;

        const render_target_attribute &get_attribute() const;

    protected:
        render_target_attribute render_target_attribute;
        graphics_attribute graphics_attribute_cache;
    };

    inline void window_base::initialize(const graphics_config &config, const graphics_attribute &attribute)
    {
        render_target_attribute = config.get_render_target_attribute();
        graphics_attribute_cache = attribute;
    }

    inline void window_base::finalize()
    {
        graphics_attribute_cache = graphics_attribute();
    }

    inline const render_target_attribute &window_base::get_attribute() const
    {
        return render_target_attribute;
    }
};
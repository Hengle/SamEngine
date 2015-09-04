#pragma once

#include "graphics/resource/graphics_resource.h"
#include "graphics/resource/graphics_resource_factory.h"

namespace sam
{
    class gl_draw_state_factory : public graphics_resource_factory<draw_state>
    {
    public:
        virtual ~gl_draw_state_factory() {};

        virtual resource::status create(draw_state &draw_state, data_ptr data) override;

        virtual void destroy(draw_state &draw_state) override;
    };
}
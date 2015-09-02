#pragma once

#include "graphics/resource/texture.h"
#include "graphics/resource/graphics_resource_factory.h"

namespace sam
{
    class gl_texture_factory : public graphics_resource_factory<texture>
    {
    public:
        virtual resource::status create(gl_texture &texture, data_ptr data) override;

        virtual void destroy(gl_texture &texture) override;
    };
}
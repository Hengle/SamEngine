#pragma once

#include "graphics/resource/shader.h"
#include "graphics/resource/graphics_resource_factory.h"

namespace sam
{
    class gl_shader_factory : public graphics_resource_factory<shader>
    {
    public:
        virtual resource::status create(gl_shader &shader, data_ptr data) override;

        virtual void destroy(gl_shader &shader) override;
    };
}
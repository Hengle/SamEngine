#pragma once

#include "graphics/core/texture_factory_base.h"

namespace sam
{
    class gl_texture_factory : public texture_factory_base
    {
    public:
        gl_texture_factory();

        virtual ~gl_texture_factory();

        virtual resource::status create(texture_base& texture) override;
    };
}
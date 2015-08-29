#pragma once

#include "texture_base.h"

#include "resource/resource.h"

namespace sam
{
    class texture_factory_base
    {
    public:
        virtual ~texture_factory_base() {}

        virtual resource::status create(texture_base &texture) = 0;
    };
}
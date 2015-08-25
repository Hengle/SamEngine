#pragma once

#include "graphics/config/texture_config.h"

#include "resource/resource.h"

namespace sam
{
    class texture_base : public resource_base<texture_config>
    {
    public:
        virtual ~texture_base() {}

        virtual void finalize() override
        {
            resource_base::finalize();
            width = 0;
            height = 0;
        }

        int32 width = 0;

        int32 height = 0;
    };
}
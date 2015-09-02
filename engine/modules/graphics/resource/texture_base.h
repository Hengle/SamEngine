#pragma once

#include "graphics/attribute/texture_attribute.h"
#include "graphics/config/texture_config.h"

#include <resource/resource.h>

namespace sam
{
    class texture_base : public resource_base<texture_config>
    {
    public:
        texture_attribute attribute;

        virtual void finalize() override;
    };

    inline void texture_base::finalize()
    {
        attribute = texture_attribute();
        resource_base::finalize();
    }
}
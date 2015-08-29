#pragma once

#include "graphics/attribute/texture_attribute.h"
#include "graphics/config/texture_config.h"

#include "resource/resource.h"

#include <memory>

namespace sam
{
    class texture_base : public resource_base<texture_config>
    {
    public:
        virtual ~texture_base() {}

        virtual void finalize() override;

        const texture_attribute &get_attribute() const;

    protected:
        texture_attribute attribute;
    };

    inline void texture_base::finalize()
    {
        attribute = texture_attribute();
        resource_base::finalize();
    }

    inline const texture_attribute &texture_base::get_attribute() const
    {
        return attribute;
    }

    typedef std::shared_ptr<texture_base> texture_base_ptr;
}
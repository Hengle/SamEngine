#pragma once

#include "graphics/attribute/graphics_attribute.h"

#include <resource/resource_factory.h>

namespace sam
{
    template <class RESOURCE>
    class graphics_resource_factory : public resource_factory<RESOURCE, graphics_attribute>
    {
    public:
        virtual void initialize(const graphics_attribute &attribute) override;

        virtual void finalize() override;

    protected:
        graphics_attribute attribute;
    };

    template <class RESOURCE>
    inline void graphics_resource_factory<RESOURCE>::initialize(const graphics_attribute &attribute)
    {
        this->attribute = attribute;
    }

    template <class RESOURCE>
    inline void graphics_resource_factory<RESOURCE>::finalize()
    {
        this->attribute = graphics_attribute();
    }
}
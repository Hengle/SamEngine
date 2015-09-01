#pragma once

#include "mesh.h"
#include "graphics/attribute/graphics_attribute.h"

#include <core/data.h>
#include <resource/resource.h>

namespace sam
{
    class mesh_factory_base
    {
    public:
        virtual ~mesh_factory_base() {}

        virtual void initialize(const graphics_attribute &attribute);

        virtual void finalize();

        virtual resource::status create(mesh &mesh) = 0;

        virtual resource::status create(mesh &mesh, data_ptr data) = 0;

        virtual void destroy(mesh &mesh) = 0;

    protected:
        graphics_attribute attribute;
    };

    inline void mesh_factory_base::initialize(const graphics_attribute &attribute)
    {
        this->attribute = attribute;
    }

    inline void mesh_factory_base::finalize()
    {
        this->attribute = graphics_attribute();
    }
}
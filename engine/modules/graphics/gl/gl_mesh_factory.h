#pragma once

#include "graphics/resource/graphics_resource.h"
#include "graphics/resource/graphics_resource_factory.h"

namespace sam
{
    class gl_mesh_factory : public graphics_resource_factory<mesh>
    {
    public:
        virtual resource::status create(mesh &mesh, data_ptr data) override;

        virtual void destroy(mesh &mesh) override;

    private:
        GLuint create_vertex_buffer(const void *buffer, uint32 size, buffer_usage usage);

        GLuint create_index_buffer(const void *buffer, uint32 size, buffer_usage usage);
    };
}
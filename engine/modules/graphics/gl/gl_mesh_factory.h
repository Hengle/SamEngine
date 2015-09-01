#pragma once

#include "gl.h"
#include "graphics/resource/mesh_factory_base.h"

namespace sam
{
    class gl_mesh_factory : public mesh_factory_base
    {
    public:
        gl_mesh_factory();

        virtual ~gl_mesh_factory();

        virtual void initialize(const graphics_attribute &attribute) override;

        void finalize() override;

        virtual resource::status create(mesh &mesh) override;

        virtual resource::status create(mesh &mesh, data_ptr data) override;

        virtual void destroy(mesh &mesh) override;

    protected:
        GLuint create_vertex_buffer(const void *buffer, uint32 size, buffer_usage usage);

        GLuint create_index_buffer(const void *buffer, uint32 size, buffer_usage usage);
    };
}
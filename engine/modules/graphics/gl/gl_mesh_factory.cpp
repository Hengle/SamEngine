#include "gl_mesh_factory.h"
#include "graphics/renderer/renderer.h"

namespace sam
{
    gl_mesh_factory::gl_mesh_factory()
    {
    }

    gl_mesh_factory::~gl_mesh_factory()
    {
    }

    void gl_mesh_factory::initialize(const graphics_attribute &attribute)
    {
        mesh_factory_base::initialize(attribute);
    }

    void gl_mesh_factory::finalize()
    {
        mesh_factory_base::finalize();
    }

    resource::status gl_mesh_factory::create(mesh &mesh)
    {
        s_error("should never reach here");
        return resource::status::invalid;
    }

    resource::status gl_mesh_factory::create(mesh &mesh, data_ptr data)
    {
        s_assert(mesh.config.is_from_data());
        s_assert(data != nullptr && !data->empty());

        auto &config = mesh.config;

        mesh.vertices.count = config.vertex_count;
        mesh.vertices.usage = config.vertex_usage;
        mesh.vertices.layout = config.vertex_layout;

        mesh.indices.count = config.index_count;
        mesh.indices.usage = config.index_usage;
        mesh.indices.type = config.index_type;

        s_assert(config.draw_count < graphics_config::max_draw_count);

        mesh.draw_count = config.draw_count;
        for (auto i = 0; i < mesh.draw_count; ++i)
        {
            mesh.draws[i] = config.draws[i];
        }

        mesh.vertex_buffer[0] = create_vertex_buffer(data->get_buffer(config.vertex_offset), mesh.vertices.size(), mesh.vertices.usage);

        if (config.index_type != index_type::none)
        {
            mesh.index_buffer = create_index_buffer(data->get_buffer(config.index_offset), mesh.indices.size(), mesh.indices.usage);
        }

        return resource::status::completed;
    }

    void gl_mesh_factory::destroy(mesh &mesh)
    {
    }

    GLuint gl_mesh_factory::create_vertex_buffer(const void *buffer, uint32 size, buffer_usage usage)
    {
        s_assert(size > 0 && buffer != nullptr);

        GLuint result;

        attribute.renderer->reset_mesh_state();

        glGenBuffers(1, &result);
        s_check_gl_error();

        s_assert(result != 0);

        attribute.renderer->bind_vertex_buffer(result);

        glBufferData(GL_ARRAY_BUFFER, size, buffer, gl::from_resource_usage(usage));
        s_check_gl_error();

        attribute.renderer->reset_mesh_state();

        return result;
    }

    GLuint gl_mesh_factory::create_index_buffer(const void *buffer, uint32 size, buffer_usage usage)
    {
        s_assert(size > 0 && buffer != nullptr);

        GLuint result;

        attribute.renderer->reset_mesh_state();

        glGenBuffers(1, &result);
        s_check_gl_error();

        s_assert(result != 0);

        attribute.renderer->bind_index_buffer(result);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, buffer, gl::from_resource_usage(usage));
        s_check_gl_error();

        attribute.renderer->reset_mesh_state();

        return result;
    }
}
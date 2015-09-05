#include "mesh_generator.h"
#include "vertex_util.h"

namespace sam
{
    mesh_generator::mesh_generator(uint32 vertex_count, uint32 index_count, index_type type, buffer_usage vertex_usage, buffer_usage index_usage)
    {
        s_assert(type == index_type::none ||
            type == index_type::uint16 && index_count > 0 && index_count <= std::numeric_limits<uint16>::max() ||
            type == index_type::uint32 && index_count > 0 && index_count <= std::numeric_limits<uint32>::max());

        config.vertices.usage = vertex_usage;
        config.vertices.count = vertex_count;
        config.indices.type = type;
        config.indices.usage = index_usage;
        config.indices.count = index_count;
    }

    mesh_generator &mesh_generator::start()
    {
        s_assert(data == nullptr && vertex_ptr == nullptr && index_ptr == nullptr);
        config.vertex_buffer_offset = 0;
        config.index_buffer_offset = config.vertices.size();
        data = data::create(config.vertices.size() + config.indices.size());
        vertex_ptr = data->get_buffer();
        index_ptr = vertex_ptr + config.index_buffer_offset;
        return *this;
    }

    mesh_generator &mesh_generator::finish()
    {
        s_assert(data != nullptr && 
            vertex_ptr == data->get_buffer() + config.vertices.size() && 
            index_ptr == data->get_buffer() + data->get_size());
        return *this;
    }

    mesh_generator &mesh_generator::vertex(uint32 vertex_index, vertex_attribute_type attribute, float32 x)
    {
        vertex_ptr = vertex_util::write(vertex_ptr, config.vertices.layout.format_of(attribute), x);
        s_assert(vertex_ptr <= data->get_buffer() + config.vertices.size());
        return *this;
    }

    mesh_generator &mesh_generator::vertex(uint32 vertex_index, vertex_attribute_type attribute, float32 x, float32 y)
    {
        vertex_ptr = vertex_util::write(vertex_ptr, config.vertices.layout.format_of(attribute), x, y);
        s_assert(vertex_ptr <= data->get_buffer() + config.vertices.size());
        return *this;
    }

    mesh_generator &mesh_generator::vertex(uint32 vertex_index, vertex_attribute_type attribute, float32 x, float32 y, float32 z)
    {
        vertex_ptr = vertex_util::write(vertex_ptr, config.vertices.layout.format_of(attribute), x, y, z);
        s_assert(vertex_ptr <= data->get_buffer() + config.vertices.size());
        return *this;
    }

    mesh_generator &mesh_generator::vertex(uint32 vertex_index, vertex_attribute_type attribute, float32 x, float32 y, float32 z, float32 w)
    {
        vertex_ptr = vertex_util::write(vertex_ptr, config.vertices.layout.format_of(attribute), x, y, z);
        s_assert(vertex_ptr <= data->get_buffer() + config.vertices.size());
        return *this;
    }

    mesh_generator &mesh_generator::index_uint16(uint16 vertex_index)
    {
        s_assert(config.indices.type == index_type::uint16 && vertex_index < config.vertices.count);
        auto pointer = reinterpret_cast<uint16 *>(index_ptr);
        *pointer++ = vertex_index;
        index_ptr = reinterpret_cast<uchar *>(pointer);
        s_assert(index_ptr <= data->get_buffer() + data->get_size());
        return *this;
    }

    mesh_generator &mesh_generator::index_uint32(uint32 vertex_index)
    {
        s_assert(config.indices.type == index_type::uint32 && vertex_index < config.vertices.count);
        auto pointer = reinterpret_cast<uint32 *>(index_ptr);
        *pointer++ = vertex_index;
        index_ptr = reinterpret_cast<uchar *>(pointer);
        s_assert(index_ptr <= data->get_buffer() + data->get_size());
        return *this;
    }

    mesh_generator &mesh_generator::index_triangle16(uint16 vertex_index_1, uint16 vertex_index_2, uint16 vertex_index_3)
    {
        s_assert(config.indices.type == index_type::uint16 &&
            vertex_index_1 < config.vertices.count &&
            vertex_index_2 < config.vertices.count &&
            vertex_index_3 < config.vertices.count);
        auto pointer = reinterpret_cast<uint16 *>(index_ptr);
        *pointer++ = vertex_index_1;
        *pointer++ = vertex_index_2;
        *pointer++ = vertex_index_3;
        index_ptr = reinterpret_cast<uchar *>(pointer);
        s_assert(index_ptr <= data->get_buffer() + data->get_size());
        return *this;
    }

    mesh_generator &mesh_generator::index_triangle32(uint32 vertex_index_1, uint32 vertex_index_2, uint32 vertex_index_3)
    {
        s_assert(config.indices.type == index_type::uint32 &&
            vertex_index_1 < config.vertices.count &&
            vertex_index_2 < config.vertices.count &&
            vertex_index_3 < config.vertices.count);
        auto pointer = reinterpret_cast<uint32 *>(index_ptr);
        *pointer++ = vertex_index_1;
        *pointer++ = vertex_index_2;
        *pointer++ = vertex_index_3;
        index_ptr = reinterpret_cast<uchar *>(pointer);
        s_assert(index_ptr <= data->get_buffer() + data->get_size());
        return *this;
    }

    mesh_generator &mesh_generator::index_quad16(uint32 vertex_index_1, uint32 vertex_index_2, uint32 vertex_index_3, uint32 vertex_index_4)
    {
        s_assert(config.indices.type == index_type::uint16 &&
            vertex_index_1 < config.vertices.count &&
            vertex_index_2 < config.vertices.count &&
            vertex_index_3 < config.vertices.count);
        auto pointer = reinterpret_cast<uint16 *>(index_ptr);
        *pointer++ = vertex_index_1;
        *pointer++ = vertex_index_2;
        *pointer++ = vertex_index_3;
        *pointer++ = vertex_index_2;
        *pointer++ = vertex_index_3;
        *pointer++ = vertex_index_4;
        index_ptr = reinterpret_cast<uchar *>(pointer);
        s_assert(index_ptr <= data->get_buffer() + data->get_size());
        return *this;
    }

    mesh_generator &mesh_generator::index_quad32(uint32 vertex_index_1, uint32 vertex_index_2, uint32 vertex_index_3, uint32 vertex_index_4)
    {
        s_assert(config.indices.type == index_type::uint32 &&
            vertex_index_1 < config.vertices.count &&
            vertex_index_2 < config.vertices.count &&
            vertex_index_3 < config.vertices.count);
        auto pointer = reinterpret_cast<uint32 *>(index_ptr);
        *pointer++ = vertex_index_1;
        *pointer++ = vertex_index_2;
        *pointer++ = vertex_index_3;
        *pointer++ = vertex_index_2;
        *pointer++ = vertex_index_3;
        *pointer++ = vertex_index_4;
        index_ptr = reinterpret_cast<uchar *>(pointer);
        s_assert(index_ptr <= data->get_buffer() + data->get_size());
        return *this;
    }

    mesh_generator &mesh_generator::draw_call(draw_type type, int32 first, int32 count)
    {
        s_assert(config.draw_count < graphics_config::max_draw_count);
        config.draws[config.draw_count].type = type;
        config.draws[config.draw_count].first = first;
        config.draws[config.draw_count].count = count;
        ++config.draw_count;
        return *this;
    }
}
#pragma once

#include <core/types.h>
#include <core/data.h>
#include <graphics/core/define.h>
#include <graphics/config/mesh_config.h>

namespace sam
{
    class mesh_generator
    {
    public:
        explicit mesh_generator(uint32 vertex_count, uint32 index_count = 0, index_type type = index_type::none, buffer_usage vertex_usage = buffer_usage::immutable, buffer_usage index_usage = buffer_usage::immutable);

        vertex_layout &layout();

        mesh_generator &start();

        mesh_generator &finish();

        mesh_generator &vertex(uint32 vertex_index, vertex_attribute_type attribute, float32 x);

        mesh_generator &vertex(uint32 vertex_index, vertex_attribute_type attribute, float32 x, float32 y);

        mesh_generator &vertex(uint32 vertex_index, vertex_attribute_type attribute, float32 x, float32 y, float32 z);

        mesh_generator &vertex(uint32 vertex_index, vertex_attribute_type attribute, float32 x, float32 y, float32 z, float32 w);

        mesh_generator &index_uint16(uint16 vertex_index);

        mesh_generator &index_uint32(uint32 vertex_index);

        mesh_generator &index_triangle16(uint16 vertex_index_1, uint16 vertex_index_2, uint16 vertex_index_3);

        mesh_generator &index_triangle32(uint32 vertex_index_1, uint32 vertex_index_2, uint32 vertex_index_3);

        mesh_generator &index_quad16(uint32 vertex_index_1, uint32 vertex_index_2, uint32 vertex_index_3, uint32 vertex_index_4);

        mesh_generator &index_quad32(uint32 vertex_index_1, uint32 vertex_index_2, uint32 vertex_index_3, uint32 vertex_index_4);

        mesh_generator &draw_call(draw_type type, int32 first, int32 count);

        mesh_config &generate_config();

        data_ptr &generate_data();

        void clear();

    private:
        mesh_config config;
        data_ptr data{ nullptr };
        uchar *vertex_ptr{ nullptr };
        uchar *index_ptr{ nullptr };
    };

    inline vertex_layout &mesh_generator::layout()
    {
        return config.vertices.layout;
    }

    inline mesh_config &mesh_generator::generate_config()
    {
        return config;
    }

    inline data_ptr &mesh_generator::generate_data()
    {
        return data;
    }

    inline void mesh_generator::clear()
    {
        config = mesh_config();
        data->clear();
    }
}
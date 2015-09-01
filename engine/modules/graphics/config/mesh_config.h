#pragma once

#include "graphics/core/define.h"
#include "graphics/core/vertex_layout.h"

namespace sam
{
    class mesh_config
    {
    public:
        static mesh_config with_file(const std::string &location);

        static mesh_config with_data(buffer_usage vertex = buffer_usage::immutable, buffer_usage index = buffer_usage::immutable);

        static mesh_config with_config(const mesh_config &other);

        bool is_from_file() const;

        bool is_from_data() const;

        const std::string &get_location() const;

    public:
        buffer_usage vertex_usage{ buffer_usage::immutable };
        vertex_layout vertex_layout;
        int32 vertex_count{ 0 };
        int32 vertex_offset{ 0 };

        buffer_usage index_usage{ buffer_usage::immutable };
        index_type index_type{ index_type::none };
        int32 index_count{ 0 };
        int32 index_offset{ 0 };

        draw_type draws[graphics_config::max_draw_count];
        int32 draw_count{ 0 };

    private:
        bool from_file{ false };
        bool from_data{ false };
        std::string location;
    };

    inline mesh_config mesh_config::with_file(const std::string &location)
    {
        mesh_config config;
        config.location = location;
        config.from_file = true;
        return config;
    }

    inline mesh_config mesh_config::with_data(buffer_usage vertex, buffer_usage index)
    {
        mesh_config config;
        config.vertex_usage = vertex;
        config.index_usage = index;
        config.from_data = true;
        return config;
    }

    inline mesh_config mesh_config::with_config(const mesh_config &other)
    {
        auto config(other);
        config.from_data = true;
        return config;
    }

    inline bool mesh_config::is_from_file() const
    {
        return from_file;
    }

    inline bool mesh_config::is_from_data() const
    {
        return from_data;
    }

    inline const std::string &mesh_config::get_location() const
    {
        return location;
    }
}
#pragma once

#include "define.h"
#include "graphics/config/graphics_config.h"

#include <core/assert.h>

namespace sam
{
    class vertex_node
    {
    public:
        vertex_node();

        vertex_node(vertex_attribute attribute, vertex_attribute_format format);

        void clear();

        int32 size() const;

        union
        {
            #pragma pack(push, 1)
            struct
            {
                vertex_attribute attribute;
                vertex_attribute_format format;
            };
            #pragma pack(pop)
            uint16 value;
        };
    };

    inline vertex_node::vertex_node() :
        attribute(vertex_attribute::invalid),
        format(vertex_attribute_format::invalid)
    {
    }

    inline vertex_node::vertex_node(vertex_attribute attribute, vertex_attribute_format format) :
        attribute(attribute),
        format(format)
    {
        static_assert(sizeof(vertex_node) == sizeof(uint16), "wrong size of vertex_node");
    }

    inline void vertex_node::clear()
    {
        attribute = vertex_attribute::invalid;
        format = vertex_attribute_format::invalid;
    }

    inline int32 vertex_node::size() const
    {
        return sizeof_attribute_format(format);
    }

    class vertex_layout
    {
    public:
        void clear();

        vertex_layout &add(const vertex_node &node);

        vertex_layout &append(const vertex_layout &layout);

        bool empty() const;

        bool contain(vertex_attribute attribute) const;

        int32 size() const;

    private:
        vertex_node nodes[graphics_config::max_vertex_node];
        uint32 count{ 0 };
    };

    inline void vertex_layout::clear()
    {
        count = 0;
    }

    inline vertex_layout& vertex_layout::add(const vertex_node &node)
    {
        s_assert(count + 1 < graphics_config::max_vertex_node);
        nodes[count++] = node;
        return *this;
    }

    inline vertex_layout& vertex_layout::append(const vertex_layout &layout)
    {
        for (uint32 i = 0; i < layout.count; ++i)
        {
            add(layout.nodes[i]);
        }
        return *this;
    }

    inline bool vertex_layout::empty() const
    {
        return count == 0;
    }

    inline bool vertex_layout::contain(vertex_attribute attribute) const
    {
        for (uint32 i = 0; i < count; ++i)
        {
            if (nodes[i].attribute == attribute)
            {
                return true;
            }
        }
        return false;
    }

    inline int32 vertex_layout::size() const
    {
        auto total = 0;
        for (uint32 i = 0; i < count; ++i)
        {
            total += nodes[i].size();
        }
        return total;
    }
}
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

        vertex_node(vertex_attribute_type attribute, vertex_attribute_format format);

        int32 size() const;

        bool operator !=(const vertex_node &other) const;

        union
        {
            #pragma pack(push, 1)
            struct
            {
                vertex_attribute_type attribute;
                vertex_attribute_format format;
            };
            #pragma pack(pop)
            uint16 value;
        };
    };

    inline vertex_node::vertex_node() :
        attribute(vertex_attribute_type::position),
        format(vertex_attribute_format::float1)
    {
    }

    inline vertex_node::vertex_node(vertex_attribute_type attribute, vertex_attribute_format format) :
        attribute(attribute),
        format(format)
    {
        static_assert(sizeof(vertex_node) == sizeof(uint16), "wrong size of vertex_node");
    }

    inline int32 vertex_node::size() const
    {
        return sizeof_attribute_format(format);
    }

    inline bool vertex_node::operator!=(const vertex_node &other) const
    {
        return value != other.value;
    }

    class vertex_layout
    {
    public:
        vertex_layout &add(vertex_attribute_type attribute, vertex_attribute_format format);

        vertex_layout &add(const vertex_node &node);

        vertex_attribute_format format_of(vertex_attribute_type attribute) const;

        bool empty() const;

        bool contain(vertex_attribute_type attribute) const;

        int32 size() const;

        const vertex_node *begin() const;

        const vertex_node *end() const;

    private:
        vertex_node nodes[graphics_config::max_vertex_node_count];
        int32 count{ 0 };
    };

    inline vertex_layout &vertex_layout::add(vertex_attribute_type attribute, vertex_attribute_format format)
    {
        return add({ attribute, format });
    }

    inline vertex_layout &vertex_layout::add(const vertex_node &node)
    {
        s_assert(count + 1 < graphics_config::max_vertex_node_count);
        s_assert(!contain(node.attribute));
        nodes[count++] = node;
        return *this;
    }

    inline vertex_attribute_format vertex_layout::format_of(vertex_attribute_type attribute) const
    {
        s_assert(contain(attribute));
        for (auto i = 0; i < count; ++i)
        {
            if (nodes[i].attribute == attribute)
            {
                return nodes[i].format;
            }
        }
        return vertex_attribute_format::float1;
    }

    inline bool vertex_layout::empty() const
    {
        return count == 0;
    }

    inline bool vertex_layout::contain(vertex_attribute_type attribute) const
    {
        for (auto i = 0; i < count; ++i)
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
        for (auto i = 0; i < count; ++i)
        {
            total += nodes[i].size();
        }
        return total;
    }

    inline const vertex_node *vertex_layout::begin() const
    {
        return nodes;
    }

    inline const vertex_node *vertex_layout::end() const
    {
        return nodes + count;
    }
}
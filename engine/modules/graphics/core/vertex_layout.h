#pragma once

#include "define.h"

#include <vector>

namespace sam
{
    class vertex_node
    {
    public:
        vertex_node(vertex_attribute attribute, vertex_attribute_format format);

        void clear();

        int32 size() const;

        union
        {
            #pragma pack(push, 1)
            struct
            {
                vertex_attribute attribute{ vertex_attribute::invalid };
                vertex_attribute_format format{ vertex_attribute_format::invalid };
            };
            #pragma pack(pop)
            uint16 value;
        };
    };

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
        std::vector<vertex_node> nodes;
    };

    inline void vertex_layout::clear()
    {
        nodes.clear();
    }

    inline vertex_layout& vertex_layout::add(const vertex_node &node)
    {
        nodes.push_back(node);
        return *this;
    }

    inline vertex_layout& vertex_layout::append(const vertex_layout &layout)
    {
        for (auto &node : layout.nodes)
        {
            nodes.push_back(node);
        }
        return *this;
    }

    inline bool vertex_layout::empty() const
    {
        return nodes.empty();
    }

    inline bool vertex_layout::contain(vertex_attribute attribute) const
    {
        for (auto &node : nodes)
        {
            if (node.attribute == attribute)
            {
                return true;
            }
        }
        return false;
    }

    inline int32 vertex_layout::size() const
    {
        auto total = 0;
        for (auto &node : nodes)
        {
            total += node.size();
        }
        return total;
    }
}
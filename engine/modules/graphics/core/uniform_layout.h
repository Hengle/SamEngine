#pragma once

#include "graphics/core/define.h"
#include "graphics/config/graphics_config.h"

#include <core/assert.h>

#include <string>

namespace sam
{
    class uniform_node
    {
    public:
        std::string name;

        uniform_format type{ uniform_format::invalid };

        void clear();

        int32 size() const;

        bool operator!=(const uniform_node &other) const;
    };

    inline void uniform_node::clear()
    {
        name.clear();
        type = uniform_format::invalid;
    }

    inline int32 uniform_node::size() const
    {
        return sizeof_uniform_format(type);
    }

    inline bool uniform_node::operator!=(const uniform_node &other) const
    {
        return type != other.type || name != other.name;
    }

    class uniform_layout
    {
    public:
        void clear();

        uniform_layout &add(const uniform_node &node);

        bool empty() const;

        bool contain(const std::string &name) const;

        int32 size() const;

        const uniform_node *begin() const;

        const uniform_node *end() const;

    private:
        int32 count{ 0 };
        uniform_node nodes[graphics_config::max_uniform_node_count];
    };

    inline void uniform_layout::clear()
    {
        count = 0;
    }

    inline uniform_layout &uniform_layout::add(const uniform_node &node)
    {
        s_assert(count + 1 < graphics_config::max_uniform_node_count);
        s_assert(!contain(node.name));
        nodes[count++] = node;
        return *this;
    }

    inline bool uniform_layout::empty() const
    {
        return count == 0;
    }

    inline bool uniform_layout::contain(const std::string &name) const
    {
        for (auto i = 0; i < count; ++i)
        {
            if (nodes[i].name == name)
            {
                return true;
            }
        }
        return false;
    }

    inline int32 uniform_layout::size() const
    {
        auto size = 0;
        for (auto i = 0; i < count; ++i)
        {
            size += nodes[i].size();
        }
        return size;
    }

    inline const uniform_node *uniform_layout::begin() const
    {
        return nodes;
    }

    inline const uniform_node *uniform_layout::end() const
    {
        return nodes + count;
    }
}
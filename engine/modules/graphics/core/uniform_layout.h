#pragma once

#include "graphics/core/define.h"
#include "graphics/config/graphics_config.h"

#include <core/data.h>
#include <core/assert.h>

#include <string>

namespace sam
{
    class uniform_node
    {
    public:
        uniform_node();

        uniform_node(const std::string &name, uniform_format type);

        int32 size() const;

        bool operator!=(const uniform_node &other) const;

        const std::string &get_name() const;

        uniform_format get_type() const;

        void set_type(uniform_format type);

        template <typename TYPE>
        void set_data(const TYPE &value);

        const void *get_data() const;

        bool is_valid() const;

        void invalid();

    private:
        std::string name;
        bool need_update{ false };
        data_ptr data{ data::create() };
        uniform_format type{ uniform_format::int1 };
    };

    inline uniform_node::uniform_node()
    {
    }

    inline uniform_node::uniform_node(const std::string &name, uniform_format type) :
        name(name),
        type(type)
    {
        data = data::create(sizeof_uniform_format(type));
    }

    inline int32 uniform_node::size() const
    {
        return sizeof_uniform_format(type);
    }

    inline bool uniform_node::operator!=(const uniform_node &other) const
    {
        return type != other.type || name != other.name;
    }

    inline const std::string &uniform_node::get_name() const
    {
        return name;
    }

    inline uniform_format uniform_node::get_type() const
    {
        return type;
    }

    inline void uniform_node::set_type(uniform_format type)
    {
        this->type = type;
        data->set_size(sizeof_uniform_format(type));
    }

    template <typename TYPE>
    void uniform_node::set_data(const TYPE &value)
    {
        s_assert(sizeof(TYPE) == data->get_size());
        std::memcpy(data->get_buffer(), &value, data->get_size());
        need_update = true;
    }

    inline const void *uniform_node::get_data() const
    {
        return data->get_buffer();
    }

    inline bool uniform_node::is_valid() const
    {
        return need_update;
    }

    inline void uniform_node::invalid()
    {
        need_update = false;
    }

    class uniform_layout
    {
    public:
        uniform_layout &add(const std::string &name, uniform_format type);

        uniform_layout &add(const uniform_node &node);

        template <typename TYPE>
        uniform_layout &set_data(int32 index, const TYPE &value);

        uniform_node &at(int32 index);

        bool empty() const;

        bool contain(const std::string &name) const;

        int32 size() const;

        int32 length() const;

    private:
        int32 count{ 0 };
        uniform_node nodes[graphics_config::max_uniform_node_count];
    };

    inline uniform_layout &uniform_layout::add(const std::string &name, uniform_format type)
    {
        return add({ name, type });
    }

    inline uniform_layout &uniform_layout::add(const uniform_node &node)
    {
        s_assert(count + 1 < graphics_config::max_uniform_node_count);
        s_assert(!contain(node.get_name()));
        nodes[count++] = node;
        return *this;
    }

    template <typename TYPE>
    uniform_layout &uniform_layout::set_data(int32 index, const TYPE &value)
    {
        s_assert_range(index, 0, count - 1);
        nodes[index].set_data(value);
        return *this;
    }

    inline uniform_node &uniform_layout::at(int32 index)
    {
        s_assert_range(index, 0, count - 1);
        return nodes[index];
    }

    inline bool uniform_layout::empty() const
    {
        return count == 0;
    }

    inline bool uniform_layout::contain(const std::string &name) const
    {
        for (auto i = 0; i < count; ++i)
        {
            if (nodes[i].get_name() == name)
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

    inline int32 uniform_layout::length() const
    {
        return count;
    }
}
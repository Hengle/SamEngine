#include "resource_registry.h"

#include <core/assert.h>

namespace sam
{
    resource_registry::~resource_registry()
    {
        finalize();
    }

    void resource_registry::initialize(int32 size)
    {
        s_assert(registry.empty());
        registry.resize(size);
    }

    void resource_registry::finalize()
    {
        registry.clear();
        id2index.clear();
        name2index.clear();
    }

    void resource_registry::add(const resource_name &name, resource::id id, resource::label label)
    {
        registry.push_back({ name, id, label });
        id2index.insert({ id, registry.size() - 1 });
        if (!name.is_unique())
        {
            name2index.insert({ name, registry.size() - 1 });
        }
    }

    std::vector<resource::id> resource_registry::remove(resource::label label)
    {
        std::vector<resource::id> removed;
        auto node = registry.begin();
        while (node != registry.end())
        {
            if (node->label == label)
            {
                removed.push_back(node->id);
                if (!node->name.is_unique())
                {
                    name2index.erase(node->name);
                }
                id2index.erase(node->id);
                registry.erase(node++);
            }
            else
            {
                ++node;
            }
        }
        return removed;
    }

    resource::id resource_registry::find(const resource_name &name) const
    {
        resource::id id = resource::invalid_id;
        if (!name.is_unique())
        {
            auto i = name2index.find(name);
            if (i == name2index.end()) return resource::invalid_id;
            auto index = i->second;
            id = registry[index].id;
        }
        return id;
    }

    bool resource_registry::contains(resource::id id) const
    {
        return id2index.find(id) != id2index.end();
    }

    const resource_name &resource_registry::get_name(resource::id id) const
    {
        auto i = id2index.find(id);
        s_assert(i != id2index.end());
        auto index = i->second;
        return registry[index].name;
    }

    resource::label resource_registry::get_label(resource::id id) const
    {
        auto i = id2index.find(id);
        s_assert(i != id2index.end());
        auto index = i->second;
        return registry[index].label;
    }

    int32 resource_registry::size() const
    {
        return registry.size();
    }

    resource::id resource_registry::operator[](int32 index) const
    {
        return registry[index].id;
    }
}
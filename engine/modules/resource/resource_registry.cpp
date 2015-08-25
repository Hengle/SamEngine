#include "resource_registry.h"

#include "core/assert.h"

namespace sam
{
    resource_registry::resource_registry()
    {
    }

    resource_registry::~resource_registry()
    {
        finalize();
    }

    void resource_registry::initialize(int32 size)
    {
        s_assert(registry.empty());
        registry.reserve(size);
    }

    void resource_registry::finalize()
    {
        registry.clear();
        id2index.clear();
        location2index.clear();
    }

    void resource_registry::add(const std::string &location, resource::id id, resource::label label)
    {
        registry.push_back({ location, id, label });
        id2index.insert(std::make_pair(id, registry.size() - 1));
        location2index.insert(std::make_pair(location, registry.size() - 1));
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
                location2index.erase(node->location);
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

    resource::id resource_registry::find(const std::string &location) const
    {
        auto i = location2index.find(location);
        if (i == location2index.end()) return resource::invalid_id;
        auto index = i->second;
        return registry[index].id;
    }

    bool resource_registry::contains(resource::id id) const
    {
        return id2index.find(id) != id2index.end();
    }

    const std::string &resource_registry::get_location(resource::id id) const
    {
        auto i = id2index.find(id);
        s_assert(i != id2index.end());
        auto index = i->second;
        return registry[index].location;
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
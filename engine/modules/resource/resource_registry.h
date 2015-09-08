#pragma once

#include "resource.h"
#include "resource_name.h"

#include <unordered_map>
#include <vector>

namespace sam
{
    class resource_registry
    {
    public:
        resource_registry();

        virtual ~resource_registry();

        void initialize(int32 size);

        void finalize();

        void add(const resource_name &name, resource::id id, resource::label label);

        std::vector<resource::id> remove(resource::label label);

        resource::id find(const resource_name &name) const;

        bool contains(resource::id id) const;

        const resource_name &get_name(resource::id id) const;

        resource::label get_label(resource::id id) const;

        int32 size() const;

        resource::id operator[](int32 index) const;

    protected:
        class node
        {
        public:
            resource_name name;
            resource::id id;
            resource::label label;
        };

        std::vector<node> registry;
        std::unordered_map<resource::id, int32> id2index;
        std::unordered_map<resource_name, int32> name2index;
    };
}
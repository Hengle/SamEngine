#pragma once

#include "resource.h"

#include <map>
#include <string>
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

        void add(const std::string &location, resource::id id, resource::label label);

        std::vector<resource::id> remove(resource::label label);

        resource::id find(const std::string &location) const;

        bool contains(resource::id id) const;

        const std::string &get_location(resource::id id) const;

        resource::label get_label(resource::id id) const;

        int32 size() const;

        resource::id operator[](int32 index) const;

    protected:
        class node
        {
        public:
            std::string location;
            resource::id id;
            resource::label label;
        };

        std::vector<node> registry;
        std::map<resource::id, int32> id2index;
        std::map<std::string, int32> location2index;
    };
}
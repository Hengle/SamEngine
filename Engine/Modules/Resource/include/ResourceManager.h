#pragma once

#include "Resource.h"
#include "ResourceName.h"

#include <unordered_map>
#include <vector>

namespace SamEngine
{
    class RESOURCE_API ResourceManager
    {
    public:
        void Add(const ResourceName &name, ResourceID id);

        void Remove(ResourceID id);

        void RemoveAll();

        ResourceID Find(const ResourceName &name) const;

        bool Contains(ResourceID id) const;

        const ResourceName &GetName(ResourceID id) const;

        int32 Size() const;

    protected:
        struct node
        {
            ResourceName Name;
            ResourceID ID;
        };

        std::vector<node> mRegistry;
        std::unordered_map<ResourceID, int32> mID2Index;
        std::unordered_map<ResourceName, int32> mName2Index;
    };
}
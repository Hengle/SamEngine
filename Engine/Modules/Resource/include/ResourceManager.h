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

        int32 Size() const;

    protected:
        std::vector<ResourceID> mResourceIDCache;
        std::unordered_map<ResourceName, ResourceID> mName2ID;
        std::unordered_map<ResourceID, ResourceName> mID2Name;
    };
}
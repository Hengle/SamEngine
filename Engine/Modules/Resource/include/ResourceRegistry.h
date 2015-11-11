#pragma once

#include "Resource.h"
#include "ResourceName.h"

#include <unordered_map>
#include <vector>

namespace SamEngine
{
    class RESOURCE_API ResourceRegistry
    {
    public:
        virtual ~ResourceRegistry();

        void Initialize(int32 size);

        void Finalize();

        void Add(const ResourceName &name, ResourceID id, ResourceLabel label);

        std::vector<ResourceID> Remove(ResourceLabel label);

        void Remove(ResourceID id);

        ResourceID Find(const ResourceName &name) const;

        bool Contains(ResourceID id) const;

        const ResourceName &GetName(ResourceID id) const;

        ResourceLabel GetLabel(ResourceID id) const;

        int32 Size() const;

        ResourceID operator[](int32 index) const;

    protected:
        struct node
        {
            ResourceName Name;
            ResourceID ID;
            ResourceLabel Label;
        };

        std::vector<node> mRegistry;
        std::unordered_map<ResourceID, int32> mID2Index;
        std::unordered_map<ResourceName, int32> mName2Index;
    };
}
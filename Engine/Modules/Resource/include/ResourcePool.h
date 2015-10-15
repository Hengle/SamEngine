#pragma once

#include "Resource.h"

#include <queue>
#include <vector>

namespace SamEngine
{
    template <class RESOURCE, class CONFIG>
    class ResourcePool
    {
    public:
        virtual ~ResourcePool();

        void Initialize(uint16 size, ResourcePoolID id);

        void Finalize();

        ResourceID Create();

        void Destroy(ResourceID id);

        RESOURCE &Get(ResourceID id, const CONFIG &config);

        RESOURCE *Find(ResourceID id);

    protected:
        ResourceUniqueID mNextUniqueID{ 0 };
        ResourcePoolID mPoolID{ InvalidResourcePoolID };
        std::vector<RESOURCE> mSlots;
        std::queue<uint16> mAvailableSlots;
    };

    template <class RESOURCE, class CONFIG>
    ResourcePool<RESOURCE, CONFIG>::~ResourcePool()
    {
        s_assert(mPoolID == InvalidResourcePoolID);
    }

    template <class RESOURCE, class CONFIG>
    void ResourcePool<RESOURCE, CONFIG>::Initialize(uint16 size, ResourcePoolID poolID)
    {
        s_assert(mPoolID == InvalidResourcePoolID);
        mPoolID = poolID;
        mSlots.resize(size);
        for (auto i = 0; i < size; ++i)
        {
            mAvailableSlots.push(i);
        }
    }

    template <class RESOURCE, class CONFIG>
    void ResourcePool<RESOURCE, CONFIG>::Finalize()
    {
        s_assert(mPoolID != InvalidResourcePoolID);
        mPoolID = InvalidResourcePoolID;
        mSlots.clear();
        while (!mAvailableSlots.empty())
        {
            mAvailableSlots.pop();
        }
    }

    template <class RESOURCE, class CONFIG>
    ResourceID ResourcePool<RESOURCE, CONFIG>::Create()
    {
        s_assert(mPoolID != InvalidResourcePoolID);
        auto slotID = mAvailableSlots.front();
        mAvailableSlots.pop();
        return GenerateResourceID(mNextUniqueID++, slotID, mPoolID);
    }

    template <class RESOURCE, class CONFIG>
    void ResourcePool<RESOURCE, CONFIG>::Destroy(ResourceID id)
    {
        s_assert(mPoolID != InvalidResourcePoolID);
        auto &slot = mSlots[GetSlotIDOfResourceID(id)];
        s_assert(slot.ID == id);
        s_assert(slot.Status != ResourceStatus::INVALID);
        slot.Finalize();
        mAvailableSlots.push(GetSlotIDOfResourceID(id));
    }

    template <class RESOURCE, class CONFIG>
    RESOURCE &ResourcePool<RESOURCE, CONFIG>::Get(ResourceID id, const CONFIG &config)
    {
        s_assert(mPoolID != InvalidResourcePoolID);
        auto &slot = mSlots[GetSlotIDOfResourceID(id)];
        s_assert(slot.Status == ResourceStatus::INVALID);
        slot.Initialize(id, config);
        return slot;
    }

    template <class RESOURCE, class CONFIG>
    RESOURCE *ResourcePool<RESOURCE, CONFIG>::Find(ResourceID id)
    {
        s_assert(mPoolID != InvalidResourcePoolID);
        RESOURCE *resource = nullptr;
        if (GetResourcePoolIDOfResourceID(id) == mPoolID)
        {
            auto &slot = mSlots[GetSlotIDOfResourceID(id)];
            resource = slot.Status == ResourceStatus::INVALID ? nullptr : &slot;
        }
        return resource;
    }
}
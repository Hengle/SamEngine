#pragma once

#include <CoreModule.h>

namespace SamEngine
{
    typedef uint64 ResourceID;

    typedef uint16 ResourcePoolID;

    typedef uint16 ResourceSlotID;

    typedef uint32 ResourceUniqueID;

    typedef uint32 ResourceLabel;

    enum : ResourceID
    {
        InvalidResourceID = 0xffffffffffffffff,
    };

    enum : ResourcePoolID
    {
        InvalidResourcePoolID = 0xffff,
        ResourcePoolIDMask = 0xffff,
        ResourcePoolIDOffset = 32,
    };

    enum : ResourceSlotID
    {
        InvalidResourceSlotID = 0xffff,
        ResourceSlotIDMask = 0xffff,
        ResourceSlotIDOffset = 16,
    };

    enum : ResourceUniqueID
    {
        InvalidResourceUniqueID = 0xffffffff,
        ResourceUniqueIDMask = 0xffffffff,
        ResourceUniqueIDOffset = 0,
    };

    enum : ResourceLabel
    {
        InvalidResourceLabel = 0xffffffff,
        DefaultResourceLabel = 0x7fffffff,
    };

    enum class ResourceStatus : uint8
    {
        INVALID,
        PENDING,
        LOADING,
        COMPLETED,
        FAILED,
    };

    inline ResourceID GenerateResourceID(ResourceUniqueID uniqueID, ResourceSlotID slotID, ResourcePoolID poolID)
    {
        return (static_cast<ResourceID>(poolID) & ResourcePoolIDMask) << ResourcePoolIDOffset
            | (static_cast<ResourceID>(slotID) & ResourceSlotIDMask) << ResourceSlotIDOffset
            | (static_cast<ResourceID>(uniqueID) & ResourceUniqueIDMask) << ResourceUniqueIDOffset;
    }

    inline ResourcePoolID GetResourcePoolIDOfResourceID(ResourceID rid)
    {
        return rid >> ResourcePoolIDOffset & ResourcePoolIDMask;
    }

    inline ResourceSlotID GetSlotIDOfResourceID(ResourceID rid)
    {
        return rid >> ResourceSlotIDOffset & ResourceSlotIDMask;
    }

    inline ResourceUniqueID GetUniqueIDOfResourceID(ResourceID rid)
    {
        return rid >> ResourceUniqueIDOffset & ResourceUniqueIDMask;
    }

    template <class CONFIG>
    class Resource
    {
    public:
        virtual ~Resource() {}

        void Initialize(ResourceID id, const CONFIG &config);

        virtual void Finalize();

        ResourceID ID{ InvalidResourceID};

        ResourceStatus Status{ ResourceStatus::INVALID };

        CONFIG Config;
    };

    template <class CONFIG>
    void Resource<CONFIG>::Initialize(ResourceID id, const CONFIG &config)
    {
        ID = id;
        Status = ResourceStatus::PENDING;
        Config = config;
    }

    template <class CONFIG>
    inline void Resource<CONFIG>::Finalize()
    {
        ID = InvalidResourceID;
        Status = ResourceStatus::INVALID;
        Config = CONFIG();
    }
}
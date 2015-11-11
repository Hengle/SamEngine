#include "ResourceRegistry.h"

namespace SamEngine
{
    ResourceRegistry::~ResourceRegistry()
    {
        Finalize();
    }

    void ResourceRegistry::Initialize(int32 size)
    {
        s_assert(mRegistry.empty());
    }

    void ResourceRegistry::Finalize()
    {
        mRegistry.clear();
        mID2Index.clear();
        mName2Index.clear();
    }

    void ResourceRegistry::Add(const ResourceName &name, ResourceID id, ResourceLabel label)
    {
        mRegistry.push_back({ name, id, label });
        mID2Index.insert({ id, mRegistry.size() - 1 });
        if (!name.IsUnique())
        {
            mName2Index.insert({ name, mRegistry.size() - 1 });
        }
    }

    std::vector<ResourceID> ResourceRegistry::Remove(ResourceLabel label)
    {
        std::vector<ResourceID> removed;
        auto node = mRegistry.begin();
        while (node != mRegistry.end())
        {
            if (node->Label == label)
            {
                removed.push_back(node->ID);
                if (!node->Name.IsUnique())
                {
                    mName2Index.erase(node->Name);
                }
                mID2Index.erase(node->ID);
                node = mRegistry.erase(node);
            }
            else
            {
                ++node;
            }
        }
        return removed;
    }

    void ResourceRegistry::Remove(ResourceID id)
    {
        auto node = mRegistry.begin();
        while (node != mRegistry.end())
        {
            if (node->ID == id)
            {
                if (!node->Name.IsUnique())
                {
                    mName2Index.erase(node->Name);
                }
                mID2Index.erase(node->ID);
                node = mRegistry.erase(node);
            }
            else
            {
                ++node;
            }
        }
    }

    ResourceID ResourceRegistry::Find(const ResourceName &name) const
    {
        ResourceID id = InvalidResourceID;
        if (!name.IsUnique())
        {
            auto i = mName2Index.find(name);
            if (i == mName2Index.end()) return InvalidResourceID;
            auto index = i->second;
            id = mRegistry[index].ID;
        }
        return id;
    }

    bool ResourceRegistry::Contains(ResourceID id) const
    {
        return mID2Index.find(id) != mID2Index.end();
    }

    const ResourceName &ResourceRegistry::GetName(ResourceID id) const
    {
        auto i = mID2Index.find(id);
        s_assert(i != mID2Index.end());
        auto index = i->second;
        return mRegistry[index].Name;
    }

    ResourceLabel ResourceRegistry::GetLabel(ResourceID id) const
    {
        auto i = mID2Index.find(id);
        s_assert(i != mID2Index.end());
        auto index = i->second;
        return mRegistry[index].Label;
    }

    int32 ResourceRegistry::Size() const
    {
        return mRegistry.size();
    }

    ResourceID ResourceRegistry::operator[](int32 index) const
    {
        return mRegistry[index].ID;
    }
}
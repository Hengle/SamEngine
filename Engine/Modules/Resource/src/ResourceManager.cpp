#include "ResourceManager.h"

namespace SamEngine
{
    void ResourceManager::Add(const ResourceName &name, ResourceID id)
    {
        mRegistry.push_back({ name, id });
        mID2Index.insert({ id, mRegistry.size() - 1 });
        if (!name.IsUnique())
        {
            mName2Index.insert({ name, mRegistry.size() - 1 });
        }
    }

    void ResourceManager::Remove(ResourceID id)
    {
        auto i = mID2Index.find(id);
        if (i != mID2Index.end())
        {
            auto node = mRegistry[i->second];
            if (!node.Name.IsUnique())
            {
                mName2Index.erase(node.Name);
            }
            mID2Index.erase(node.ID);
            mRegistry.erase(mRegistry.begin() + i->second);
        }
    }

    void ResourceManager::RemoveAll()
    {
        mRegistry.clear();
        mID2Index.clear();
        mName2Index.clear();
    }

    ResourceID ResourceManager::Find(const ResourceName &name) const
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

    bool ResourceManager::Contains(ResourceID id) const
    {
        return mID2Index.find(id) != mID2Index.end();
    }

    const ResourceName &ResourceManager::GetName(ResourceID id) const
    {
        auto i = mID2Index.find(id);
        s_assert(i != mID2Index.end());
        auto index = i->second;
        return mRegistry[index].Name;
    }

    int32 ResourceManager::Size() const
    {
        return mRegistry.size();
    }
}
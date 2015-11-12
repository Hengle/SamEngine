#include "ResourceManager.h"

namespace SamEngine
{
    void ResourceManager::Add(const ResourceName &name, ResourceID id)
    {
        mResourceIDCache.push_back(id);
        if (!name.IsUnique())
        {
            mName2ID.insert({ name, id });
            mID2Name.insert({ id, name });
        }
    }

    void ResourceManager::Remove(ResourceID id)
    {
        auto cache = std::find(mResourceIDCache.begin(), mResourceIDCache.end(), id);
        if (cache != mResourceIDCache.end())
        {
            mResourceIDCache.erase(cache);
            auto node = mID2Name.find(id);
            if (node != mID2Name.end())
            {
                mName2ID.erase(node->second);
                mID2Name.erase(id);
            }
        }
    }

    void ResourceManager::RemoveAll()
    {
        mResourceIDCache.clear();
        mName2ID.clear();
    }

    ResourceID ResourceManager::Find(const ResourceName &name) const
    {
        ResourceID id = InvalidResourceID;
        if (!name.IsUnique())
        {
            auto node = mName2ID.find(name);
            if (node != mName2ID.end())
            {
                id = node->second;
            }
        }
        return id;
    }

    bool ResourceManager::Contains(ResourceID id) const
    {
        return std::find(mResourceIDCache.begin(), mResourceIDCache.end(), id) != mResourceIDCache.end();
    }

    int32 ResourceManager::Size() const
    {
        return mName2ID.size();
    }
}
#include "ResourceManager.h"

namespace SamEngine
{
    void ResourceManager::Initialize(uint32 size)
    {
        s_assert(mLabelStack.empty());
        mRegistry.Initialize(size);
        mLabelStack.push(DefaultResourceLabel);
    }

    void ResourceManager::Finalize()
    {
        s_assert(mLabelStack.size() == 1);
        while (!mLabelStack.empty())
        {
            mLabelStack.pop();
        }
        mRegistry.Finalize();
    }

    ResourceLabel ResourceManager::PushLabel()
    {
        mLabelStack.push(mCurrentLabel++);
        return mLabelStack.top();
    }

    void ResourceManager::PushLabel(ResourceLabel label)
    {
        mLabelStack.push(label);
    }

    ResourceLabel ResourceManager::PopLabel()
    {
        auto label = mLabelStack.top();
        mLabelStack.pop();
        return label;
    }

    ResourceID ResourceManager::Find(const ResourceName &name) const
    {
        return mRegistry.Find(name);
    }
}
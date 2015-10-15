#pragma once

#include "Resource.h"
#include "ResourceRegistry.h"

#include <stack>

namespace SamEngine
{
    class RESOURCE_API ResourceManager
    {
    public:
        virtual ~ResourceManager() {}

        void Initialize(uint32 size);

        virtual void Finalize();

        ResourceLabel PushLabel();

        void PushLabel(ResourceLabel label);

        ResourceLabel PopLabel();

        ResourceID Find(const ResourceName &name) const;

    protected:
        ResourceLabel mCurrentLabel{ 0 };
        std::stack<ResourceLabel> mLabelStack;
        ResourceRegistry mRegistry;
    };
}
#pragma once

#include "Resource.h"

namespace SamEngine
{
    template <class RESOURCE>
    class ResourceFactory
    {
    public:
        virtual ~ResourceFactory() {}

        virtual ResourceStatus Create(RESOURCE &resource, DataPtr data) = 0;

        virtual void Destroy(RESOURCE &resource) = 0;
    };
}
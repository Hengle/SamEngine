#pragma once

#include "resource.h"

#include <core/data.h>

namespace sam
{
    template <class RESOURCE, class ATTRIBUTE>
    class resource_factory
    {
    public:
        virtual ~resource_factory() {}

        virtual void initialize(const ATTRIBUTE &attribute) = 0;

        virtual void finalize() = 0;

        virtual resource::status create(RESOURCE &resource, data_ptr data) = 0;

        virtual void destroy(RESOURCE &resource) = 0;
    };
}
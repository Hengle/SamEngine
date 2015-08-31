#pragma once

#include "resource.h"
#include "resource_registry.h"

#include <stack>

namespace sam
{
    class resource_manager
    {
    public:
        resource_manager();

        virtual ~resource_manager();

        void initialize(uint32 size);

        virtual void finalize();

        resource::label push_label();

        void push_label(resource::label label);

        resource::label pop_label();

        resource::id find(const std::string &location) const;

    protected:
        resource::label current_label{ 0 };
        std::stack<resource::label> label_stack;
        resource_registry registry;
    };
}
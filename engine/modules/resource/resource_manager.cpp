#include "resource_manager.h"

namespace sam
{
    resource_manager::resource_manager()
    {
    }

    resource_manager::~resource_manager()
    {
    }

    void resource_manager::initialize(uint32 size)
    {
        registry.initialize(size);
    }

    void resource_manager::finalize()
    {
        while (!label_stack.empty())
        {
            label_stack.pop();
        }
        registry.finalize();
    }

    resource::label resource_manager::push_label()
    {
        label_stack.push(current_label++);
        return label_stack.top();
    }

    void resource_manager::push_label(resource::label label)
    {
        label_stack.push(label);
    }

    resource::label resource_manager::pop_label()
    {
        auto label = label_stack.top();
        label_stack.pop();
        return label;
    }

    resource::id resource_manager::find(const resource_name &name) const
    {
        return registry.find(name);
    }
}
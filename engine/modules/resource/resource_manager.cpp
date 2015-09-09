#include "resource_manager.h"

namespace sam
{
    void resource_manager::initialize(uint32 size)
    {
        s_assert(label_stack.empty());
        registry.initialize(size);
        label_stack.push(resource::default_label);
    }

    void resource_manager::finalize()
    {
        s_assert(label_stack.size() == 1);
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
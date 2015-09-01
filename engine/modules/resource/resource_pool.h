#pragma once

#include "resource.h"

#include <core/assert.h>
#include <core/types.h>

#include <queue>
#include <vector>

namespace sam
{
    template <class RESOURCE, class CONFIG>
    class resource_pool
    {
    public:
        resource_pool();

        virtual ~resource_pool();

        void initialize(uint16 size, resource::pool_id id);

        void finalize();

        resource::id create();

        void destory(resource::id id);

        RESOURCE &get_resource(resource::id id, const CONFIG &config);

    protected:
        resource::unique_id unique_id = 0;
        resource::pool_id pool_id = resource::invalid_pool_id;
        std::vector<RESOURCE> slots;
        std::queue<uint16> available_slots;
    };

    template <class RESOURCE, class CONFIG>
    resource_pool<RESOURCE, CONFIG>::resource_pool()
    {
    }

    template <class RESOURCE, class CONFIG>
    resource_pool<RESOURCE, CONFIG>::~resource_pool()
    {
        s_assert(this->pool_id == resource::invalid_pool_id);
    }

    template <class RESOURCE, class CONFIG>
    void resource_pool<RESOURCE, CONFIG>::initialize(uint16 size, resource::pool_id pool_id)
    {
        s_assert(this->pool_id == resource::invalid_pool_id);
        this->pool_id = pool_id;
        slots.reserve(size);
        for (auto i = 0; i < size; ++i)
        {
            available_slots.push(i);
        }
    }

    template <class RESOURCE, class CONFIG>
    void resource_pool<RESOURCE, CONFIG>::finalize()
    {
        s_assert(pool_id != resource::invalid_pool_id);
        pool_id = resource::invalid_pool_id;
        slots.clear();
        while (!available_slots.empty())
        {
            available_slots.pop();
        }
    }

    template <class RESOURCE, class CONFIG>
    resource::id resource_pool<RESOURCE, CONFIG>::create()
    {
        s_assert(pool_id != resource::invalid_pool_id);
        auto slot_id = available_slots.front();
        available_slots.pop();
        return resource::generate_id(unique_id++, slot_id, pool_id);
    }

    template <class RESOURCE, class CONFIG>
    void resource_pool<RESOURCE, CONFIG>::destory(resource::id id)
    {
        s_assert(pool_id != resource::invalid_pool_id);
        auto &slot = slots[resource::get_slot_id(id)];
        s_assert(slot.id == id);
        slot.finalize();
        available_slots.push(resource::get_slot_id(id));
    }

    template <class RESOURCE, class CONFIG>
    RESOURCE &resource_pool<RESOURCE, CONFIG>::get_resource(resource::id id, const CONFIG &config)
    {
        s_assert(pool_id != resource::invalid_pool_id);
        auto &slot = slots[resource::get_slot_id(id)];
        s_assert(slot.status == resource::status::invalid);
        slot.initialize(id, config);
        return slot;
    }
}
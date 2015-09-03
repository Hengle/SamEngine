#pragma once

#include <core/types.h>

namespace sam
{
    class resource
    {
    public:
        enum class status
        {
            invalid,
            pending,
            loading,
            completed,
            failed,
        };

        typedef int32 label;

        static const label invalid_label = 0xffffffff;

        static const label default_label = 0x7fffffff;

        typedef uint64 id;

        typedef uint16 pool_id;

        typedef uint16 slot_id;

        typedef uint32 unique_id;

        static const id invalid_id = 0xffffffffffffffff;

        static const uint32 invalid_pool_id = 0xffff;

        static const uint32 pool_id_mask = 0xffff;

        static const uint32 pool_id_offset = 32;

        static const uint32 invalid_slot_id = 0xffff;

        static const uint32 slot_id_mask = 0xffff;

        static const uint32 slot_id_offset = 16;

        static const uint32 invalid_unique_id = 0xffffffff;

        static const uint32 unique_id_mask = 0xffffffff;

        static id generate_id(unique_id uid, slot_id sid, pool_id pid);

        static pool_id get_pool_id(id rid);

        static slot_id get_slot_id(id rid);

        static unique_id get_unique_id(id rid);
    };

    template <class CONFIG>
    class resource_base
    {
    public:
        virtual ~resource_base() {}

        void initialize(resource::id id, const CONFIG &config);

        virtual void finalize();

        resource::id id;

        resource::status status = resource::status::invalid;

        CONFIG config;
    };

    inline resource::id resource::generate_id(unique_id uid, slot_id sid, pool_id pid)
    {
        return (static_cast<uint64>(pid) & pool_id_mask) << pool_id_offset | (sid & slot_id_mask) << slot_id_offset | uid;
    }

    inline resource::pool_id resource::get_pool_id(id rid)
    {
        return rid >> pool_id_offset & pool_id_mask;
    }

    inline resource::slot_id resource::get_slot_id(id rid)
    {
        return rid >> slot_id_offset & slot_id_mask;
    }

    inline resource::unique_id resource::get_unique_id(id rid)
    {
        return rid & unique_id_mask;
    }

    template <class CONFIG>
    void resource_base<CONFIG>::initialize(resource::id id, const CONFIG &config)
    {
        this->id = id;
        this->status = resource::status::pending;
        this->config = config;
    }

    template <class CONFIG>
    inline void resource_base<CONFIG>::finalize()
    {
        id = resource::invalid_id;
        status = resource::status::invalid;
        config = CONFIG();
    }
}
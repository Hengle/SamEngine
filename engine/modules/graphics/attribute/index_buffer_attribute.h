#pragma once

#include "graphics/core/define.h"

namespace sam
{
    class index_buffer_attribute
    {
    public:
        int32 count = 0;

        index_type type = index_type::none;

        buffer_usage usage = buffer_usage::immutable;

        int32 size() const;
    };

    inline int32 index_buffer_attribute::size() const
    {
        return count * sizeof_index(type);
    }
}
#pragma once

#include "define.h"

namespace sam
{
    class stencil_state
    {
    public:
        union
        {
            #pragma pack(push, 1)
            struct
            {
                stencil_operation fail : 4;
                stencil_operation depth_fail : 4;
                stencil_operation pass : 4;
                compare_func compare : 4;
            };
            #pragma pack(pop)
            uint16 value;
        };

        stencil_state();

        bool operator==(const stencil_state &other) const;

        bool operator!=(const stencil_state &other) const;
    };

    inline stencil_state::stencil_state()
    {
        static_assert(sizeof(stencil_state) == sizeof(uint16), "wrong size of stencil_state");
        value = 0;
        fail = stencil_operation::keep;
        depth_fail = stencil_operation::keep;
        pass = stencil_operation::keep;
        compare = compare_func::always;
    }

    inline bool stencil_state::operator==(const stencil_state &other) const
    {
        return this->value == other.value;
    }

    inline bool stencil_state::operator!=(const stencil_state &other) const
    {
        return this->value != other.value;
    }

    class depth_stencil_state
    {
    public:
        stencil_state front;

        stencil_state back;

        union
        {
            #pragma pack(push, 1)
            struct
            {
                compare_func compare : 4;
                bool is_depth_enable : 1;
                bool is_stencil_enable : 1;
                uint8 stencil_read_mask : 8;
                uint8 stencil_write_mask : 8;
                uint8 stencil_value : 8;
            };
            #pragma pack(pop)
            uint32 value;
        };

        depth_stencil_state();

        bool operator==(const depth_stencil_state &other) const;

        bool operator!=(const depth_stencil_state &other) const;
    };

    inline depth_stencil_state::depth_stencil_state()
    {
        static_assert(sizeof(depth_stencil_state) == (sizeof(uint32) + 2 * sizeof(stencil_state)), "wrong size of depth_stencil_state");
        value = 0;
        compare = compare_func::always;
        is_depth_enable = false;
        is_stencil_enable = false;
        stencil_read_mask = 0xff;
        stencil_write_mask = 0xff;
        stencil_value = 0;
    }

    inline bool depth_stencil_state::operator==(const depth_stencil_state &other) const
    {
        return this->value == other.value && this->front == other.front && this->back == other.back;
    }

    inline bool depth_stencil_state::operator!=(const depth_stencil_state &other) const
    {
        return this->value != other.value || this->front != other.front || this->back != other.back;
    }
}
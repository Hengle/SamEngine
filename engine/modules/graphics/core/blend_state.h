#pragma once

#include "define.h"

#include "core/types.h"

namespace sam
{
    class blend_state
    {
    public:
        union
        {
            #pragma pack(push,1)
            struct
            {
                bool enabled : 1;

                blend_factor src_rgb_factor : 4;
                blend_factor dst_rgb_factor : 4;
                blend_operation rgb_operation : 3;

                blend_factor src_alpha_factor : 4;
                blend_factor dst_alpha_factor : 4;
                blend_operation alpha_operation : 3;

                pixel_channel color_mask : 5;
                pixel_format color_format : 5;
                pixel_format depth_format : 5;
            };
            #pragma pack(pop)
            uint64 value;
        };

        blend_state();

        bool operator==(const blend_state &other) const;

        bool operator!=(const blend_state &other) const;
    };

    inline blend_state::blend_state()
    {
        static_assert(sizeof(blend_state) == sizeof(uint64), "wrong size of blend_state");
        value = 0;
        enabled = false;
        src_rgb_factor = blend_factor::one;
        dst_rgb_factor = blend_factor::zero;
        rgb_operation = blend_operation::add;
        src_alpha_factor = blend_factor::one;
        dst_alpha_factor = blend_factor::zero;
        alpha_operation = blend_operation::add;
        color_mask = pixel_channel_type::rgba;
        color_format = pixel_format::RGB8;
        depth_format = pixel_format::D24S8;
    }

    inline bool blend_state::operator==(const blend_state &other) const
    {
        return this->value == other.value;
    }

    inline bool blend_state::operator!=(const blend_state &other) const
    {
        return this->value != other.value;
    }
}
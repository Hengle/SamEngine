#pragma once

#include "define.h"

namespace sam
{
    class rasterizer_state
    {
    public:
        union
        {
            #pragma pack(push, 1)
            struct
            {
                bool is_cull_face_enable : 1;
                bool is_depth_offset_enable : 1;
                bool is_scissor_test_enable : 1;
                bool is_dither_enable : 1;
                bool is_alpha_to_coverage_enable : 1;
                face_side cull_face : 2;
                uint8 sample : 4;
            };
            #pragma pack(pop)
            uint16 value;
        };

        rasterizer_state();

        bool operator==(const rasterizer_state &other) const;

        bool operator!=(const rasterizer_state &other) const;
    };

    inline rasterizer_state::rasterizer_state()
    {
        static_assert(sizeof(rasterizer_state) == sizeof(uint16), "wrong size of rasterizer_state");
        value = 0;
        is_cull_face_enable = false;
        is_depth_offset_enable = false;
        is_scissor_test_enable = false;
        is_dither_enable = true;
        is_alpha_to_coverage_enable = false;
        cull_face = face_side::back;
        sample = 1;
    }

    inline bool rasterizer_state::operator==(const rasterizer_state &other) const
    {
        return this->value == other.value;
    }

    inline bool rasterizer_state::operator!=(const rasterizer_state &other) const
    {
        return this->value != other.value;
    }
}
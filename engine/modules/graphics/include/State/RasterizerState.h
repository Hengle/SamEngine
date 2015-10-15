#pragma once

#include "GraphicsDefine.h"

namespace SamEngine
{
    struct GRAPHICS_API RasterizerState
    {
        union
        {
            #pragma pack(push, 1)
            struct
            {
                bool CullFaceEnable : 1;
                bool DepthOffsetEnable : 1;
                bool ScissorTestEnable : 1;
                bool DitherEnable : 1;
                bool AlphaToCoverageEnable : 1;
                FaceSide CullFace : 2;
                uint8 Sample : 4;
            };
            #pragma pack(pop)
            uint16 Value;
        };

        RasterizerState();

        bool operator==(const RasterizerState &other) const;

        bool operator!=(const RasterizerState &other) const;
    };

    inline RasterizerState::RasterizerState()
    {
        static_assert(sizeof(RasterizerState) == sizeof(uint16), "wrong size of RasterizerState");
        Value = 0;
        CullFaceEnable = false;
        DepthOffsetEnable = false;
        ScissorTestEnable = false;
        DitherEnable = true;
        AlphaToCoverageEnable = false;
        CullFace = FaceSide::BACK;
        Sample = 1;
    }

    inline bool RasterizerState::operator==(const RasterizerState &other) const
    {
        return this->Value == other.Value;
    }

    inline bool RasterizerState::operator!=(const RasterizerState &other) const
    {
        return this->Value != other.Value;
    }
}
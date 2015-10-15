#pragma once

#include "GraphicsDefine.h"

namespace SamEngine
{
    struct GRAPHICS_API StencilState
    {
    public:
        union
        {
            #pragma pack(push, 1)
            struct
            {
                StencilOperation Fail : 4;
                StencilOperation DepthFail : 4;
                StencilOperation Pass : 4;
                CompareFunction Compare : 4;
            };
            #pragma pack(pop)
            uint16 Value;
        };

        StencilState();

        bool operator==(const StencilState &other) const;

        bool operator!=(const StencilState &other) const;
    };

    inline StencilState::StencilState()
    {
        static_assert(sizeof(StencilState) == sizeof(uint16), "wrong size of StencilState");
        Value = 0;
        Fail = StencilOperation::KEEP;
        DepthFail = StencilOperation::KEEP;
        Pass = StencilOperation::KEEP;
        Compare = CompareFunction::ALWAYS;
    }

    inline bool StencilState::operator==(const StencilState &other) const
    {
        return this->Value == other.Value;
    }

    inline bool StencilState::operator!=(const StencilState &other) const
    {
        return this->Value != other.Value;
    }

    struct GRAPHICS_API DepthStencilState
    {
        StencilState Front;

        StencilState Back;

        union
        {
            #pragma pack(push, 1)
            struct
            {
                CompareFunction Compare : 4;
                bool DepthEnable : 1;
                bool StencilEnable : 1;
                uint8 StencilReadMask : 8;
                uint8 StencilWriteMask : 8;
                uint8 StencilValue : 8;
            };
            #pragma pack(pop)
            uint32 Value;
        };

        DepthStencilState();

        bool operator==(const DepthStencilState &other) const;

        bool operator!=(const DepthStencilState &other) const;
    };

    inline DepthStencilState::DepthStencilState()
    {
        static_assert(sizeof(DepthStencilState) == (sizeof(uint32) + 2 * sizeof(StencilState)), "wrong size of DepthStencilState");
        Value = 0;
        Compare = CompareFunction::ALWAYS;
        DepthEnable = false;
        StencilEnable = false;
        StencilReadMask = 0xff;
        StencilWriteMask = 0xff;
        StencilValue = 0;
    }

    inline bool DepthStencilState::operator==(const DepthStencilState &other) const
    {
        return this->Value == other.Value && this->Front == other.Front && this->Back == other.Back;
    }

    inline bool DepthStencilState::operator!=(const DepthStencilState &other) const
    {
        return this->Value != other.Value || this->Front != other.Front || this->Back != other.Back;
    }
}
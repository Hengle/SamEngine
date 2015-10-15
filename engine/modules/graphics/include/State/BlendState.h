#pragma once

#include "GraphicsDefine.h"

#include <WindowModule.h>

namespace SamEngine
{
    struct GRAPHICS_API BlendState
    {
        union
        {
            #pragma pack(push,1)
            struct
            {
                bool Enabled : 1;

                BlendFactor SrcRGBFactor : 5;
                BlendFactor DstRGBFactor : 5;
                BlendOperation RGBOperation : 3;

                BlendFactor SrcAlphaFactor : 5;
                BlendFactor DstAlphaFactor : 5;
                BlendOperation AlphaOperation : 3;

                PixelChannel ColorMask : 4;
                PixelFormat ColorFormat : 5;
                PixelFormat DepthFormat : 5;
            };
            #pragma pack(pop)
            uint64 Value;
        };

        Color BlendColor{ 1.0f, 1.0f, 1.0f, 1.0f };

        BlendState();

        bool operator==(const BlendState &other) const;

        bool operator!=(const BlendState &other) const;
    };

    inline BlendState::BlendState()
    {
        static_assert(sizeof(BlendState) == sizeof(uint64) + sizeof(Color), "wrong size of blend_state");
        Value = 0;
        Enabled = false;
        SrcRGBFactor = BlendFactor::ONE;
        DstRGBFactor = BlendFactor::ZERO;
        RGBOperation = BlendOperation::ADD;
        SrcAlphaFactor = BlendFactor::ONE;
        DstAlphaFactor = BlendFactor::ZERO;
        AlphaOperation = BlendOperation::ADD;
        ColorMask = PixelChannel::RGBA;
        ColorFormat = PixelFormat::RGB8;
        DepthFormat = PixelFormat::D24S8;
        BlendColor = Color(1.0f, 1.0f, 1.0f, 1.0f);
    }

    inline bool BlendState::operator==(const BlendState &other) const
    {
        return this->Value == other.Value && BlendColor == other.BlendColor;
    }

    inline bool BlendState::operator!=(const BlendState &other) const
    {
        return this->Value != other.Value || BlendColor != BlendColor;
    }
}
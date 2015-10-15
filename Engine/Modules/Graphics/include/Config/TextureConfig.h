#pragma once

#include "GraphicsDefine.h"

#include <WindowModule.h>

namespace SamEngine
{
    struct GRAPHICS_API TextureConfig
    {
        static TextureConfig FromData(int32 width, int32 height, int32 mipMapCount, TextureType type, PixelFormat format);

        ResourceName Name { ResourceName::Unique() };

        TextureType Type{ TextureType::TEXTURE_2D };

        PixelFormat ColorFormat{ PixelFormat::NONE };

        PixelFormat DepthFormat{ PixelFormat::NONE };

        int32 Width{ 0 };

        int32 Height{ 0 };

        int32 Depth{ 0 };

        int32 MipMapCount{ 1 };

        bool IsRenderTarget{ false };

        bool DepthBufferEnabled{ false };

        bool SharedDepthBufferEnabled{ false };

        ResourceID DepthRenderTarget{ InvalidResourceID };

        TextureWrapMode WrapModeS{ TextureWrapMode::REPEAT };

        TextureWrapMode WrapModeT{ TextureWrapMode::REPEAT };

        TextureWrapMode WrapModeR{ TextureWrapMode::REPEAT };

        TextureFilterMode FilterModeMin{ TextureFilterMode::NEAREST };

        TextureFilterMode FilterModeMag{ TextureFilterMode::NEAREST };

        int32 DataOffset[GraphicsConfig::CubeTextureFaceCount][GraphicsConfig::MaxTextureMipMapCount];
        int32 DataSize[GraphicsConfig::CubeTextureFaceCount][GraphicsConfig::MaxTextureMipMapCount];
    };

    inline TextureConfig TextureConfig::FromData(int32 width, int32 height, int32 mipMapCount, TextureType type, PixelFormat format)
    {
        s_assert(width > 0 && height > 0);
        s_assert_range(mipMapCount, 0, GraphicsConfig::MaxTextureMipMapCount);

        TextureConfig config;
        config.Width = width;
        config.Height = height;
        config.MipMapCount = mipMapCount;
        config.Type = type;
        config.ColorFormat = format;
        return config;
    }
}
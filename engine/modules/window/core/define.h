#pragma once

#include <core/types.h>

namespace sam
{
    typedef uint8 pixel_channel;

    class pixel_channel_type
    {
    public:
        static const uint8 none = 0;

        static const uint8 alpha = 1 << 0;
        static const uint8 red = 1 << 1;
        static const uint8 green = 1 << 2;
        static const uint8 blue = 1 << 3;
        static const uint8 depth = 1 << 4;
        static const uint8 stencil = 1 << 5;

        static const uint8 depth_and_stencil = depth | stencil;

        static const uint8 rgba = alpha | red | green | blue;

        static const uint8 all = alpha | red | green | blue | depth | stencil;
    };

    enum class pixel_format : uint8
    {
        NONE,
        RGBA8,          ///< 32-bit wide, 4 channels @ 8-bit
        RGB8,           ///< 24-bit wide, 3 channels @ 8-bit
        RGBA4,          ///< 16-bit wide, 4 channels @ 4-bit
        R5G6B5,         ///< 16-bit wide, 3 channels @ 5/6/5 bits
        R5G5B5A1,       ///< 16-bit wide, 4 channels @ 1-bit alpha, 5-bit rgb
        RGBA32F,        ///< 128-bit wide, 4 channel @ 32-bit float
        RGBA16F,        ///< 64-bit wide, 4 channel @ 16-bit float
        L8,             ///< 8-bit wide, single channel
        DXT1,           ///< DXT1 compressed format
        DXT3,           ///< DXT3 compressed format
        DXT5,           ///< DXT5 compressed format
        D16,            ///< 16-bit depth
        D32,            ///< 32-bit depth
        D24S8,          ///< 24-bit depth, 8-bit stencil
        PVRTC2_RGB,     ///< PVRTC2 compressed format (RGB)
        PVRTC4_RGB,     ///< PVRTC4 compressed format (RGB)
        PVRTC2_RGBA,    ///< PVRTC2 compressed format (RGBA)
        PVRTC4_RGBA,    ///< PVRTC4 compressed format (RGBA)
        ETC2_RGB8,      ///< ETC2 compressed format (RGB8)
        ETC2_SRGB8,     ///< ETC2 compressed format (SRGB8)
    };

    static int8 channel_bits_of_format(pixel_format format, pixel_channel channel)
    {
        int8 count = 0;
        switch (format)
        {
        case pixel_format::RGBA32F:
            if ((pixel_channel_type::red == channel) || (pixel_channel_type::green == channel) || (pixel_channel_type::blue == channel) || (pixel_channel_type::alpha == channel))
            {
                count = 32;
            }
            break;
        case pixel_format::RGBA16F:
            if ((pixel_channel_type::red == channel) || (pixel_channel_type::green == channel) || (pixel_channel_type::blue == channel) || (pixel_channel_type::alpha == channel))
            {
                count = 16;
            }
            break;
        case pixel_format::RGBA8:
            if ((pixel_channel_type::red == channel) || (pixel_channel_type::green == channel) || (pixel_channel_type::blue == channel) || (pixel_channel_type::alpha == channel))
            {
                count = 8;
            }
            break;
        case pixel_format::RGB8:
            if ((pixel_channel_type::red == channel) || (pixel_channel_type::green == channel) || (pixel_channel_type::blue == channel))
            {
                count = 8;
            }
            break;
        case pixel_format::R5G6B5:
            if ((pixel_channel_type::red == channel) || (pixel_channel_type::blue == channel))
            {
                count = 5;
            }
            else if (pixel_channel_type::green == channel)
            {
                count = 6;
            }
            break;
        case pixel_format::R5G5B5A1:
            if ((pixel_channel_type::red == channel) || (pixel_channel_type::green == channel) || (pixel_channel_type::blue == channel))
            {
                count = 5;
            }
            else if (pixel_channel_type::alpha == channel)
            {
                count = 1;
            }
            break;
        case pixel_format::RGBA4:
            if ((pixel_channel_type::red == channel) || (pixel_channel_type::green == channel) || (pixel_channel_type::blue == channel) || (pixel_channel_type::alpha == channel))
            {
                count = 4;
            }
            break;
        case pixel_format::L8:
            if (pixel_channel_type::red == channel)
            {
                count = 8;
            }
            break;
        case pixel_format::D16:
            if (pixel_channel_type::depth == channel)
            {
                count = 16;
            }
            break;
        case pixel_format::D32:
            if (pixel_channel_type::depth == channel)
            {
                count = 32;
            }
            break;
        case pixel_format::D24S8:
            if (pixel_channel_type::depth == channel)
            {
                count = 24;
            }
            else if (pixel_channel_type::stencil == channel)
            {
                count = 8;
            }
            break;
        default:
            break;
        }
        return count;
    }
}
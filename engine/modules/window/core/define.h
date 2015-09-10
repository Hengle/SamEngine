#pragma once

#include <core/types.h>

#include <cstddef>

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
        none,
        rgba8,          ///< 32-bit wide, 4 channels @ 8-bit
        rgb8,           ///< 24-bit wide, 3 channels @ 8-bit
        rgba4,          ///< 16-bit wide, 4 channels @ 4-bit
        r5g6b5,         ///< 16-bit wide, 3 channels @ 5/6/5 bits
        r5g5b5a1,       ///< 16-bit wide, 4 channels @ 1-bit alpha, 5-bit rgb
        rgba32f,        ///< 128-bit wide, 4 channel @ 32-bit float
        rgba16f,        ///< 64-bit wide, 4 channel @ 16-bit float
        l8,             ///< 8-bit wide, single channel
        dxt1,           ///< DXT1 compressed format
        dxt3,           ///< DXT3 compressed format
        dxt5,           ///< DXT5 compressed format
        d16,            ///< 16-bit depth
        d32,            ///< 32-bit depth
        d24s8,          ///< 24-bit depth, 8-bit stencil
        pvrtc2_rgb,     ///< PVRTC2 compressed format (RGB)
        pvrtc4_rgb,     ///< PVRTC4 compressed format (RGB)
        pvrtc2_rgba,    ///< PVRTC2 compressed format (RGBA)
        pvrtc4_rgba,    ///< PVRTC4 compressed format (RGBA)
        etc2_rgb8,      ///< ETC2 compressed format (RGB8)
        etc2_srgb8,     ///< ETC2 compressed format (SRGB8)
    };

    static bool is_depth_format(pixel_format format)
    {
        switch (format)
        {
        case pixel_format::d16:
        case pixel_format::d32:
        case pixel_format::d24s8:
            return true;
        default:
            return false;
        }
    }
    
    static bool is_compressed_format(pixel_format format)
    {
        switch (format)
        {
        case pixel_format::dxt1:
        case pixel_format::dxt3:
        case pixel_format::dxt5:
        case pixel_format::pvrtc2_rgb:
        case pixel_format::pvrtc4_rgb:
        case pixel_format::pvrtc2_rgba:
        case pixel_format::pvrtc4_rgba:
        case pixel_format::etc2_rgb8:
        case pixel_format::etc2_srgb8:
            return true;
        default:
            return false;
        }
    }

    static size_t sizeof_pixel_format(pixel_format format)
    {
        switch (format)
        {
        case pixel_format::rgba8: return 4;
        case pixel_format::rgb8: return 3;
        case pixel_format::rgba4: return 2;
        case pixel_format::r5g6b5: return 2;
        case pixel_format::r5g5b5a1: return 2;
        case pixel_format::rgba32f: return 16;
        case pixel_format::rgba16f: return 8;
        case pixel_format::l8: return 1;
        default: return 0;
        }
    }

    static int8 channel_bits_of_format(pixel_format format, pixel_channel channel)
    {
        int8 count = 0;
        switch (format)
        {
        case pixel_format::rgba32f:
            if ((pixel_channel_type::red == channel) || (pixel_channel_type::green == channel) || (pixel_channel_type::blue == channel) || (pixel_channel_type::alpha == channel))
            {
                count = 32;
            }
            break;
        case pixel_format::rgba16f:
            if ((pixel_channel_type::red == channel) || (pixel_channel_type::green == channel) || (pixel_channel_type::blue == channel) || (pixel_channel_type::alpha == channel))
            {
                count = 16;
            }
            break;
        case pixel_format::rgba8:
            if ((pixel_channel_type::red == channel) || (pixel_channel_type::green == channel) || (pixel_channel_type::blue == channel) || (pixel_channel_type::alpha == channel))
            {
                count = 8;
            }
            break;
        case pixel_format::rgb8:
            if ((pixel_channel_type::red == channel) || (pixel_channel_type::green == channel) || (pixel_channel_type::blue == channel))
            {
                count = 8;
            }
            break;
        case pixel_format::r5g6b5:
            if ((pixel_channel_type::red == channel) || (pixel_channel_type::blue == channel))
            {
                count = 5;
            }
            else if (pixel_channel_type::green == channel)
            {
                count = 6;
            }
            break;
        case pixel_format::r5g5b5a1:
            if ((pixel_channel_type::red == channel) || (pixel_channel_type::green == channel) || (pixel_channel_type::blue == channel))
            {
                count = 5;
            }
            else if (pixel_channel_type::alpha == channel)
            {
                count = 1;
            }
            break;
        case pixel_format::rgba4:
            if ((pixel_channel_type::red == channel) || (pixel_channel_type::green == channel) || (pixel_channel_type::blue == channel) || (pixel_channel_type::alpha == channel))
            {
                count = 4;
            }
            break;
        case pixel_format::l8:
            if (pixel_channel_type::red == channel)
            {
                count = 8;
            }
            break;
        case pixel_format::d16:
            if (pixel_channel_type::depth == channel)
            {
                count = 16;
            }
            break;
        case pixel_format::d32:
            if (pixel_channel_type::depth == channel)
            {
                count = 32;
            }
            break;
        case pixel_format::d24s8:
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
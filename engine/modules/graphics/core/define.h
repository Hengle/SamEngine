#pragma once

#include "core/types.h"

#include <glm.hpp>

#undef assert

namespace sam
{
    typedef glm::vec4 color;

    enum class graphics_resource_type
    {
        texture,
        shader,
        mesh,
        draw_state,
        count,
    };

    enum class blend_factor : uint8
    {
        zero,
        one,

        src_color,
        one_minus_src_color,

        src_alpha,
        one_minus_src_alpha,

        dst_color,
        one_minus_dst_color,

        dst_alpha,
        one_minux_dst_alpha,

        blend_color,
        one_minus_blend_color,

        blend_alpha,
        one_minus_blend_alpha,

        src_color_saturated,
    };

    enum class pixel_channel :uint8
    {
        none = 0,

        alpha = 1 << 0,
        red = 1 << 1,
        green = 1 << 2,
        blue = 1 << 3,
        depth = 1 << 4,
        stencil = 1 << 5,

        depth_and_stencil = depth | stencil,

        rgba = alpha | red | green | blue,

        all = alpha | red | green | blue | depth | stencil,
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
        int8 size = 0;
        switch (format)
        {
        case pixel_format::RGBA32F:
            if ((pixel_channel::red == channel) || (pixel_channel::green == channel) || (pixel_channel::blue == channel) || (pixel_channel::alpha == channel))
            {
                size = 32;
            }
            break;
        case pixel_format::RGBA16F:
            if ((pixel_channel::red == channel) || (pixel_channel::green == channel) || (pixel_channel::blue == channel) || (pixel_channel::alpha == channel))
            {
                size = 16;
            }
            break;
        case pixel_format::RGBA8:
            if ((pixel_channel::red == channel) || (pixel_channel::green == channel) || (pixel_channel::blue == channel) || (pixel_channel::alpha == channel))
            {
                size = 8;
            }
            break;
        case pixel_format::RGB8:
            if ((pixel_channel::red == channel) || (pixel_channel::green == channel) || (pixel_channel::blue == channel))
            {
                size = 8;
            }
            break;
        case pixel_format::R5G6B5:
            if ((pixel_channel::red == channel) || (pixel_channel::blue == channel))
            {
                size = 5;
            }
            else if (pixel_channel::green == channel)
            {
                size = 6;
            }
            break;
        case pixel_format::R5G5B5A1:
            if ((pixel_channel::red == channel) || (pixel_channel::green == channel) || (pixel_channel::blue == channel))
            {
                size = 5;
            }
            else if (pixel_channel::alpha == channel)
            {
                size = 1;
            }
            break;
        case pixel_format::RGBA4:
            if ((pixel_channel::red == channel) || (pixel_channel::green == channel) || (pixel_channel::blue == channel) || (pixel_channel::alpha == channel))
            {
                size = 4;
            }
            break;
        case pixel_format::L8:
            if (pixel_channel::red == channel)
            {
                size = 8;
            }
            break;
        case pixel_format::D16:
            if (pixel_channel::depth == channel)
            {
                size = 16;
            }
            break;
        case pixel_format::D32:
            if (pixel_channel::depth == channel)
            {
                size = 32;
            }
            break;
        case pixel_format::D24S8:
            if (pixel_channel::depth == channel)
            {
                size = 24;
            }
            else if (pixel_channel::stencil == channel)
            {
                size = 8;
            }
            break;
        default:
            break;
        }
        return size;
    }

    enum class blend_operation : uint8
    {
        add,
        substract,
        reverse_subtract,
        min,
        max,
    };

    enum class texture_type : uint8
    {
        invalid,
        texture_2d,
        texture_3d,
        texture_cube,
    };

    enum class resource_usage : uint8
    {
        invalid,
        immutable,
        statics,
        dynamic,
        stream,
    };

    enum class compare_func : uint8
    {
        never,
        less,
        less_equal,
        greater,
        greater_equal,
        equal,
        not_equal,
        always,
    };

    enum class stencil_operation : uint8
    {
        keep,
        zero,
        replace,
        increment,
        increment_wrap,
        decrement,
        decrement_wrap,
        invert,
    };

    enum class face_side : uint8
    {
        front,
        back,
        both
    };
}
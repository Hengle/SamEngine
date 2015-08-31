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

    enum class index_type : uint8
    {
        none,
        uint16,
        uint32,
    };

    static int32 sizeof_index(index_type type)
    {
        auto size = 0;
        switch (type)
        {
        case index_type::none:
            size = 0;
            break;
        case index_type::uint16:
            size = 2;
            break;
        case index_type::uint32:
            size = 4;
            break;
        }
        return size;
    }

    enum class vertex_attribute : uint8
    {
        invalid,
        position,
        texcoord0,
        texcoord1,
        texcorrd2,
        texcorrd3,
        color0,
        color1,
        normal,
        tangent,
        binormal,
        weights,
        indices,
        instance0,
        instance1,
        instance2,
        instance3,
    };

    static const char *attribute_name(vertex_attribute attribute)
    {
        switch (attribute)
        {
        case vertex_attribute::position: return "position";
        case vertex_attribute::texcoord0: return "texcoord0";
        case vertex_attribute::texcoord1: return "texcoord1";
        case vertex_attribute::texcorrd2: return "texcorrd2";
        case vertex_attribute::texcorrd3: return "texcorrd3";
        case vertex_attribute::color0: return "color0";
        case vertex_attribute::color1: return "color1";
        case vertex_attribute::normal: return "normal";
        case vertex_attribute::tangent: return "tangent";
        case vertex_attribute::binormal: return "binormal";
        case vertex_attribute::weights: return "weights";
        case vertex_attribute::indices: return "indices";
        case vertex_attribute::instance0: return "instance0";
        case vertex_attribute::instance1: return "instance1";
        case vertex_attribute::instance2: return "instance2";
        case vertex_attribute::instance3: return "instance3";
        default: return nullptr;
        }
    }

    enum class vertex_attribute_format : uint8
    {
        invalid,
        float1,
        float2,
        float3,
        float4,
        byte4,
        byte4_normalized,
        unsigned_byte4,
        unsigned_byte4_normalized,
        short2,
        short2_normalized,
        short4,
        short4_normalized,
    };

    static int32 sizeof_attribute_format(vertex_attribute_format format)
    {
        switch (format)
        {
        case vertex_attribute_format::float1: return 4;
        case vertex_attribute_format::float2: return 8;
        case vertex_attribute_format::float3: return 12;
        case vertex_attribute_format::float4: return 16;
        case vertex_attribute_format::byte4: return 4;
        case vertex_attribute_format::byte4_normalized: return 4;
        case vertex_attribute_format::unsigned_byte4: return 4;
        case vertex_attribute_format::unsigned_byte4_normalized: return 4;
        case vertex_attribute_format::short2: return 4;
        case vertex_attribute_format::short2_normalized: return 4;
        case vertex_attribute_format::short4: return 8;
        case vertex_attribute_format::short4_normalized: return 8;
        default: return 0;
        }
    }

    enum class uniform_format : uint8
    {
        invalid,
        int1,
        bool1,
        vector1,
        vector2,
        vector3,
        vector4,
        matrix2,
        matrix3,
        matrix4,
        texture,
    };

    static int32 sizeof_uniform_format(uniform_format format)
    {
        switch (format)
        {
        case uniform_format::int1: return sizeof(int32);
        case uniform_format::bool1:
        case uniform_format::vector1:
        case uniform_format::vector2:
        case uniform_format::vector3:
        case uniform_format::vector4:
        case uniform_format::matrix2:
        case uniform_format::matrix3:
        case uniform_format::matrix4:
        case uniform_format::texture:
        default: return 0;
        }
    }

    enum class draw_type : uint8
    {
        points,
        lines,
        line_strip,
        line_loop,
        triangles,
        triangle_strip,
        triangle_fan,
    };
}
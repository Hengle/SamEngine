#pragma once

#include <core/types.h>

#include <window/core/define.h>

#include <glm.hpp>

namespace sam
{
    typedef glm::vec4 color;

    enum class graphics_resource_type : uint16
    {
        mesh,
        shader,
        texture,
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

        src_alpha_saturated,
    };

    enum class blend_operation : uint8
    {
        add,
        substract,
        reverse_subtract,
    };

    enum class texture_type : uint8
    {
        texture_2d,
        texture_3d,
        texture_cube,
    };

    enum class buffer_usage : uint8
    {
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

    enum class vertex_attribute_type : uint8
    {
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

        max_count,
    };

    static const char *attribute_name(vertex_attribute_type attribute)
    {
        switch (attribute)
        {
        case vertex_attribute_type::position: return "position";
        case vertex_attribute_type::texcoord0: return "texcoord0";
        case vertex_attribute_type::texcoord1: return "texcoord1";
        case vertex_attribute_type::texcorrd2: return "texcorrd2";
        case vertex_attribute_type::texcorrd3: return "texcorrd3";
        case vertex_attribute_type::color0: return "color0";
        case vertex_attribute_type::color1: return "color1";
        case vertex_attribute_type::normal: return "normal";
        case vertex_attribute_type::tangent: return "tangent";
        case vertex_attribute_type::binormal: return "binormal";
        case vertex_attribute_type::weights: return "weights";
        case vertex_attribute_type::indices: return "indices";
        case vertex_attribute_type::instance0: return "instance0";
        case vertex_attribute_type::instance1: return "instance1";
        case vertex_attribute_type::instance2: return "instance2";
        case vertex_attribute_type::instance3: return "instance3";
        default: return nullptr;
        }
    }

    enum class vertex_attribute_format : uint8
    {
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

    enum class texture_wrap_mode : uint8
    {
        clamp_to_edge,
        repeat,
        mirrored_repeat,
    };

    enum class texture_filter_mode : uint8
    {
        nearest,
        linear,
        nearest_mipmap_nearest,
        nearest_mipmap_linear,
        linear_mipmap_nearest,
        linear_mipmap_linear,
    };

    static bool filter_mode_use_mipmap(texture_filter_mode mode)
    {
        return !(mode == texture_filter_mode::nearest || mode == texture_filter_mode::linear);
    }

    enum class shader_type : uint8
    {
        vertex_shader,
        fragment_shader,
    };
}
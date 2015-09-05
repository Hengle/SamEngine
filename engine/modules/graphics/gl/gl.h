#pragma once

#include "graphics/core/define.h"
#include "graphics/core/blend_state.h"
#include "graphics/core/rasterizer_state.h"
#include "graphics/core/depth_stencil_state.h"
#include "graphics/config/graphics_config.h"

#include <core/assert.h>
#include <core/log.h>

#include <glad.h>

#include <cstring>

#if SAM_DEBUG
#    define s_check_gl_error() \
        do \
        { \
            GLenum error; \
            while ((error = glGetError()) != GL_NO_ERROR) \
            { \
                switch (error) \
                { \
                    case GL_NO_ERROR: \
                        sam::log::debug("GL_NO_ERROR\n"); \
                        SAM_TRAP(); \
                    case GL_INVALID_ENUM: \
                        sam::log::debug("GL_INVALID_ENUM\n"); \
                        SAM_TRAP(); \
                    case GL_INVALID_OPERATION: \
                        sam::log::debug("GL_INVALID_OPERATION\n"); \
                        SAM_TRAP(); \
                    case GL_INVALID_VALUE: \
                        sam::log::debug("GL_INVALID_VALUE\n"); \
                        SAM_TRAP(); \
                    case GL_INVALID_FRAMEBUFFER_OPERATION: \
                        sam::log::debug("GL_INVALID_FRAMEBUFFER_OPERATION\n"); \
                        SAM_TRAP(); \
                    case GL_OUT_OF_MEMORY: \
                        sam::log::debug("GL_OUT_OF_MEMORY\n"); \
                        SAM_TRAP(); \
                    default: \
                        sam::log::debug("UNKNOWN_ERROR\n"); \
                        SAM_TRAP(); \
                } \
            } \
        } while(0)
#else
#    define s_check_gl_error() ((void)0)
#endif

namespace sam
{
    class gl_vertex_attribute
    {
    public:
        bool enabled{ false };

        bool streaming{ false };

        GLuint index{ 0 };

        GLsizei stride{ 0 };

        GLint size{ 0 };

        GLboolean normalized{ 0 };

        GLvoid *offset{ nullptr };

        GLenum type{ 0 };

        void operator=(const gl_vertex_attribute &other)
        {
            std::memcpy(this, &other, sizeof(gl_vertex_attribute));
        }

        bool operator==(const gl_vertex_attribute &other) const
        {
            return std::memcmp(this, &other, sizeof(gl_vertex_attribute)) == 0;
        }

        bool operator!=(const gl_vertex_attribute &other) const
        {
            return std::memcmp(this, &other, sizeof(gl_vertex_attribute)) != 0;
        }
    };

    class gl_cache
    {
    public:
        blend_state blend_state_cache;
        depth_stencil_state depth_stencil_state_cache;
        rasterizer_state rasterizer_state_cache;

        GLint view_port_x;
        GLint view_port_y;
        GLsizei view_port_width;
        GLsizei view_port_height;

        GLint scissor_x;
        GLint scissor_y;
        GLsizei scissor_width;
        GLsizei scissor_height;

        color blend_color;

        GLuint vao;
        GLuint vertex_buffer;
        GLuint index_buffer;
        GLuint program;

        GLuint texture_2d[graphics_config::max_texture_count];
        GLuint texture_cube[graphics_config::max_texture_count];

        GLuint vertex_attribute[static_cast<uint8>(vertex_attribute_type::max_count)];
        gl_vertex_attribute gl_vertex_attribute[static_cast<uint8>(vertex_attribute_type::max_count)];
    };

    class gl
    {
    public:
        static GLenum from_resource_usage(buffer_usage usage);

        static GLenum from_texture_filter_mode(texture_filter_mode mode);

        static GLenum from_texture_wrap_mode(texture_wrap_mode mode);

        static GLenum from_texture_type(texture_type type);

        static GLenum from_pixel_format_as_internal(pixel_format format);

        static GLenum from_pixel_format_as_layout(pixel_format format);

        static GLenum from_pixel_format_as_format(pixel_format format);

        static GLenum from_shader_type(shader_type type);

        static GLint from_vertex_attribute_format_as_count(vertex_attribute_format format);

        static GLenum from_vertex_attribute_format_as_type(vertex_attribute_format format);

        static GLboolean from_vertex_attribute_format_as_normalized(vertex_attribute_format format);

        static GLenum from_draw_type(draw_type type);

        static GLenum from_index_type(index_type type);

        static GLenum from_blend_factor(blend_factor type);

        static GLenum from_blend_operation(blend_operation type);

        static GLenum from_compare_func(compare_func func);

        static GLenum from_stencil_operation(stencil_operation type);

        static GLenum from_face_side(face_side face);
    };

    inline GLenum gl::from_resource_usage(buffer_usage usage)
    {
        switch (usage)
        {
        case buffer_usage::immutable: return GL_STATIC_DRAW;
        case buffer_usage::statics: return GL_STATIC_DRAW;
        case buffer_usage::dynamic: return GL_DYNAMIC_DRAW;
        case buffer_usage::stream: return GL_STREAM_DRAW;
        default: s_error("unknown buffer_usage\n"); return 0;
        }
    }

    inline GLenum gl::from_texture_filter_mode(texture_filter_mode mode)
    {
        switch (mode)
        {
        case texture_filter_mode::nearest: return GL_NEAREST;
        case texture_filter_mode::linear: return GL_LINEAR;
        case texture_filter_mode::nearest_mipmap_nearest: return GL_NEAREST_MIPMAP_NEAREST;
        case texture_filter_mode::nearest_mipmap_linear: return GL_NEAREST_MIPMAP_LINEAR;
        case texture_filter_mode::linear_mipmap_nearest: return GL_LINEAR_MIPMAP_NEAREST;
        case texture_filter_mode::linear_mipmap_linear: return GL_LINEAR_MIPMAP_LINEAR;
        default: s_error("unknown texture_filter_mode\n"); return 0;
        }
    }

    inline GLenum gl::from_texture_wrap_mode(texture_wrap_mode mode)
    {
        switch (mode)
        {
        case texture_wrap_mode::clamp_to_edge: return GL_CLAMP_TO_EDGE;
        case texture_wrap_mode::repeat: return GL_REPEAT;
        case texture_wrap_mode::mirrored_repeat: return GL_MIRRORED_REPEAT;
        default: s_error("unknown texture_wrap_mode\n"); return 0;
        }
    }

    inline GLenum gl::from_texture_type(texture_type type)
    {
        switch (type)
        {
        case texture_type::texture_2d: return GL_TEXTURE_2D;
        case texture_type::texture_3d: return GL_TEXTURE_3D;
        case texture_type::texture_cube: return GL_TEXTURE_CUBE_MAP;
        default: s_error("unknown texture_type\n"); return 0;
        }
    }

    inline GLenum gl::from_pixel_format_as_internal(pixel_format format)
    {
        switch (format)
        {
        case pixel_format::rgba8: return GL_RGBA8;
        case pixel_format::rgb8: return GL_RGB8;
        case pixel_format::rgba4: return GL_RGBA4;
        case pixel_format::r5g6b5: return GL_RGB5;
        case pixel_format::r5g5b5a1: return GL_RGB5_A1;
        case pixel_format::rgba32f: return GL_RGBA32F;
        case pixel_format::rgba16f: return GL_RGBA16F;
        case pixel_format::l8: return GL_R8;
        case pixel_format::dxt1: return 0x83F1;
        case pixel_format::dxt3: return 0x83F2;
        case pixel_format::dxt5: return 0x83F3;
        case pixel_format::d16: return GL_DEPTH_COMPONENT16;
        case pixel_format::d32: return GL_DEPTH_COMPONENT32F;
        case pixel_format::d24s8: return GL_DEPTH24_STENCIL8;
        case pixel_format::pvrtc2_rgb: return 0x8C01;
        case pixel_format::pvrtc4_rgb: return 0x8C00;
        case pixel_format::pvrtc2_rgba: return 0x8C03;
        case pixel_format::pvrtc4_rgba: return 0x8C02;
        case pixel_format::etc2_rgb8: return GL_COMPRESSED_RGB8_ETC2;
        case pixel_format::etc2_srgb8: return GL_COMPRESSED_SRGB8_ETC2;
        default: s_error("unknown pixel_format\n"); return 0;
        }
    }

    inline GLenum gl::from_pixel_format_as_layout(pixel_format format)
    {
        switch (format)
        {
        case pixel_format::rgba32f: return GL_FLOAT;
        case pixel_format::rgba16f: return GL_HALF_FLOAT;
        case pixel_format::rgba8:
        case pixel_format::rgb8:
        case pixel_format::l8:
            return GL_UNSIGNED_BYTE;
        case pixel_format::r5g5b5a1: return GL_UNSIGNED_SHORT_5_5_5_1;
        case pixel_format::r5g6b5: return GL_UNSIGNED_SHORT_5_6_5;
        case pixel_format::rgba4: return GL_UNSIGNED_SHORT_4_4_4_4;
        case pixel_format::d16: return GL_UNSIGNED_SHORT;
        case pixel_format::d32: return GL_UNSIGNED_INT;
        case pixel_format::d24s8: return GL_UNSIGNED_INT_24_8;
        default: s_error("unknown pixel_format\n"); return 0;
        }
    }

    inline GLenum gl::from_pixel_format_as_format(pixel_format format)
    {
        switch (format) 
        {
        case pixel_format::rgba8:
        case pixel_format::r5g5b5a1:
        case pixel_format::rgba4:
        case pixel_format::rgba32f:
        case pixel_format::rgba16f:
            return GL_RGBA;
        case pixel_format::rgb8:
        case pixel_format::r5g6b5:
            return GL_RGB;
        case pixel_format::l8:
            return GL_RED;
        case pixel_format::d16:
        case pixel_format::d32:
            return GL_DEPTH_COMPONENT;
        case pixel_format::d24s8:
            return GL_DEPTH_STENCIL;
        case pixel_format::dxt1: return 0x83F1;
        case pixel_format::dxt3: return 0x83F2;
        case pixel_format::dxt5: return 0x83F3;
        case pixel_format::pvrtc2_rgb: return 0x8C01;
        case pixel_format::pvrtc4_rgb: return 0x8C00;
        case pixel_format::pvrtc2_rgba: return 0x8C03;
        case pixel_format::pvrtc4_rgba: return 0x8C02;
        case pixel_format::etc2_rgb8: return GL_COMPRESSED_RGB8_ETC2;
        case pixel_format::etc2_srgb8: return GL_COMPRESSED_SRGB8_ETC2;
        default: s_error("unknown pixel_format\n"); return 0;
        }
    }

    inline GLenum gl::from_shader_type(shader_type type)
    {
        switch (type)
        {
        case shader_type::vertex_shader: return GL_VERTEX_SHADER;
        case shader_type::fragment_shader: return GL_FRAGMENT_SHADER;
        default: s_error("unknown shader_type\n"); return 0;
        }
    }

    inline GLint gl::from_vertex_attribute_format_as_count(vertex_attribute_format format)
    {
        switch (format)
        {
        case vertex_attribute_format::float1: return 1;
        case vertex_attribute_format::float2: return 2;
        case vertex_attribute_format::float3: return 3;
        case vertex_attribute_format::float4: return 4;
        case vertex_attribute_format::byte4: return 4;
        case vertex_attribute_format::byte4_normalized: return 4;
        case vertex_attribute_format::unsigned_byte4: return 4;
        case vertex_attribute_format::unsigned_byte4_normalized: return 4;
        case vertex_attribute_format::short2: return 2;
        case vertex_attribute_format::short2_normalized: return 2;
        case vertex_attribute_format::short4: return 4;
        case vertex_attribute_format::short4_normalized: return 4;
        default: s_error("unknown vertex_attribute_format\n"); return 0;
        }
    }

    inline GLenum gl::from_vertex_attribute_format_as_type(vertex_attribute_format format)
    {
        switch (format)
        {
        case vertex_attribute_format::float1: return GL_FLOAT;
        case vertex_attribute_format::float2: return GL_FLOAT;
        case vertex_attribute_format::float3: return GL_FLOAT;
        case vertex_attribute_format::float4: return GL_FLOAT;
        case vertex_attribute_format::byte4: return GL_BYTE;
        case vertex_attribute_format::byte4_normalized: return GL_BYTE;
        case vertex_attribute_format::unsigned_byte4: return GL_UNSIGNED_BYTE;
        case vertex_attribute_format::unsigned_byte4_normalized: return GL_UNSIGNED_BYTE;
        case vertex_attribute_format::short2: return GL_SHORT;
        case vertex_attribute_format::short2_normalized: return GL_SHORT;
        case vertex_attribute_format::short4: return GL_SHORT;
        case vertex_attribute_format::short4_normalized: return GL_SHORT;
        default: s_error("unknown vertex_attribute_format\n"); return 0;
        }
    }

    inline GLboolean gl::from_vertex_attribute_format_as_normalized(vertex_attribute_format format)
    {
        switch (format)
        {
        case vertex_attribute_format::float1: return GL_FALSE;
        case vertex_attribute_format::float2: return GL_FALSE;
        case vertex_attribute_format::float3: return GL_FALSE;
        case vertex_attribute_format::float4: return GL_FALSE;
        case vertex_attribute_format::byte4: return GL_FALSE;
        case vertex_attribute_format::byte4_normalized: return GL_TRUE;
        case vertex_attribute_format::unsigned_byte4: return GL_FALSE;
        case vertex_attribute_format::unsigned_byte4_normalized: return GL_TRUE;
        case vertex_attribute_format::short2: return GL_FALSE;
        case vertex_attribute_format::short2_normalized: return GL_TRUE;
        case vertex_attribute_format::short4: return GL_FALSE;
        case vertex_attribute_format::short4_normalized: return GL_TRUE;
        default: s_error("unknown vertex_attribute_format\n"); return 0;
        }
    }

    inline GLenum gl::from_draw_type(draw_type type)
    {
        switch (type)
        {
        case draw_type::points: return GL_POINTS;
        case draw_type::lines: return GL_LINES;
        case draw_type::line_strip: return GL_LINE_STRIP;
        case draw_type::line_loop: return GL_LINE_LOOP;
        case draw_type::triangles: return GL_TRIANGLES;
        case draw_type::triangle_strip: return GL_TRIANGLE_STRIP;
        case draw_type::triangle_fan: return GL_TRIANGLE_FAN;
        default: s_error("unknown draw_type\n"); return 0;
        }
    }

    inline GLenum gl::from_index_type(index_type type)
    {
        switch (type)
        {
        case index_type::uint16: return GL_UNSIGNED_SHORT;
        case index_type::uint32: return GL_UNSIGNED_INT;
        default: s_error("unknown index_type\n"); return 0;
        }
    }

    inline GLenum gl::from_blend_factor(blend_factor type)
    {
        switch (type)
        {
        case blend_factor::zero: return GL_ZERO;
        case blend_factor::one: return GL_ONE;
        case blend_factor::src_color: return GL_SRC_COLOR;
        case blend_factor::one_minus_src_color: return GL_ONE_MINUS_SRC_COLOR;
        case blend_factor::src_alpha: return GL_SRC_COLOR;
        case blend_factor::one_minus_src_alpha: return GL_ONE_MINUS_SRC_ALPHA;
        case blend_factor::dst_color: return GL_DST_COLOR;
        case blend_factor::one_minus_dst_color: return GL_ONE_MINUS_DST_COLOR;
        case blend_factor::dst_alpha: return GL_DST_ALPHA;
        case blend_factor::one_minux_dst_alpha: return GL_ONE_MINUS_DST_ALPHA;
        case blend_factor::blend_color: return GL_CONSTANT_COLOR;
        case blend_factor::one_minus_blend_color: return GL_ONE_MINUS_CONSTANT_COLOR;
        case blend_factor::blend_alpha: return GL_CONSTANT_ALPHA;
        case blend_factor::one_minus_blend_alpha: return GL_ONE_MINUS_CONSTANT_ALPHA;
        case blend_factor::src_alpha_saturated: return GL_SRC_ALPHA_SATURATE;
        default: s_error("unknown blend_factor\n"); return 0;
        }
    }

    inline GLenum gl::from_blend_operation(blend_operation type)
    {
        switch (type)
        {
        case blend_operation::add: return GL_FUNC_ADD;
        case blend_operation::substract: return GL_FUNC_SUBTRACT;
        case blend_operation::reverse_subtract: return GL_FUNC_REVERSE_SUBTRACT;
        default: s_error("unknown blend_operation\n"); return 0;
        }
    }

    inline GLenum gl::from_compare_func(compare_func func)
    {
        switch (func)
        {
        case compare_func::never: return GL_NEVER;
        case compare_func::less: return GL_LESS;
        case compare_func::less_equal: return GL_LEQUAL;
        case compare_func::greater: return GL_GREATER;
        case compare_func::greater_equal: return GL_GEQUAL;
        case compare_func::equal: return GL_EQUAL;
        case compare_func::not_equal: return GL_NOTEQUAL;
        case compare_func::always: return GL_ALWAYS;
        default: s_error("unknown compare_func\n"); return 0;
        }
    }

    inline GLenum gl::from_stencil_operation(stencil_operation type)
    {
        switch (type)
        {
        case stencil_operation::keep: return GL_KEEP;
        case stencil_operation::zero: return GL_ZERO;
        case stencil_operation::replace: return GL_REPLACE;
        case stencil_operation::increment: return GL_INCR;
        case stencil_operation::increment_wrap: return GL_INCR_WRAP;
        case stencil_operation::decrement: return GL_DECR;
        case stencil_operation::decrement_wrap: return GL_DECR_WRAP;
        case stencil_operation::invert: return GL_INVERT;
        default: s_error("unknown stencil_operation\n"); return 0;
        }
    }

    inline GLenum gl::from_face_side(face_side face)
    {
        switch (face)
        {
        case face_side::front: return GL_FRONT;
        case face_side::back: return GL_BACK;
        case face_side::both: return GL_FRONT_AND_BACK;
        default: s_error("unknown face_side\n"); return 0;
        }
    }
}
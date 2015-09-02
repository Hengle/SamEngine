#pragma once

#include "graphics/core/define.h"
#include "graphics/core/blend_state.h"
#include "graphics/core/rasterizer_state.h"
#include "graphics/core/depth_stencil_state.h"
#include "graphics/config/graphics_config.h"

#include <core/assert.h>
#include <core/log.h>

#include <glad.h>

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
                        break; \
                    case GL_INVALID_ENUM: \
                        sam::log::debug("GL_INVALID_ENUM\n"); \
                        break; \
                    case GL_INVALID_OPERATION: \
                        sam::log::debug("GL_INVALID_OPERATION\n"); \
                        break; \
                    case GL_INVALID_VALUE: \
                        sam::log::debug("GL_INVALID_VALUE\n"); \
                        break; \
                    case GL_INVALID_FRAMEBUFFER_OPERATION: \
                        sam::log::debug("GL_INVALID_FRAMEBUFFER_OPERATION\n"); \
                        break; \
                    case GL_OUT_OF_MEMORY: \
                        sam::log::debug("GL_OUT_OF_MEMORY\n"); \
                        break; \
                    default: \
                        sam::log::debug("UNKNOWN_ERROR\n"); \
                } \
            } \
        } while(0)
#else
#    define s_check_gl_error() ((void)0)
#endif

namespace sam
{
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

        GLuint vertex_buffer;
        GLuint index_buffer;
        GLuint program;

        GLuint texture_2d[graphics_config::max_texture_count];
        GLuint texture_cube[graphics_config::max_texture_count];

        GLuint vertex_attribute[static_cast<uint8>(vertex_attribute::max_count)];
//        gl_vertex_attribute gl_vertex_attribute[static_cast<uint8>(vertex_attribute::max_count)];
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
    };

    inline GLenum gl::from_resource_usage(buffer_usage usage)
    {
        switch (usage)
        {
        case buffer_usage::immutable: return GL_STATIC_DRAW;
        case buffer_usage::statics: return GL_STATIC_DRAW;
        case buffer_usage::dynamic: return GL_DYNAMIC_DRAW;
        case buffer_usage::stream: return GL_STREAM_DRAW;
        default: s_error("unknown buffer_usage"); return 0;
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
        default: s_error("unknown texture_filter_mode"); return 0;
        }
    }

    inline GLenum gl::from_texture_wrap_mode(texture_wrap_mode mode)
    {
        switch (mode)
        {
        case texture_wrap_mode::clamp_to_edge: return GL_CLAMP_TO_EDGE;
        case texture_wrap_mode::repeat: return GL_REPEAT;
        case texture_wrap_mode::mirrored_repeat: return GL_MIRRORED_REPEAT;
        default: s_error("unknown texture_wrap_mode"); return 0;
        }
    }

    inline GLenum gl::from_texture_type(texture_type type)
    {
        switch (type)
        {
        case texture_type::texture_2d: return GL_TEXTURE_2D;
        case texture_type::texture_3d: return GL_TEXTURE_3D;
        case texture_type::texture_cube: return GL_TEXTURE_CUBE_MAP;
        default: s_error("unknown texture_type"); return 0;
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
        default: s_error("unknown pixel_format"); return 0;
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
        default: s_error("unknown pixel_format"); return 0;
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
        default: s_error("unknown pixel_format"); return 0;
        }
    }
}
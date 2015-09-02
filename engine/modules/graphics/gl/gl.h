#pragma once

#include "graphics/core/define.h"
#include "graphics/core/blend_state.h"
#include "graphics/core/rasterizer_state.h"
#include "graphics/core/depth_stencil_state.h"
#include "graphics/config/graphics_config.h"

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
    };

    inline GLenum gl::from_resource_usage(buffer_usage usage)
    {
        switch (usage)
        {
        case buffer_usage::immutable: return GL_STATIC_DRAW;
        case buffer_usage::statics: return GL_STATIC_DRAW;
        case buffer_usage::dynamic: return GL_DYNAMIC_DRAW;
        case buffer_usage::stream: return GL_STREAM_DRAW;
        default: return 0;
        }
    }
}
#pragma once

#include "core/log.h"

#include <glad/glad.h>

#if DEBUG
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
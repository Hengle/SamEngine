#pragma once

#include "GraphicsDefine.h"
#include "Config/GraphicsConfig.h"
#include "State/BlendState.h"
#include "State/DepthStencilState.h"
#include "State/RasterizerState.h"

#include <glad/glad.h>

#include <cstring>

namespace SamEngine
{
    struct OpenGLVertexAttributeParam
    {
        bool Enabled{ false };
        bool Streaming{ false };
        GLuint Index{ 0 };
        GLsizei Stride{ 0 };
        GLint Size{ 0 };
        GLboolean Normalized{ 0 };
        GLvoid *Offset{ nullptr };
        GLenum Type{ 0 };

        bool operator==(const OpenGLVertexAttributeParam &other) const
        {
            return Enabled == other.Enabled &&
                Streaming == other.Streaming &&
                Index == other.Index &&
                Stride == other.Stride &&
                Size == other.Size &&
                Normalized == other.Normalized &&
                Offset == other.Offset &&
                Type == other.Type;
        }

        bool operator!=(const OpenGLVertexAttributeParam &other) const
        {
            return Enabled != other.Enabled ||
                Streaming != other.Streaming ||
                Index != other.Index ||
                Stride != other.Stride ||
                Size != other.Size ||
                Normalized != other.Normalized ||
                Offset != other.Offset ||
                Type != other.Type;
        }
    };

    struct OpenGLRendererCache
    {
        BlendState BlendStateCache;
        DepthStencilState DepthStencilStateCache;
        RasterizerState RasterizerStateCache;

        GLint ViewportX;
        GLint ViewportY;
        GLsizei ViewportWidth;
        GLsizei ViewportHeight;

        GLint ScissorX;
        GLint ScissorY;
        GLsizei ScissorWidth;
        GLsizei ScissorHeight;

        Color BlendColor;

        GLuint VAO;
        GLuint VertexBufferCache;
        GLuint IndexBufferCache;
        IndexAttributeType IndexBufferType{ IndexAttributeType::NONE };
        GLuint ProgramCache;

        GLuint Texture2DCache[GraphicsConfig::MaxTextureCount];
        GLuint TextureCubeCache[GraphicsConfig::MaxTextureCount];

        GLuint VertexAttributePositionCache[static_cast<uint8>(VertexAttributeType::MAX_COUNT)];
        OpenGLVertexAttributeParam VertexAttributeParamCache[static_cast<uint8>(VertexAttributeType::MAX_COUNT)];
    };

    inline GLenum GLEnumFromBufferUsage(BufferUsage usage)
    {
        switch (usage)
        {
        case BufferUsage::IMMUTABLE: return GL_STATIC_DRAW;
        case BufferUsage::STATIC: return GL_STATIC_DRAW;
        case BufferUsage::DYNAMIC: return GL_DYNAMIC_DRAW;
        case BufferUsage::STREAM: return GL_STREAM_DRAW;
        default: s_error("unknown BufferUsage\n"); return 0;
        }
    }

    inline GLenum GLEnumFromTextureFilterMode(TextureFilterMode mode)
    {
        switch (mode)
        {
        case TextureFilterMode::NEAREST: return GL_NEAREST;
        case TextureFilterMode::LINEAR: return GL_LINEAR;
        case TextureFilterMode::NEAREST_MIPMAP_NEAREST: return GL_NEAREST_MIPMAP_NEAREST;
        case TextureFilterMode::NEAREST_MIPMAP_LINEAR: return GL_NEAREST_MIPMAP_LINEAR;
        case TextureFilterMode::LINEAR_MIPMAP_NEAREST: return GL_LINEAR_MIPMAP_NEAREST;
        case TextureFilterMode::LINEAR_MIPMAP_LINEAR: return GL_LINEAR_MIPMAP_LINEAR;
        default: s_error("unknown TextureFilterMode\n"); return 0;
        }
    }

    inline GLenum GLEnumFromTextureWrapMode(TextureWrapMode mode)
    {
        switch (mode)
        {
        case TextureWrapMode::CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
        case TextureWrapMode::REPEAT: return GL_REPEAT;
        case TextureWrapMode::MIRRORED_REPEAT: return GL_MIRRORED_REPEAT;
        default: s_error("unknown TextureWrapMode\n"); return 0;
        }
    }

    inline GLenum GLEnumFromTextureType(TextureType type)
    {
        switch (type)
        {
        case TextureType::TEXTURE_2D: return GL_TEXTURE_2D;
        case TextureType::TEXTURE_3D: return GL_TEXTURE_3D;
        case TextureType::TEXTURE_CUBE: return GL_TEXTURE_CUBE_MAP;
        default: s_error("unknown TextureType\n"); return 0;
        }
    }

    inline GLenum GLEnumFromPixelFormatAsInternal(PixelFormat format)
    {
        switch (format)
        {
        case PixelFormat::RGBA8: return GL_RGBA8;
        case PixelFormat::RGB8: return GL_RGB8;
        case PixelFormat::RGBA4: return GL_RGBA4;
        case PixelFormat::R5G6B5: return GL_RGB5;
        case PixelFormat::R5G5B5A1: return GL_RGB5_A1;
        case PixelFormat::RGBA32F: return GL_RGBA32F;
        case PixelFormat::RGBA16F: return GL_RGBA16F;
        case PixelFormat::L8: return GL_R8;
        case PixelFormat::DXT1: return 0X83F1;
        case PixelFormat::DXT3: return 0X83F2;
        case PixelFormat::DXT5: return 0X83F3;
        case PixelFormat::D16: return GL_DEPTH_COMPONENT16;
        case PixelFormat::D32: return GL_DEPTH_COMPONENT32F;
        case PixelFormat::D24S8: return GL_DEPTH24_STENCIL8;
        case PixelFormat::PVRTC2_RGB: return 0X8C01;
        case PixelFormat::PVRTC4_RGB: return 0X8C00;
        case PixelFormat::PVRTC2_RGBA: return 0X8C03;
        case PixelFormat::PVRTC4_RGBA: return 0X8C02;
        case PixelFormat::ETC2_RGB8: return GL_COMPRESSED_RGB8_ETC2;
        case PixelFormat::ETC2_SRGB8: return GL_COMPRESSED_SRGB8_ETC2;
        default: s_error("unknown PixelFormat\n"); return 0;
        }
    }

    inline GLenum GLEnumFromPixelFormatAsLayout(PixelFormat format)
    {
        switch (format)
        {
        case PixelFormat::RGBA32F: return GL_FLOAT;
        case PixelFormat::RGBA16F: return GL_HALF_FLOAT;
        case PixelFormat::RGBA8:
        case PixelFormat::RGB8:
        case PixelFormat::L8:
            return GL_UNSIGNED_BYTE;
        case PixelFormat::R5G5B5A1: return GL_UNSIGNED_SHORT_5_5_5_1;
        case PixelFormat::R5G6B5: return GL_UNSIGNED_SHORT_5_6_5;
        case PixelFormat::RGBA4: return GL_UNSIGNED_SHORT_4_4_4_4;
        case PixelFormat::D16: return GL_UNSIGNED_SHORT;
        case PixelFormat::D32: return GL_UNSIGNED_INT;
        case PixelFormat::D24S8: return GL_UNSIGNED_INT_24_8;
        default: s_error("unknown PixelFormat\n"); return 0;
        }
    }

    inline GLenum GLEnumFromPixelFormatAsFormat(PixelFormat format)
    {
        switch (format)
        {
        case PixelFormat::RGBA8:
        case PixelFormat::R5G5B5A1:
        case PixelFormat::RGBA4:
        case PixelFormat::RGBA32F:
        case PixelFormat::RGBA16F:
            return GL_RGBA;
        case PixelFormat::RGB8:
        case PixelFormat::R5G6B5:
            return GL_RGB;
        case PixelFormat::L8:
            return GL_RED;
        case PixelFormat::D16:
        case PixelFormat::D32:
            return GL_DEPTH_COMPONENT;
        case PixelFormat::D24S8:
            return GL_DEPTH_STENCIL;
        case PixelFormat::DXT1: return 0X83F1;
        case PixelFormat::DXT3: return 0X83F2;
        case PixelFormat::DXT5: return 0X83F3;
        case PixelFormat::PVRTC2_RGB: return 0X8C01;
        case PixelFormat::PVRTC4_RGB: return 0X8C00;
        case PixelFormat::PVRTC2_RGBA: return 0X8C03;
        case PixelFormat::PVRTC4_RGBA: return 0X8C02;
        case PixelFormat::ETC2_RGB8: return GL_COMPRESSED_RGB8_ETC2;
        case PixelFormat::ETC2_SRGB8: return GL_COMPRESSED_SRGB8_ETC2;
        default: s_error("unknown PixelFormat\n"); return 0;
        }
    }

    inline GLenum GLEnumFromShaderType(ShaderType type)
    {
        switch (type)
        {
        case ShaderType::VERTEX_SHADER: return GL_VERTEX_SHADER;
        case ShaderType::FRAGMENT_SHADER: return GL_FRAGMENT_SHADER;
        default: s_error("unknown ShaderType\n"); return 0;
        }
    }

    inline GLint VertexCountFromVertexAttributeFormat(VertexAttributeFormat format)
    {
        switch (format)
        {
        case VertexAttributeFormat::FLOAT1: return 1;
        case VertexAttributeFormat::FLOAT2: return 2;
        case VertexAttributeFormat::FLOAT3: return 3;
        case VertexAttributeFormat::FLOAT4: return 4;
        case VertexAttributeFormat::BYTE4: return 4;
        case VertexAttributeFormat::BYTE4_NORMALIZED: return 4;
        case VertexAttributeFormat::UNSIGNED_BYTE4: return 4;
        case VertexAttributeFormat::UNSIGNED_BYTE4_NORMALIZED: return 4;
        case VertexAttributeFormat::SHORT2: return 2;
        case VertexAttributeFormat::SHORT2_NORMALIZED: return 2;
        case VertexAttributeFormat::SHORT4: return 4;
        case VertexAttributeFormat::SHORT4_NORMALIZED: return 4;
        default: s_error("unknown VertexAttributeFormat\n"); return 0;
        }
    }

    inline GLenum GLEnumFromVertexAttributeFormat(VertexAttributeFormat format)
    {
        switch (format)
        {
        case VertexAttributeFormat::FLOAT1: return GL_FLOAT;
        case VertexAttributeFormat::FLOAT2: return GL_FLOAT;
        case VertexAttributeFormat::FLOAT3: return GL_FLOAT;
        case VertexAttributeFormat::FLOAT4: return GL_FLOAT;
        case VertexAttributeFormat::BYTE4: return GL_BYTE;
        case VertexAttributeFormat::BYTE4_NORMALIZED: return GL_BYTE;
        case VertexAttributeFormat::UNSIGNED_BYTE4: return GL_UNSIGNED_BYTE;
        case VertexAttributeFormat::UNSIGNED_BYTE4_NORMALIZED: return GL_UNSIGNED_BYTE;
        case VertexAttributeFormat::SHORT2: return GL_SHORT;
        case VertexAttributeFormat::SHORT2_NORMALIZED: return GL_SHORT;
        case VertexAttributeFormat::SHORT4: return GL_SHORT;
        case VertexAttributeFormat::SHORT4_NORMALIZED: return GL_SHORT;
        default: s_error("unknown VertexAttributeFormat\n"); return 0;
        }
    }

    inline GLboolean IsNormalizedFromVertexAttributeFormat(VertexAttributeFormat format)
    {
        switch (format)
        {
        case VertexAttributeFormat::FLOAT1: return GL_FALSE;
        case VertexAttributeFormat::FLOAT2: return GL_FALSE;
        case VertexAttributeFormat::FLOAT3: return GL_FALSE;
        case VertexAttributeFormat::FLOAT4: return GL_FALSE;
        case VertexAttributeFormat::BYTE4: return GL_FALSE;
        case VertexAttributeFormat::BYTE4_NORMALIZED: return GL_TRUE;
        case VertexAttributeFormat::UNSIGNED_BYTE4: return GL_FALSE;
        case VertexAttributeFormat::UNSIGNED_BYTE4_NORMALIZED: return GL_TRUE;
        case VertexAttributeFormat::SHORT2: return GL_FALSE;
        case VertexAttributeFormat::SHORT2_NORMALIZED: return GL_TRUE;
        case VertexAttributeFormat::SHORT4: return GL_FALSE;
        case VertexAttributeFormat::SHORT4_NORMALIZED: return GL_TRUE;
        default: s_error("unknown VertexAttributeFormat\n"); return 0;
        }
    }

    inline GLenum GLEnumFromDrawType(DrawType type)
    {
        switch (type)
        {
        case DrawType::POINTS: return GL_POINTS;
        case DrawType::LINES: return GL_LINES;
        case DrawType::LINE_STRIP: return GL_LINE_STRIP;
        case DrawType::LINE_LOOP: return GL_LINE_LOOP;
        case DrawType::TRIANGLES: return GL_TRIANGLES;
        case DrawType::TRIANGLE_STRIP: return GL_TRIANGLE_STRIP;
        case DrawType::TRIANGLE_FAN: return GL_TRIANGLE_FAN;
        default: s_error("unknown DrawType\n"); return 0;
        }
    }

    inline GLenum GLEnumFromIndexAttributeType(IndexAttributeType type)
    {
        switch (type)
        {
        case IndexAttributeType::UINT16: return GL_UNSIGNED_SHORT;
        case IndexAttributeType::UINT32: return GL_UNSIGNED_INT;
        default: s_error("unknown IndexAttributeType\n"); return 0;
        }
    }

    inline GLenum GLEnumFromBlendFactor(BlendFactor type)
    {
        switch (type)
        {
        case BlendFactor::ZERO: return GL_ZERO;
        case BlendFactor::ONE: return GL_ONE;
        case BlendFactor::SRC_COLOR: return GL_SRC_COLOR;
        case BlendFactor::ONE_MINUS_SRC_COLOR: return GL_ONE_MINUS_SRC_COLOR;
        case BlendFactor::SRC_ALPHA: return GL_SRC_COLOR;
        case BlendFactor::ONE_MINUS_SRC_ALPHA: return GL_ONE_MINUS_SRC_ALPHA;
        case BlendFactor::DST_COLOR: return GL_DST_COLOR;
        case BlendFactor::ONE_MINUS_DST_COLOR: return GL_ONE_MINUS_DST_COLOR;
        case BlendFactor::DST_ALPHA: return GL_DST_ALPHA;
        case BlendFactor::ONE_MINUX_DST_ALPHA: return GL_ONE_MINUS_DST_ALPHA;
        case BlendFactor::BLEND_COLOR: return GL_CONSTANT_COLOR;
        case BlendFactor::ONE_MINUS_BLEND_COLOR: return GL_ONE_MINUS_CONSTANT_COLOR;
        case BlendFactor::BLEND_ALPHA: return GL_CONSTANT_ALPHA;
        case BlendFactor::ONE_MINUS_BLEND_ALPHA: return GL_ONE_MINUS_CONSTANT_ALPHA;
        case BlendFactor::SRC_ALPHA_SATURATED: return GL_SRC_ALPHA_SATURATE;
        default: s_error("unknown BlendFactor\n"); return 0;
        }
    }

    inline GLenum GLEnumFromBlendOperation(BlendOperation type)
    {
        switch (type)
        {
        case BlendOperation::ADD: return GL_FUNC_ADD;
        case BlendOperation::SUBSTRACT: return GL_FUNC_SUBTRACT;
        case BlendOperation::REVERSE_SUBTRACT: return GL_FUNC_REVERSE_SUBTRACT;
        default: s_error("unknown BlendOperation\n"); return 0;
        }
    }

    inline GLenum GLEnumFromCompareFunction(CompareFunction func)
    {
        switch (func)
        {
        case CompareFunction::NEVER: return GL_NEVER;
        case CompareFunction::LESS: return GL_LESS;
        case CompareFunction::LESS_EQUAL: return GL_LEQUAL;
        case CompareFunction::GREATER: return GL_GREATER;
        case CompareFunction::GREATER_EQUAL: return GL_GEQUAL;
        case CompareFunction::EQUAL: return GL_EQUAL;
        case CompareFunction::NOT_EQUAL: return GL_NOTEQUAL;
        case CompareFunction::ALWAYS: return GL_ALWAYS;
        default: s_error("unknown CompareFunction\n"); return 0;
        }
    }

    inline GLenum GLEnumFromStencilOperation(StencilOperation type)
    {
        switch (type)
        {
        case StencilOperation::KEEP: return GL_KEEP;
        case StencilOperation::ZERO: return GL_ZERO;
        case StencilOperation::REPLACE: return GL_REPLACE;
        case StencilOperation::INCREMENT: return GL_INCR;
        case StencilOperation::INCREMENT_WRAP: return GL_INCR_WRAP;
        case StencilOperation::DECREMENT: return GL_DECR;
        case StencilOperation::DECREMENT_WRAP: return GL_DECR_WRAP;
        case StencilOperation::INVERT: return GL_INVERT;
        default: s_error("unknown StencilOperation\n"); return 0;
        }
    }

    inline GLenum GLEnumFromFaceSide(FaceSide face)
    {
        switch (face)
        {
        case FaceSide::FRONT: return GL_FRONT;
        case FaceSide::BACK: return GL_BACK;
        case FaceSide::BOTH: return GL_FRONT_AND_BACK;
        default: s_error("unknown FaceSide\n"); return 0;
        }
    }
}
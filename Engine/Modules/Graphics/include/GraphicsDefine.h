#pragma once

#include <CoreModule.h>
#include <ResourceModule.h>

#include <glm.hpp>

namespace SamEngine
{
    typedef glm::vec4 Color;

    typedef glm::highp_ivec4 IntColor;

    enum class GraphicsType : uint8
    {
        NONE,
        OPENGL2,
        OPENGL3,
        OPENGL4,
        OPENGLES1,
        OPENGLES2,
#if SAM_WINDOWS
        D3D9,
        D3D10,
        D3D11,
#endif
        COUNT,
    };

    enum class GraphicsResourceType : uint16
    {
        VERTEX_BUFFER,
        INDEX_BUFFER,
        SHADER,
        PROGRAM,
        TEXTURE,

        COUNT,
    };

    enum class BlendFactor : uint8
    {
        ZERO,
        ONE,

        SRC_COLOR,
        ONE_MINUS_SRC_COLOR,

        SRC_ALPHA,
        ONE_MINUS_SRC_ALPHA,

        DST_COLOR,
        ONE_MINUS_DST_COLOR,

        DST_ALPHA,
        ONE_MINUX_DST_ALPHA,

        BLEND_COLOR,
        ONE_MINUS_BLEND_COLOR,

        BLEND_ALPHA,
        ONE_MINUS_BLEND_ALPHA,

        SRC_ALPHA_SATURATED,
    };

    enum class BlendOperation : uint8
    {
        ADD,
        SUBSTRACT,
        REVERSE_SUBTRACT,
    };

    enum class TextureType : uint8
    {
        TEXTURE_2D,
        TEXTURE_3D,
        TEXTURE_CUBE,
    };

    enum class BufferUsage : uint8
    {
        IMMUTABLE,
        STATIC,
        DYNAMIC,
        STREAM,
    };

    enum class CompareFunction : uint8
    {
        NEVER,
        LESS,
        LESS_EQUAL,
        GREATER,
        GREATER_EQUAL,
        EQUAL,
        NOT_EQUAL,
        ALWAYS,
    };

    enum class StencilOperation : uint8
    {
        KEEP,
        ZERO,
        REPLACE,
        INCREMENT,
        INCREMENT_WRAP,
        DECREMENT,
        DECREMENT_WRAP,
        INVERT,
    };

    enum class FaceSide : uint8
    {
        FRONT,
        BACK,
        BOTH
    };

    enum class IndexAttributeType : uint8
    {
        NONE,
        UINT16,
        UINT32,
    };

    static int32 SizeOfIndexAttributeType(IndexAttributeType type)
    {
        auto size = 0;
        switch (type)
        {
        case IndexAttributeType::NONE:
            size = 0;
            break;
        case IndexAttributeType::UINT16:
            size = 2;
            break;
        case IndexAttributeType::UINT32:
            size = 4;
            break;
        default:
            break;
        }
        return size;
    }

    enum class VertexAttributeType : uint8
    {
        POSITION,
        TEXCOORD0,
        TEXCOORD1,
        TEXCORRD2,
        TEXCORRD3,
        COLOR0,
        COLOR1,
        NORMAL,
        TANGENT,
        BINORMAL,
        WEIGHTS,
        INDICES,
        INSTANCE0,
        INSTANCE1,
        INSTANCE2,
        INSTANCE3,

        MAX_COUNT,
    };

    static const char *VertexAttributeNameFromType(VertexAttributeType attribute)
    {
        switch (attribute)
        {
        case VertexAttributeType::POSITION: return "aPosition";
        case VertexAttributeType::TEXCOORD0: return "aTexcoord0";
        case VertexAttributeType::TEXCOORD1: return "aTexcoord1";
        case VertexAttributeType::TEXCORRD2: return "aTexcorrd2";
        case VertexAttributeType::TEXCORRD3: return "aTexcorrd3";
        case VertexAttributeType::COLOR0: return "aColor0";
        case VertexAttributeType::COLOR1: return "aColor1";
        case VertexAttributeType::NORMAL: return "aNormal";
        case VertexAttributeType::TANGENT: return "aTangent";
        case VertexAttributeType::BINORMAL: return "aBinormal";
        case VertexAttributeType::WEIGHTS: return "aWeights";
        case VertexAttributeType::INDICES: return "aIndices";
        case VertexAttributeType::INSTANCE0: return "aInstance0";
        case VertexAttributeType::INSTANCE1: return "aInstance1";
        case VertexAttributeType::INSTANCE2: return "aInstance2";
        case VertexAttributeType::INSTANCE3: return "aInstance3";
        default: s_error("unknown VertexAttributeType\n"); return nullptr;
        }
    }

    enum class VertexAttributeFormat : uint8
    {
        FLOAT1,
        FLOAT2,
        FLOAT3,
        FLOAT4,
        BYTE4,
        BYTE4_NORMALIZED,
        UNSIGNED_BYTE4,
        UNSIGNED_BYTE4_NORMALIZED,
        SHORT2,
        SHORT2_NORMALIZED,
        SHORT4,
        SHORT4_NORMALIZED,
    };

    static int32 SizeOfVertexAttributeFormat(VertexAttributeFormat format)
    {
        switch (format)
        {
        case VertexAttributeFormat::FLOAT1: return 4;
        case VertexAttributeFormat::FLOAT2: return 8;
        case VertexAttributeFormat::FLOAT3: return 12;
        case VertexAttributeFormat::FLOAT4: return 16;
        case VertexAttributeFormat::BYTE4: return 4;
        case VertexAttributeFormat::BYTE4_NORMALIZED: return 4;
        case VertexAttributeFormat::UNSIGNED_BYTE4: return 4;
        case VertexAttributeFormat::UNSIGNED_BYTE4_NORMALIZED: return 4;
        case VertexAttributeFormat::SHORT2: return 4;
        case VertexAttributeFormat::SHORT2_NORMALIZED: return 4;
        case VertexAttributeFormat::SHORT4: return 8;
        case VertexAttributeFormat::SHORT4_NORMALIZED: return 8;
        default: s_error("unknown VertexAttributeFormat\n"); return 0;
        }
    }

    enum class UniformAttributeFormat : uint8
    {
        INT,
        BOOL,
        VECTOR1,
        VECTOR2,
        VECTOR3,
        VECTOR4,
        MATRIX2,
        MATRIX3,
        MATRIX4,
        TEXTURE,
    };

    static int32 SizeOfUniformAttributeFormat(UniformAttributeFormat format)
    {
        switch (format)
        {
        case UniformAttributeFormat::INT: return sizeof(int32);
        case UniformAttributeFormat::BOOL: return sizeof(int32);
        case UniformAttributeFormat::VECTOR1: return sizeof(float32);
        case UniformAttributeFormat::VECTOR2: return 2 * sizeof(float32);
        case UniformAttributeFormat::VECTOR3: return 3 * sizeof(float32);
        case UniformAttributeFormat::VECTOR4: return 4 * sizeof(float32);
        case UniformAttributeFormat::MATRIX2: return 2 * 2 * sizeof(int32);
        case UniformAttributeFormat::MATRIX3: return 3 * 3 * sizeof(int32);
        case UniformAttributeFormat::MATRIX4: return 4 * 4 * sizeof(int32);
        case UniformAttributeFormat::TEXTURE: return sizeof(ResourceID);
        default: s_error("unknown UniformAttributeFormat\n"); return 0;
        }
    }

    enum class DrawType : uint8
    {
        POINTS,
        LINES,
        LINE_STRIP,
        LINE_LOOP,
        TRIANGLES,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
    };

    enum class TextureWrapMode : uint8
    {
        CLAMP_TO_EDGE,
        REPEAT,
        MIRRORED_REPEAT,
    };

    enum class TextureFilterMode : uint8
    {
        NEAREST,
        LINEAR,
        NEAREST_MIPMAP_NEAREST,
        NEAREST_MIPMAP_LINEAR,
        LINEAR_MIPMAP_NEAREST,
        LINEAR_MIPMAP_LINEAR,
    };

    static bool IsTextureFilterModeUseMipmap(TextureFilterMode mode)
    {
        return !(mode == TextureFilterMode::NEAREST || mode == TextureFilterMode::LINEAR);
    }

    enum class ShaderType : uint8
    {
        VERTEX_SHADER,
        FRAGMENT_SHADER,
    };

    enum class ClearType : uint8
    {
        NONE = 0,
        COLOR = 1 << 0,
        DEPTH = 1 << 1,
        STENCIL = 1 << 2,

        DEPTH_AND_STENCIL = DEPTH | STENCIL,
        ALL = COLOR | DEPTH_AND_STENCIL,
    };
}
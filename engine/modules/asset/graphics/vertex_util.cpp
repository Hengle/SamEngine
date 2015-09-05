#include "vertex_util.h"

#include <core/assert.h>

#define CAST_PTR(type, value) reinterpret_cast<type *>(value)

namespace sam
{
    uchar *vertex_util::write(uchar *buffer, vertex_attribute_format format, float32 x)
    {
        s_assert(buffer != nullptr && format == vertex_attribute_format::float1);
        auto pointer = CAST_PTR(float32, buffer);
        *pointer++ = x;
        return CAST_PTR(uchar, pointer);
    }

    uchar *vertex_util::write(uchar *buffer, vertex_attribute_format format, float32 x, float32 y)
    {
        s_assert(buffer != nullptr);
        switch (format)
        {
        case vertex_attribute_format::float2:
        {
            auto pointer = CAST_PTR(float32, buffer);
            *pointer++ = x;
            *pointer++ = y;
            return CAST_PTR(uchar, pointer);
        }
        case vertex_attribute_format::short2:
        {
            glm::i16vec2 packed(glm::clamp(glm::vec2(x, y), -32768.0f, 32767.0f));
            auto pointer = CAST_PTR(int16, buffer);
            *pointer++ = packed.x;
            *pointer++ = packed.y;
            return CAST_PTR(uchar, pointer);
        }
        case vertex_attribute_format::short2_normalized:
        {
            glm::i16vec2 packed(glm::round(glm::clamp(glm::vec2(x, y), -1.0f, 1.0f) * 32767.0f));
            auto pointer = CAST_PTR(int16, buffer);
            *pointer++ = packed.x;
            *pointer++ = packed.y;
            return CAST_PTR(uchar, pointer);
        }
        default:
            s_error("unknown format\n");
            return nullptr;
        }
    }

    uchar *vertex_util::write(uchar *buffer, vertex_attribute_format format, float32 x, float32 y, float32 z)
    {
        s_assert(buffer != nullptr);
        switch (format)
        {
        case vertex_attribute_format::float3:
        {
            auto pointer = CAST_PTR(float32, buffer);
            *pointer++ = x;
            *pointer++ = y;
            *pointer++ = z;
            return CAST_PTR(uchar, pointer);
        }
        default:
            return write(buffer, format, x, y, z, 0.0f);
        }
    }

    uchar *vertex_util::write(uchar *buffer, vertex_attribute_format format, float32 x, float32 y, float32 z, float32 w)
    {
        s_assert(buffer != nullptr);
        switch (format)
        {
        case vertex_attribute_format::float4:
        {
            auto pointer = CAST_PTR(float32, buffer);
            *pointer++ = x;
            *pointer++ = y;
            *pointer++ = z;
            *pointer++ = w;
            return CAST_PTR(uchar, pointer);
        }
        case vertex_attribute_format::short4:
        {
            glm::i16vec4 packed(glm::clamp(glm::vec4(x, y, z, w), -32768.0f, 32767.0f));
            auto pointer = CAST_PTR(int16, buffer);
            *pointer++ = packed.x;
            *pointer++ = packed.y;
            *pointer++ = packed.z;
            *pointer++ = packed.w;
            return CAST_PTR(uchar, pointer);
        }
        case vertex_attribute_format::short4_normalized:
        {
            glm::i16vec4 packed(glm::round(glm::clamp(glm::vec4(x, y, z, w), -1.0f, 1.0f) * 32767.0f));
            auto pointer = CAST_PTR(int16, buffer);
            *pointer++ = packed.x;
            *pointer++ = packed.y;
            *pointer++ = packed.z;
            *pointer++ = packed.w;
            return CAST_PTR(uchar, pointer);
        }
        case vertex_attribute_format::unsigned_byte4:
        {
            glm::u8vec4 packed(glm::clamp(glm::vec4(x, y, z, w), 0.0f, 255.0f));
            *buffer++ = packed.x;
            *buffer++ = packed.y;
            *buffer++ = packed.z;
            *buffer++ = packed.w;
            return buffer;
        }
        case vertex_attribute_format::unsigned_byte4_normalized:
        {
            glm::u8vec4 packed(glm::round(glm::clamp(glm::vec4(x, y, z, w), 0.0f, 1.0f) * 255.0f));
            *buffer++ = packed.x;
            *buffer++ = packed.y;
            *buffer++ = packed.z;
            *buffer++ = packed.w;
            return buffer;
        }
        case vertex_attribute_format::byte4:
        {
            glm::i8vec4 packed(glm::clamp(glm::vec4(x, y, z, w), -128.0f, 127.0f));
            auto pointer = CAST_PTR(int8, buffer);
            *pointer++ = packed.x;
            *pointer++ = packed.y;
            *pointer++ = packed.z;
            *pointer++ = packed.w;
            return CAST_PTR(uchar, pointer);
        }
        case vertex_attribute_format::byte4_normalized:
        {
            glm::i8vec4 packed(glm::round(glm::clamp(glm::vec4(x, y, z, w), -1.0f, 1.0f) * 127.0f));
            auto pointer = CAST_PTR(int8, buffer);
            *pointer++ = packed.x;
            *pointer++ = packed.y;
            *pointer++ = packed.z;
            *pointer++ = packed.w;
            return CAST_PTR(uchar, pointer);
        }
        default:
            s_error("unknown format\n");
            return nullptr;
        }
    }
}
#pragma once

#include <core/types.h>
#include <graphics/core/define.h>

namespace sam
{
    class vertex_util
    {
    public:
        static uchar *write(uchar *buffer, vertex_attribute_format format, float32 x);

        static uchar *write(uchar *buffer, vertex_attribute_format format, float32 x, float32 y);

        static uchar *write(uchar *buffer, vertex_attribute_format format, float32 x, float32 y, float32 z);

        static uchar *write(uchar *buffer, vertex_attribute_format format, float32 x, float32 y, float32 z, float32 w);
    };
}
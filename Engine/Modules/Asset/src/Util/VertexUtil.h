#pragma once

#include <GraphicsModule.h>

namespace SamEngine
{
    class VertexUtil
    {
    public:
        static uchar *Write(uchar *buffer, VertexAttributeFormat format, float32 x);

        static uchar *Write(uchar *buffer, VertexAttributeFormat format, float32 x, float32 y);

        static uchar *Write(uchar *buffer, VertexAttributeFormat format, float32 x, float32 y, float32 z);

        static uchar *Write(uchar *buffer, VertexAttributeFormat format, float32 x, float32 y, float32 z, float32 w);
    };
}
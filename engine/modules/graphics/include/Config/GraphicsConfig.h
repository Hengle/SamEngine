#pragma once

#include "GraphicsDefine.h"

namespace SamEngine
{
    struct GRAPHICS_API GraphicsConfig
    {
        static const int32 CubeTextureFaceCount = 6;

        static const int32 MaxTextureMipMapCount = 12;

        static const int32 MaxTextureCount = 16;

        static const int32 MaxUniformNodeCount = 16;

        static const int32 MaxVertexNodeCount = 16;

        static const int32 MaxStreamVertexBufferCount = 2;

        GraphicsType Type{ GraphicsType::OPENGL3 };

        int32 RegistrySize{ 256 };

        int32 VertexBufferPoolSize{ 128 };

        int32 IndexBufferPoolSize{ 128 };

        int32 UniformBufferPoolSize{ 128 };

        int32 ShaderPoolSize{ 256 };

        int32 ProgramPoolSize{ 128 };

        int32 TexturePoolSize{ 128 };

        int32 DrawCallPoolSize{ 128 };
    };
}
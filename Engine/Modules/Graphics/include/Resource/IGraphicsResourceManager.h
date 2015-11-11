#pragma once

#include <ResourceModule.h>

namespace SamEngine
{
    struct TextureConfig;
    struct ProgramConfig;
    struct ShaderConfig;
    struct IndexBufferConfig;
    struct VertexBufferConfig;

    class GRAPHICS_API IGraphicsResourceManager : public ResourceManager
    {
    public:
        virtual ~IGraphicsResourceManager() {}

        virtual void Initialize(const GraphicsConfig &config) = 0;

        virtual ResourceID Create(const VertexBufferConfig &config, DataPtr data) = 0;

        virtual ResourceID Create(const IndexBufferConfig &config, DataPtr data) = 0;

        virtual ResourceID Create(const ShaderConfig &config, DataPtr data) = 0;

        virtual ResourceID Create(const ProgramConfig &config, DataPtr data) = 0;

        virtual ResourceID Create(const TextureConfig &config, DataPtr data) = 0;

        virtual VertexBufferConfig &GetVertexBufferConfig(ResourceID id) = 0;

        virtual IndexBufferConfig &GetIndexBufferConfig(ResourceID id) = 0;

        virtual ShaderConfig &GetShaderConfig(ResourceID id) = 0;

        virtual ProgramConfig &GetProgramConfig(ResourceID id) = 0;

        virtual TextureConfig &GetTextureConfig(ResourceID id) = 0;

        virtual void SetProgramUniformData(ResourceID id, int32 index, const void *buffer, size_t size) = 0;

        virtual void Destroy(ResourceLabel label) = 0;

        virtual void Destroy(ResourceID id) = 0;
    };
}
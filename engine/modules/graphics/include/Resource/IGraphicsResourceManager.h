#pragma once

#include <ResourceModule.h>

namespace SamEngine
{
    struct TextureConfig;
    struct ProgramConfig;
    struct ShaderConfig;
    struct UniformBufferConfig;
    struct IndexBufferConfig;
    struct VertexBufferConfig;
    struct DrawCallConfig;

    class GRAPHICS_API IGraphicsResourceManager : public ResourceManager
    {
    public:
        virtual ~IGraphicsResourceManager() {}

        virtual void Initialize(const GraphicsConfig &config) = 0;

        virtual ResourceID Create(const VertexBufferConfig &config, DataPtr data) = 0;

        virtual ResourceID Create(const IndexBufferConfig &config, DataPtr data) = 0;

        virtual ResourceID Create(const UniformBufferConfig &config, DataPtr data) = 0;

        virtual ResourceID Create(const ShaderConfig &config, DataPtr data) = 0;

        virtual ResourceID Create(const ProgramConfig &config, DataPtr data) = 0;

        virtual ResourceID Create(const TextureConfig &config, DataPtr data) = 0;

        virtual ResourceID Create(const DrawCallConfig &config, DataPtr data) = 0;

        virtual void Destroy(ResourceLabel label) = 0;

        virtual void Destroy(ResourceID id) = 0;
    };
}
#pragma once

#include "OpenGL/Resource/OpenGLResource.h"
#include "OpenGL/Resource/OpenGLVertexBufferFactory.h"
#include "OpenGL/Resource/OpenGLIndexBufferFactory.h"
#include "OpenGL/Resource/OpenGLShaderFactory.h"
#include "OpenGL/Resource/OpenGLProgramFactory.h"
#include "OpenGL/Resource/OpenGLTextureFactory.h"

#include "Config/GraphicsConfig.h"
#include "Resource/IGraphicsResourceManager.h"

namespace SamEngine
{
    class OpenGLVertexBufferPool : public ResourcePool<OpenGLVertexBuffer, VertexBufferConfig> {};
    class OpenGLIndexBufferPool : public ResourcePool<OpenGLIndexBuffer, IndexBufferConfig> {};
    class OpenGLShaderPool : public ResourcePool<OpenGLShader, ShaderConfig> {};
    class OpenGLProgramPool : public ResourcePool<OpenGLProgram, ProgramConfig> {};
    class OpenGLTexturePool : public ResourcePool<OpenGLTexture, TextureConfig> {};

    class OpenGLGraphicsResourceManager : public IGraphicsResourceManager
    {
    public:
        static OpenGLGraphicsResourceManager &Get();

        void Initialize(const GraphicsConfig &config) override;

        void Finalize() override;

        ResourceID Create(const VertexBufferConfig &config, DataPtr data) override;

        ResourceID Create(const IndexBufferConfig &config, DataPtr data) override;

        ResourceID Create(const ShaderConfig &config, DataPtr data) override;

        ResourceID Create(const ProgramConfig &config, DataPtr data) override;

        ResourceID Create(const TextureConfig &config, DataPtr data) override;

        VertexBufferConfig &GetVertexBufferConfig(ResourceID id) override;

        IndexBufferConfig &GetIndexBufferConfig(ResourceID id) override;

        ShaderConfig &GetShaderConfig(ResourceID id) override;

        ProgramConfig &GetProgramConfig(ResourceID id) override;

        TextureConfig &GetTextureConfig(ResourceID id) override;

        void SetProgramUniformData(ResourceID id, int32 index, const void *buffer, size_t size) override;

        void Destroy(ResourceID id) override;

        OpenGLVertexBuffer *GetVertexBuffer(ResourceID id);

        OpenGLIndexBuffer *GetIndexBuffer(ResourceID id);

        OpenGLShader *GetShader(ResourceID id);

        OpenGLProgram *GetProgram(ResourceID id);

        OpenGLTexture *GetTexture(ResourceID id);

    private:
        static OpenGLGraphicsResourceManager *sInstance;

        OpenGLVertexBufferPool mVertexBufferPool;
        OpenGLIndexBufferPool mIndexBufferPool;
        OpenGLShaderPool mShaderPool;
        OpenGLProgramPool mProgramPool;
        OpenGLTexturePool mTexturePool;

        OpenGLVertexBufferFactory mVertexBufferFactory;
        OpenGLIndexBufferFactory mIndexBufferFactory;
        OpenGLShaderFactory mShaderFactory;
        OpenGLProgramFactory mProgramFactory;
        OpenGLTextureFactory mTextureFactory;
    };
}
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

        virtual void Initialize(const GraphicsConfig &config) override;

        virtual void Finalize() override;

        virtual ResourceID Create(const VertexBufferConfig &config, DataPtr data) override;

        virtual ResourceID Create(const IndexBufferConfig &config, DataPtr data) override;

        virtual ResourceID Create(const ShaderConfig &config, DataPtr data) override;

        virtual ResourceID Create(const ProgramConfig &config, DataPtr data) override;

        virtual ResourceID Create(const TextureConfig &config, DataPtr data) override;

        virtual VertexBufferConfig &GetVertexBufferConfig(ResourceID id) override;

        virtual IndexBufferConfig &GetIndexBufferConfig(ResourceID id) override;

        virtual ShaderConfig &GetShaderConfig(ResourceID id) override;

        virtual ProgramConfig &GetProgramConfig(ResourceID id) override;

        virtual TextureConfig &GetTextureConfig(ResourceID id) override;

        virtual void SetProgramUniformData(ResourceID id, int32 index, const void *buffer, size_t size) override;

        virtual void Destroy(ResourceID id) override;

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
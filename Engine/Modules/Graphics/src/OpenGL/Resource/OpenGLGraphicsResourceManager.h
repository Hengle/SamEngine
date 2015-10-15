#pragma once

#include "OpenGL/Resource/OpenGLResource.h"
#include "OpenGL/Resource/OpenGLVertexBufferFactory.h"
#include "OpenGL/Resource/OpenGLIndexBufferFactory.h"
#include "OpenGL/Resource/OpenGLUniformBufferFactory.h"
#include "OpenGL/Resource/OpenGLShaderFactory.h"
#include "OpenGL/Resource/OpenGLProgramFactory.h"
#include "OpenGL/Resource/OpenGLTextureFactory.h"
#include "OpenGL/Resource/OpenGLDrawCallFactory.h"

#include "Config/GraphicsConfig.h"
#include "Resource/IGraphicsResourceManager.h"

namespace SamEngine
{
    class OpenGLVertexBufferPool : public ResourcePool<OpenGLVertexBuffer, VertexBufferConfig> {};
    class OpenGLIndexBufferPool : public ResourcePool<OpenGLIndexBuffer, IndexBufferConfig> {};
    class OpenGLUniformBufferPool : public ResourcePool<OpenGLUniformBuffer, UniformBufferConfig> {};
    class OpenGLShaderPool : public ResourcePool<OpenGLShader, ShaderConfig> {};
    class OpenGLProgramPool : public ResourcePool<OpenGLProgram, ProgramConfig> {};
    class OpenGLTexturePool : public ResourcePool<OpenGLTexture, TextureConfig> {};
    class OpenGLDrawCallPool : public ResourcePool<OpenGLDrawCall, DrawCallConfig> {};

    class OpenGLGraphicsResourceManager : public IGraphicsResourceManager
    {
    public:
        static OpenGLGraphicsResourceManager &Get();

        void Initialize(const GraphicsConfig &config) override;

        void Finalize() override;

        ResourceID Create(const VertexBufferConfig &config, DataPtr data) override;

        ResourceID Create(const IndexBufferConfig &config, DataPtr data) override;

        ResourceID Create(const UniformBufferConfig &config, DataPtr data) override;

        ResourceID Create(const ShaderConfig &config, DataPtr data) override;

        ResourceID Create(const ProgramConfig &config, DataPtr data) override;

        ResourceID Create(const TextureConfig &config, DataPtr data) override;

        ResourceID Create(const DrawCallConfig &config, DataPtr data) override;

        void Destroy(ResourceLabel label) override;

        void Destroy(ResourceID id) override;

        OpenGLVertexBuffer *GetVertexBuffer(ResourceID id);

        OpenGLIndexBuffer *GetIndexBuffer(ResourceID id);

        OpenGLUniformBuffer *GetUniformBuffer(ResourceID id);

        OpenGLShader *GetShader(ResourceID id);

        OpenGLProgram *GetProgram(ResourceID id);

        OpenGLTexture *GetTexture(ResourceID id);

        OpenGLDrawCall *GetDrawCall(ResourceID id);

    private:
        static OpenGLGraphicsResourceManager *sInstance;

        OpenGLVertexBufferPool mVertexBufferPool;
        OpenGLIndexBufferPool mIndexBufferPool;
        OpenGLUniformBufferPool mUniformBufferPool;
        OpenGLShaderPool mShaderPool;
        OpenGLProgramPool mProgramPool;
        OpenGLTexturePool mTexturePool;
        OpenGLDrawCallPool mDrawCallPool;

        OpenGLVertexBufferFactory mVertexBufferFactory;
        OpenGLIndexBufferFactory mIndexBufferFactory;
        OpenGLUniformBufferFactory mUniformBufferFactory;
        OpenGLShaderFactory mShaderFactory;
        OpenGLProgramFactory mProgramFactory;
        OpenGLTextureFactory mTextureFactory;
        OpenGLDrawCallFactory mDrawCallFactory;
    };
}
#include "OpenGLGraphicsResourceManager.h"

namespace SamEngine
{
    OpenGLGraphicsResourceManager *OpenGLGraphicsResourceManager::sInstance = nullptr;

    OpenGLGraphicsResourceManager &OpenGLGraphicsResourceManager::Get()
    {
        s_assert(sInstance != nullptr);
        return *sInstance;
    }

    void OpenGLGraphicsResourceManager::Initialize(const GraphicsConfig &config)
    {
        mVertexBufferPool.Initialize(config.VertexBufferPoolSize, static_cast<uint16>(GraphicsResourceType::VERTEX_BUFFER));
        mIndexBufferPool.Initialize(config.IndexBufferPoolSize, static_cast<uint16>(GraphicsResourceType::INDEX_BUFFER));
        mShaderPool.Initialize(config.ShaderPoolSize, static_cast<uint16>(GraphicsResourceType::SHADER));
        mProgramPool.Initialize(config.ProgramPoolSize, static_cast<uint16>(GraphicsResourceType::PROGRAM));
        mTexturePool.Initialize(config.TexturePoolSize, static_cast<uint16>(GraphicsResourceType::TEXTURE));
        ResourceManager::Initialize(config.RegistrySize);
        sInstance = this;
    }

    void OpenGLGraphicsResourceManager::Finalize()
    {
        mVertexBufferPool.Finalize();
        mIndexBufferPool.Finalize();
        mShaderPool.Finalize();
        mProgramPool.Finalize();
        mTexturePool.Finalize();
        ResourceManager::Finalize();
        sInstance = nullptr;
    }

    ResourceID OpenGLGraphicsResourceManager::Create(const VertexBufferConfig &config, DataPtr data)
    {
        auto id = mRegistry.Find(config.Name);
        if (id == InvalidResourceID)
        {
            id = mVertexBufferPool.Create();
            mRegistry.Add(config.Name, id, mLabelStack.top());
            auto &vertexBuffer = mVertexBufferPool.Get(id, config);
            vertexBuffer.Status = mVertexBufferFactory.Create(vertexBuffer, data);
            s_assert(vertexBuffer.Status != ResourceStatus::INVALID);
        }
        return id;
    }

    ResourceID OpenGLGraphicsResourceManager::Create(const IndexBufferConfig &config, DataPtr data)
    {
        auto id = mRegistry.Find(config.Name);
        if (id == InvalidResourceID)
        {
            id = mIndexBufferPool.Create();
            mRegistry.Add(config.Name, id, mLabelStack.top());
            auto &indexBuffer = mIndexBufferPool.Get(id, config);
            indexBuffer.Status = mIndexBufferFactory.Create(indexBuffer, data);
            s_assert(indexBuffer.Status != ResourceStatus::INVALID);
        }
        return id;
    }

    ResourceID OpenGLGraphicsResourceManager::Create(const ShaderConfig &config, DataPtr data)
    {
        auto id = mRegistry.Find(config.Name);
        if (id == InvalidResourceID)
        {
            id = mShaderPool.Create();
            mRegistry.Add(config.Name, id, mLabelStack.top());
            auto &shader = mShaderPool.Get(id, config);
            shader.Status = mShaderFactory.Create(shader, data);
            s_assert(shader.Status != ResourceStatus::INVALID);
        }
        return id;
    }

    ResourceID OpenGLGraphicsResourceManager::Create(const ProgramConfig &config, DataPtr data)
    {
        auto id = mRegistry.Find(config.Name);
        if (id == InvalidResourceID)
        {
            id = mProgramPool.Create();
            mRegistry.Add(config.Name, id, mLabelStack.top());
            auto &program = mProgramPool.Get(id, config);
            program.Status = mProgramFactory.Create(program, data);
            s_assert(program.Status != ResourceStatus::INVALID);
        }
        return id;
    }

    ResourceID OpenGLGraphicsResourceManager::Create(const TextureConfig &config, DataPtr data)
    {
        auto id = mRegistry.Find(config.Name);
        if (id == InvalidResourceID)
        {
            id = mTexturePool.Create();
            mRegistry.Add(config.Name, id, mLabelStack.top());
            auto &texture = mTexturePool.Get(id, config);
            texture.Status = mTextureFactory.Create(texture, data);
            s_assert(texture.Status != ResourceStatus::INVALID);
        }
        return id;
    }

    VertexBufferConfig &OpenGLGraphicsResourceManager::GetVertexBufferConfig(ResourceID id)
    {
        auto resource = mVertexBufferPool.Find(id);
        s_assert(resource != nullptr);
        return resource->Config;
    }

    IndexBufferConfig &OpenGLGraphicsResourceManager::GetIndexBufferConfig(ResourceID id)
    {
        auto resource = mIndexBufferPool.Find(id);
        s_assert(resource != nullptr);
        return resource->Config;
    }

    ShaderConfig &OpenGLGraphicsResourceManager::GetShaderConfig(ResourceID id)
    {
        auto resource = mShaderPool.Find(id);
        s_assert(resource != nullptr);
        return resource->Config;
    }

    ProgramConfig &OpenGLGraphicsResourceManager::GetProgramConfig(ResourceID id)
    {
        auto resource = mProgramPool.Find(id);
        s_assert(resource != nullptr);
        return resource->Config;
    }

    TextureConfig &OpenGLGraphicsResourceManager::GetTextureConfig(ResourceID id)
    {
        auto resource = mTexturePool.Find(id);
        s_assert(resource != nullptr);
        return resource->Config;
    }

    void OpenGLGraphicsResourceManager::SetProgramUniformData(ResourceID id, int32 index, const void *buffer, size_t size)
    {
        auto program = mProgramPool.Find(id);
        s_assert(program != nullptr);
        s_assert_range(index, 0, GraphicsConfig::MaxUniformNodeCount - 1);
        auto offset = program->UniformDataOffset[index];
        s_assert(offset + size <= program->UniformData.GetSize());
        program->UniformData.Copy(buffer, size, offset);
        program->NeedUpdate[index] = true;
    }

    void OpenGLGraphicsResourceManager::Destroy(ResourceLabel label)
    {
        auto all = mRegistry.Remove(label);
        for (auto id : all)
        {
            Destroy(id);
        }
    }

    void OpenGLGraphicsResourceManager::Destroy(ResourceID id)
    {
        switch (static_cast<GraphicsResourceType>(GetResourcePoolIDOfResourceID(id)))
        {
        case GraphicsResourceType::VERTEX_BUFFER:
        {
            auto vertexBuffer = mVertexBufferPool.Find(id);
            if (vertexBuffer)
            {
                mVertexBufferFactory.Destroy(*vertexBuffer);
                mVertexBufferPool.Destroy(id);
            }
            break;
        }
        case GraphicsResourceType::INDEX_BUFFER:
        {
            auto indexBuffer = mIndexBufferPool.Find(id);
            if (indexBuffer)
            {
                mIndexBufferFactory.Destroy(*indexBuffer);
                mIndexBufferPool.Destroy(id);
            }
            break;
        }
        case GraphicsResourceType::SHADER:
        {
            auto shader = mShaderPool.Find(id);
            if (shader)
            {
                mShaderFactory.Destroy(*shader);
                mShaderPool.Destroy(id);
            }
            break;
        }
        case GraphicsResourceType::PROGRAM:
        {
            auto program = mProgramPool.Find(id);
            if (program)
            {
                mProgramFactory.Destroy(*program);
                mProgramPool.Destroy(id);
            }
            break;
        }
        case GraphicsResourceType::TEXTURE:
        {
            auto texture = mTexturePool.Find(id);
            if (texture)
            {
                mTextureFactory.Destroy(*texture);
                mTexturePool.Destroy(id);
            }
            break;
        }
        default:
            s_error("unknown resource type");
            break;
        }
    }

    OpenGLVertexBuffer *OpenGLGraphicsResourceManager::GetVertexBuffer(ResourceID id)
    {
        return mVertexBufferPool.Find(id);
    }

    OpenGLIndexBuffer *OpenGLGraphicsResourceManager::GetIndexBuffer(ResourceID id)
    {
        return mIndexBufferPool.Find(id);
    }

    OpenGLShader *OpenGLGraphicsResourceManager::GetShader(ResourceID id)
    {
        return mShaderPool.Find(id);
    }

    OpenGLProgram *OpenGLGraphicsResourceManager::GetProgram(ResourceID id)
    {
        return mProgramPool.Find(id);
    }

    OpenGLTexture *OpenGLGraphicsResourceManager::GetTexture(ResourceID id)
    {
        return mTexturePool.Find(id);
    }
}
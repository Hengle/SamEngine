#pragma once

#include "OpenGL/Renderer/OpenGLDefine.h"

#include "Config/VertexBufferConfig.h"
#include "Config/IndexBufferConfig.h"
#include "Config/UniformBufferConfig.h"
#include "Config/ShaderConfig.h"
#include "Config/ProgramConfig.h"
#include "Config/TextureConfig.h"
#include "Config/DrawCallConfig.h"

#include <ResourceModule.h>

#include <glad/glad.h>

#include <cstring>

namespace SamEngine
{
    class OpenGLVertexBuffer : public Resource<VertexBufferConfig>
    {
    public:
        GLuint VertexBufferID[GraphicsConfig::MaxStreamVertexBufferCount];

        uint32 VertexBufferCount{ 1 };

        uint32 CurrentVertexBuffer{ 0 };

        OpenGLVertexAttributeParam VertexAttributeParam[GraphicsConfig::MaxVertexNodeCount];

        void Finalize() override;
    };

    inline void OpenGLVertexBuffer::Finalize()
    {
        std::memset(VertexBufferID, 0, sizeof(VertexBufferID));
        VertexBufferCount = 1;
        CurrentVertexBuffer = 0;
        std::memset(VertexAttributeParam, 0, sizeof(VertexAttributeParam));
        Resource::Finalize();
    }

    class OpenGLIndexBuffer : public Resource<IndexBufferConfig>
    {
    public:
        GLuint IndexBufferID{ 0 };

        void Finalize() override;
    };

    inline void OpenGLIndexBuffer::Finalize()
    {
        IndexBufferID = 0;
        Resource::Finalize();
    }

    class OpenGLUniformBuffer : public Resource<UniformBufferConfig>
    {
    public:
        GLint UniformLocations[GraphicsConfig::MaxUniformNodeCount];

        void Finalize() override;
    };

    inline void OpenGLUniformBuffer::Finalize()
    {
        std::memset(UniformLocations, 0, sizeof(UniformLocations));
        Resource::Finalize();
    }

    class OpenGLShader : public Resource<ShaderConfig>
    {
    public:
        GLuint ShaderID{ 0 };

        void Finalize() override;
    };

    inline void OpenGLShader::Finalize()
    {
        ShaderID = 0;
        Resource::Finalize();
    }

    class OpenGLProgram : public Resource<ProgramConfig>
    {
    public:
        GLuint ProgramID{ 0 };

        void Finalize() override;
    };

    inline void OpenGLProgram::Finalize()
    {
        ProgramID = 0;
        Resource::Finalize();
    }

    class OpenGLTexture : public Resource<TextureConfig>
    {
    public:
        GLuint TextureID{ 0 };

        GLenum Target{ 0 };

        GLuint FrameBufferID{ 0 };

        GLuint DepthRenderBufferID{ 0 };

        void Finalize() override;
    };

    inline void OpenGLTexture::Finalize()
    {
        TextureID = 0;
        Target = 0;
        FrameBufferID = 0;
        DepthRenderBufferID = 0;
        Resource::Finalize();
    }

    class OpenGLDrawCall : public Resource<DrawCallConfig> {};
}
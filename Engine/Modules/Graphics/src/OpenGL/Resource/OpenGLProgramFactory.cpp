#include "OpenGLProgramFactory.h"

#include "OpenGL/Renderer/OpenGLRenderer.h"
#include "OpenGL/Resource/OpenGLGraphicsResourceManager.h"

namespace SamEngine
{
    ResourceStatus OpenGLProgramFactory::Create(OpenGLProgram &resource, DataPtr data)
    {
        auto vertex = OpenGLGraphicsResourceManager::Get().GetShader(resource.Config.VertexShader);
        auto fragment = OpenGLGraphicsResourceManager::Get().GetShader(resource.Config.FragmentShader);

        s_assert(vertex != nullptr);
        s_assert(fragment != nullptr);

        auto program = glCreateProgram();
        
        glAttachShader(program, vertex->ShaderID);
        glAttachShader(program, fragment->ShaderID);

        for (auto i = 0; i < GraphicsConfig::MaxVertexNodeCount; ++i)
        {
            glBindAttribLocation(program, i, VertexAttributeNameFromType(static_cast<VertexAttributeType>(i)));
        }

        glLinkProgram(program);

        auto status = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &status);

        #if SAM_DEBUG
        auto log_length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
        if (status == GL_FALSE && log_length > 0)
        {
            auto log = static_cast<GLchar *>(malloc(log_length));
            glGetProgramInfoLog(program, log_length, &log_length, log);
            GetLog().Debug("[link log]:\n%s\n\n", log);
            free(log);
        }
        #endif

        if (status == GL_FALSE)
        {
            glDeleteProgram(program);
            program = 0;
        }

        if (program != 0)
        {
            OpenGLRenderer::Get().BindProgram(program);
            auto &config = resource.Config;
            resource.UniformData.SetSize(config.Size());
            auto length = config.Uniform.Length();
            auto offset = 0;
            auto index = 0;
            for (auto i = 0; i < length; ++i)
            {
                auto &node = config.Uniform.At(i);
                resource.UniformLocations[i] = glGetUniformLocation(program, node.GetName().c_str());
                resource.UniformDataOffset[i] = offset;
                resource.NeedUpdate[i] = true;
                offset += node.Size();
                if (node.GetType() == UniformAttributeFormat::TEXTURE)
                {
                    resource.TextureUniformIndex[i] = index++;
                    glUniform1i(resource.UniformLocations[i], resource.TextureUniformIndex[i]);
                }
            }
        }

        resource.ProgramID = program;

        return ResourceStatus::COMPLETED;
    }

    void OpenGLProgramFactory::Destroy(OpenGLProgram &resource)
    {
        OpenGLRenderer::Get().ResetProgram();
        glDeleteProgram(resource.ProgramID);
    }
}
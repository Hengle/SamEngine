#include "OpenGLShaderFactory.h"

namespace SamEngine
{
    ResourceStatus OpenGLShaderFactory::Create(OpenGLShader &resource, DataPtr data)
    {
        auto type = GLEnumFromShaderType(resource.Config.Type);
        auto source = resource.Config.Source.c_str();
        int32 length = resource.Config.Source.length();

        auto shader = glCreateShader(type);
        s_assert(shader != 0);

        glShaderSource(shader, 1, &source, &length);
        glCompileShader(shader);

        auto status = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

        #if SAM_DEBUG
        auto log_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
        if (status == GL_FALSE && log_length > 0)
        {
            GetLog().Debug("[shader source]:\n%s\n\n", source);
            auto log = static_cast<GLchar *>(std::malloc(log_length));
            glGetShaderInfoLog(shader, log_length, &log_length, log);
            GetLog().Debug("[compile log]:\n%s\n\n", log);
            std::free(log);
        }
        #endif

        if (status == GL_FALSE)
        {
            glDeleteShader(shader);
            shader = 0;
        }

        resource.ShaderID = shader;
        return ResourceStatus::COMPLETED;
    }

    void OpenGLShaderFactory::Destroy(OpenGLShader &resource)
    {
        glDeleteShader(resource.ShaderID);
    }
}
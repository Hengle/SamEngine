#include "OpenGLUniformBufferFactory.h"

#include "OpenGL/Renderer/OpenGLRenderer.h"
#include "OpenGL/Resource/OpenGLGraphicsResourceManager.h"

namespace SamEngine
{
    ResourceStatus OpenGLUniformBufferFactory::Create(OpenGLUniformBuffer &resource, DataPtr data)
    {
        auto &config = resource.Config;

        s_assert(config.Program != InvalidResourceID);
        OpenGLRenderer::Get().ApplyProgram(config.Program);

        auto program = OpenGLGraphicsResourceManager::Get().GetProgram(config.Program);
        s_assert(program != nullptr);

        resource.UniformData.SetSize(config.Size());

        auto length = config.Layout.Length();
        auto offset = 0;
        for (auto i = 0; i < length; ++i)
        {
            auto &node = config.Layout.At(i);
            resource.UniformLocations[i] = glGetUniformLocation(program->ProgramID, node.GetName().c_str());
            resource.UniformDataOffset[i] = offset;
            resource.NeedUpdate[i] = true;
            offset += node.Size();
        }

        return ResourceStatus::COMPLETED;
    }

    void OpenGLUniformBufferFactory::Destroy(OpenGLUniformBuffer &resource)
    {
    }
}
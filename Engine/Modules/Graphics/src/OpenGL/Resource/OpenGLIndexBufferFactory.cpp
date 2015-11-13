#include "OpenGLIndexBufferFactory.h"

#include "OpenGL/Renderer/OpenGLRenderer.h"

namespace SamEngine
{
    ResourceStatus OpenGLIndexBufferFactory::Create(OpenGLIndexBuffer &resource, DataPtr data)
    {
        auto &config = resource.Config;

        s_assert(config.Type != IndexAttributeType::NONE);

        void *buffer = nullptr;
        if (data != nullptr && !data->Empty())
        {
            s_assert(config.Size() <= data->GetSize());
            buffer = data->GetBuffer();
        }

        glGenBuffers(1, &resource.IndexBufferID);
        s_assert(resource.IndexBufferID != 0);

        OpenGLRenderer::Get().BindIndexBuffer(resource.IndexBufferID);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, config.Size(), buffer, GLEnumFromBufferUsage(config.Usage));

        OpenGLRenderer::Get().ResetIndexBuffer();

        return ResourceStatus::COMPLETED;
    }

    void OpenGLIndexBufferFactory::Destroy(OpenGLIndexBuffer &resource)
    {
        OpenGLRenderer::Get().ResetIndexBuffer();
        glDeleteBuffers(1, &resource.IndexBufferID);
    }
}
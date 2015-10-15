#include "OpenGLIndexBufferFactory.h"

#include "OpenGL/Renderer/OpenGLRenderer.h"

namespace SamEngine
{
    ResourceStatus OpenGLIndexBufferFactory::Create(OpenGLIndexBuffer &resource, DataPtr data)
    {
        s_assert(data != nullptr && data->GetSize() > 0);
        s_assert(resource.Config.Type != IndexAttributeType::NONE);

        glGenBuffers(1, &resource.IndexBufferID);
        s_assert(resource.IndexBufferID != 0);

        OpenGLRenderer::Get().BindIndexBuffer(resource.IndexBufferID);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->GetSize(), data->GetBuffer(), GLEnumFromBufferUsage(resource.Config.Usage));

        OpenGLRenderer::Get().ResetIndexBuffer();

        return ResourceStatus::COMPLETED;
    }

    void OpenGLIndexBufferFactory::Destroy(OpenGLIndexBuffer &resource)
    {
        OpenGLRenderer::Get().ResetIndexBuffer();
        glDeleteBuffers(1, &resource.IndexBufferID);
    }
}
#include "OpenGLUniformBufferFactory.h"

namespace SamEngine
{
    ResourceStatus OpenGLUniformBufferFactory::Create(OpenGLUniformBuffer &resource, DataPtr data)
    {
        return ResourceStatus::COMPLETED;
    }

    void OpenGLUniformBufferFactory::Destroy(OpenGLUniformBuffer &resource)
    {
    }
}
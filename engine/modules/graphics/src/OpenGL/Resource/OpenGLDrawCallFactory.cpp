#include "OpenGLDrawCallFactory.h"

namespace SamEngine
{
    ResourceStatus OpenGLDrawCallFactory::Create(OpenGLDrawCall &resource, DataPtr data)
    {
        return ResourceStatus::COMPLETED;
    }

    void OpenGLDrawCallFactory::Destroy(OpenGLDrawCall &resource)
    {
    }
}
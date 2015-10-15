#pragma once

#include "OpenGLResource.h"

#include "GraphicsDefine.h"

namespace SamEngine
{
    class OpenGLUniformBufferFactory : public ResourceFactory<OpenGLUniformBuffer>
    {
    public:
        ResourceStatus Create(OpenGLUniformBuffer &resource, DataPtr data) override;

        void Destroy(OpenGLUniformBuffer &resource) override;
    };
}
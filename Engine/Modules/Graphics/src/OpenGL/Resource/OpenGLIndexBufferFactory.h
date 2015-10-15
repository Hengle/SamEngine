#pragma once

#include "OpenGLResource.h"

#include "GraphicsDefine.h"

namespace SamEngine
{
    class OpenGLIndexBufferFactory : public ResourceFactory<OpenGLIndexBuffer>
    {
    public:
        ResourceStatus Create(OpenGLIndexBuffer& resource, DataPtr data) override;

        void Destroy(OpenGLIndexBuffer& resource) override;
    };
}
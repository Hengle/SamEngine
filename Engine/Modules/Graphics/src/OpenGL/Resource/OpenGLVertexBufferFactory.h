#pragma once

#include "OpenGLResource.h"

#include "GraphicsDefine.h"

namespace SamEngine
{
    class OpenGLVertexBufferFactory : public ResourceFactory<OpenGLVertexBuffer>
    {
    public:
        ResourceStatus Create(OpenGLVertexBuffer &resource, DataPtr data) override;

        void Destroy(OpenGLVertexBuffer &resource) override;
    };
}
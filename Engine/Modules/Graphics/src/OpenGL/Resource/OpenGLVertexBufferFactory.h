#pragma once

#include "OpenGLResource.h"

#include "GraphicsDefine.h"

namespace SamEngine
{
    class OpenGLVertexBufferFactory : public ResourceFactory<OpenGLVertexBuffer>
    {
    public:
        virtual ResourceStatus Create(OpenGLVertexBuffer &resource, DataPtr data) override;

        virtual void Destroy(OpenGLVertexBuffer &resource) override;
    };
}
#pragma once

#include "OpenGLResource.h"

#include "GraphicsDefine.h"

namespace SamEngine
{
    class OpenGLIndexBufferFactory : public ResourceFactory<OpenGLIndexBuffer>
    {
    public:
        virtual ResourceStatus Create(OpenGLIndexBuffer& resource, DataPtr data) override;

        virtual void Destroy(OpenGLIndexBuffer& resource) override;
    };
}
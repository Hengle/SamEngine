#pragma once

#include "OpenGLResource.h"

#include "GraphicsDefine.h"

namespace SamEngine
{
    class OpenGLDrawCallFactory : public ResourceFactory<OpenGLDrawCall>
    {
    public:
        ResourceStatus Create(OpenGLDrawCall& resource, DataPtr data) override;

        void Destroy(OpenGLDrawCall& resource) override;
    };
}
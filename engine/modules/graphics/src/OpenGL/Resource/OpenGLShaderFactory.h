#pragma once

#include "OpenGLResource.h"

#include "GraphicsDefine.h"

namespace SamEngine
{
    class OpenGLShaderFactory : public ResourceFactory<OpenGLShader>
    {
    public:
        ResourceStatus Create(OpenGLShader& resource, DataPtr data) override;

        void Destroy(OpenGLShader& resource) override;
    };
}
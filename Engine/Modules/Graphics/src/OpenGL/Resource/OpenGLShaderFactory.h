#pragma once

#include "OpenGLResource.h"

#include "GraphicsDefine.h"

namespace SamEngine
{
    class OpenGLShaderFactory : public ResourceFactory<OpenGLShader>
    {
    public:
        virtual ResourceStatus Create(OpenGLShader& resource, DataPtr data) override;

        virtual void Destroy(OpenGLShader& resource) override;
    };
}
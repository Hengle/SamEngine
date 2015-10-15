#pragma once

#include "OpenGLResource.h"

#include "GraphicsDefine.h"

namespace SamEngine
{
    class OpenGLProgramFactory : public ResourceFactory<OpenGLProgram>
    {
    public:
        ResourceStatus Create(OpenGLProgram& resource, DataPtr data) override;

        void Destroy(OpenGLProgram& resource) override;
    };
}
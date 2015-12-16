#pragma once

#include "OpenGLResource.h"

#include "GraphicsDefine.h"

namespace SamEngine
{
    class OpenGLProgramFactory : public ResourceFactory<OpenGLProgram>
    {
    public:
        virtual ResourceStatus Create(OpenGLProgram& resource, DataPtr data) override;

        virtual void Destroy(OpenGLProgram& resource) override;
    };
}
#pragma once

#include "OpenGLResource.h"

#include "GraphicsDefine.h"

namespace SamEngine
{
    class OpenGLTextureFactory : public ResourceFactory<OpenGLTexture>
    {
    public:
        virtual ResourceStatus Create(OpenGLTexture &resource, DataPtr data) override;

        virtual void Destroy(OpenGLTexture &resource) override;
    };
}
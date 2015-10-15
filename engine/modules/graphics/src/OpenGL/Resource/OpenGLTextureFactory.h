#pragma once

#include "OpenGLResource.h"

#include "GraphicsDefine.h"

namespace SamEngine
{
    class OpenGLTextureFactory : public ResourceFactory<OpenGLTexture>
    {
    public:
        ResourceStatus Create(OpenGLTexture &resource, DataPtr data) override;

        void Destroy(OpenGLTexture &resource) override;
    };
}
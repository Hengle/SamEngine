#pragma once

#include "Renderer/ICanvas.h"

#include <glad/glad.h>
#include <nanovg.h>

namespace SamEngine
{
    class OpenGLCanvas : public ICanvas
    {
    public:
        virtual void Initialize() override;

        virtual void Finalize() override;

        virtual bool Available() override;

        virtual void BeginFrame() override;

        virtual void EndFrame() override;

        virtual CanvasContextPtr GetContext() override;

    private:
        CanvasContextPtr mContext{ nullptr };
    };
}
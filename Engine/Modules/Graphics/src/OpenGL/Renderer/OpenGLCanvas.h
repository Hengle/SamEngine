#pragma once

#include "Renderer/ICanvas.h"

#include <glad/glad.h>
#include <nanovg.h>

namespace SamEngine
{
    class OpenGLCanvas : public ICanvas
    {
    public:
        void Initialize() override;

        void Finalize() override;

        bool Available() override;

        void BeginFrame() override;

        void EndFrame() override;

        CanvasContextPtr GetContext() override;

    private:
        CanvasContextPtr mContext{ nullptr };
    };
}
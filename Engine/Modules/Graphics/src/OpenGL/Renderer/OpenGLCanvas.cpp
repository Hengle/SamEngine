#include "OpenGLCanvas.h"

#include <WindowModule.h>

#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg_gl.h>

namespace SamEngine
{
    void OpenGLCanvas::Initialize()
    {
        s_assert(!Available());
        mContext.reset(nvgCreateGL3(0), nvgDeleteGL3);
    }

    void OpenGLCanvas::Finalize()
    {
        s_assert(Available());
    }

    bool OpenGLCanvas::Available()
    {
        return mContext != nullptr;
    }

    void OpenGLCanvas::BeginFrame()
    {
        s_assert(Available());
        auto config = GetWindow().GetConfig();
        auto ratio = static_cast<float32>(config.Width) / static_cast<float32>(config.Height);
        nvgBeginFrame(mContext.get(), config.Width, config.Height, ratio);
    }

    void OpenGLCanvas::EndFrame()
    {
        s_assert(Available());
        nvgEndFrame(mContext.get());
    }

    CanvasContextPtr OpenGLCanvas::GetContext()
    {
        return mContext;
    }
}
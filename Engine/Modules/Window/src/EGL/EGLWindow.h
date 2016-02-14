#pragma once

#if SAM_ANDROID

#include "IWindow.h"

#include "EGL/Input/EGLInput.h"

#include <EGL/egl.h>

extern android_app *gAndroidApp;

namespace SamEngine
{
    class EGLWindow : public IWindow, public ITick
    {
    public:
        virtual void Initialize(const WindowConfig &config) override;

        virtual void Finalize() override;

        virtual bool Available() override;

        virtual bool ShouldClose() override;

        virtual void Present() override;

        virtual IInput &GetInput() override;

        virtual void SetTitle(const std::string &name) override;

        virtual const WindowConfig &GetConfig() const override;

        virtual void Tick(TickCount now, TickCount delta) override;

    private:
        EGLInput mInput;
        WindowConfig mConfig;
        EGLDisplay mEGLDisplay{ nullptr };
        EGLConfig mEGLConfig{ nullptr };
        EGLSurface mEGLSurface{ nullptr };
        EGLContext mEGLContext{ nullptr };
    };
}

#endif
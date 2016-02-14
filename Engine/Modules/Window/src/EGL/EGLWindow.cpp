#if SAM_ANDROID

#include "EGLWindow.h"

namespace SamEngine
{
    void EGLWindow::Initialize(const WindowConfig &config)
    {
        s_assert(!Available());
        mConfig = config;
        mEGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        s_assert(Available());
        s_assert(eglGetError() == EGL_SUCCESS);
        if (!eglInitialize(mEGLDisplay, nullptr, nullptr)) {
            s_error("Initialize EGL failed!\n");
            return;
        }
    }

    void EGLWindow::Finalize()
    {
        s_assert(Available());
        eglDestroyContext(mEGLDisplay, mEGLContext);
        eglDestroySurface(mEGLDisplay, mEGLSurface);
        eglTerminate(mEGLDisplay);
        mEGLDisplay = mEGLContext = mEGLSurface = nullptr;
    }

    bool EGLWindow::Available()
    {
        return mEGLDisplay != nullptr;
    }

    bool EGLWindow::ShouldClose()
    {
        return false;
    }

    void EGLWindow::Present()
    {
        eglSwapBuffers(mEGLDisplay, mEGLSurface);
    }

    IInput &EGLWindow::GetInput()
    {
        return mInput;
    }

    void EGLWindow::SetTitle(const std::string &name)
    {

    }

    const WindowConfig &EGLWindow::GetConfig() const
    {
        return mConfig;
    }

    void EGLWindow::Tick(TickCount now, TickCount delta)
    {

    }
}

#endif
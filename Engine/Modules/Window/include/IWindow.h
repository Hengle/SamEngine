#pragma once

#include "WindowConfig.h"

#include <functional>

namespace SamEngine
{
    typedef std::function<void(MouseButtonType, bool)> MouseInputCallback;

    typedef std::function<void(KeyboardButtonType, bool)> KeyboardInputCallback;

    class WINDOW_API IWindow
    {
    public:
        virtual ~IWindow() {}

        virtual void Initialize(const WindowConfig &config) = 0;

        virtual void Finalize() = 0;

        virtual bool Available() = 0;

        virtual bool ShouldClose() = 0;

        virtual void Present() = 0;

        virtual void SetMouseInputCallback(MouseInputCallback callback) = 0;

        virtual void SetKeyboardInputCallback(KeyboardInputCallback callback) = 0;

        virtual const WindowConfig &GetConfig() const = 0;
    };

    extern WINDOW_API IWindow &GetWindow();
};
#pragma once

#include "Input/IInput.h"
#include "WindowConfig.h"

namespace SamEngine
{
    class WINDOW_API IWindow
    {
    public:
        virtual ~IWindow() {}

        virtual void Initialize(const WindowConfig &config) = 0;

        virtual void Finalize() = 0;

        virtual bool Available() = 0;

        virtual bool ShouldClose() = 0;

        virtual void Present() = 0;

        virtual void SetTitle(const std::string &name) = 0;

        virtual IInput &GetInput() = 0;

        virtual const WindowConfig &GetConfig() const = 0;
    };

    extern WINDOW_API IWindow &GetWindow();
};
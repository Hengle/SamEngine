#pragma once

#include <CoreModule.h>

struct NVGcontext;

namespace SamEngine
{
    typedef std::shared_ptr<NVGcontext> CanvasContextPtr;

    class GRAPHICS_API ICanvas
    {
        public:
        virtual ~ICanvas() {}

        virtual void Initialize() = 0;

        virtual void Finalize() = 0;

        virtual bool Available() = 0;

        virtual void BeginFrame() = 0;

        virtual void EndFrame() = 0;

        virtual CanvasContextPtr GetContext() = 0;
    };
}
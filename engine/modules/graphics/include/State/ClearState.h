#pragma once

#include "GraphicsDefine.h"

namespace SamEngine
{
    struct GRAPHICS_API ClearState
    {
        Color ClearColor = Color(1.0f, 1.0f, 1.0f, 1.0f);

        float32 Depth = 1.0f;

        uint8 Stencil = 0;

        ClearType Type = ClearType::ALL;
    };
}
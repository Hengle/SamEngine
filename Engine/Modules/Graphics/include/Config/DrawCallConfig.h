#pragma once

#include "GraphicsDefine.h"

namespace SamEngine
{
    struct GRAPHICS_API DrawCallConfig
    {
        ResourceName Name{ ResourceName::Unique() };

        DrawType Type{ DrawType::TRIANGLES };

        int32 First{ 0 };

        int32 Count{ 0 };
    };
}
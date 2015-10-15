#pragma once

#include "GraphicsDefine.h"

namespace SamEngine
{
    struct GRAPHICS_API IndexBufferConfig
    {
        ResourceName Name{ ResourceName::Unique() };

        int32 Count{ 0 };

        IndexAttributeType Type{ IndexAttributeType::NONE };

        BufferUsage Usage{ BufferUsage::IMMUTABLE };

        int32 Size() const;
    };

    inline int32 IndexBufferConfig::Size() const
    {
        return Count * SizeOfIndexAttributeType(Type);
    }
}
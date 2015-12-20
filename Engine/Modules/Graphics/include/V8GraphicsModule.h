#pragma once

#include "GraphicsModule.h"

#include <v8.h>
#include <v8pp/class.hpp>
#include <v8pp/module.hpp>

namespace SamEngine
{
    int test(int i) { return i; }

    inline static void OpenGraphicsV8Module(v8pp::module &root)
    {
        root.set("GetGraphics", &GetGraphics);
    }
}
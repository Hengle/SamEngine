#pragma once

#include "IOModule.h"

#include <LuaIntf.h>

using namespace LuaIntf;

namespace SamEngine
{
    inline static void OpenIOModule(LuaState state)
    {
        LuaBinding(state).beginModule("SamEngine")
            .addProperty("IO", &GetIO)
            .beginClass<IIO>("IIO")
                .addFunction("SetLocationPlaceholder", &IIO::SetLocationPlaceholder, LUA_ARGS(std::string, std::string))
                .addFunction("Read", &IIO::Read, LUA_ARGS(std::string, IOCallbackFunction))
                .addFunction("Write", &IIO::Write, LUA_ARGS(std::string, DataPtr, _opt<IOCallbackFunction>))
            .endClass()
       .endModule();
    }
}
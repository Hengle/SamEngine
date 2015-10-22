#pragma once

#include "CoreModule.h"

#include <lua.hpp>
#include <LuaIntf.h>

#include <map>
#include <memory>
#include <vector>

using namespace LuaIntf;

namespace LuaIntf
{
    LUA_USING_SHARED_PTR_TYPE(std::shared_ptr)
    LUA_USING_LIST_TYPE(std::vector)
    LUA_USING_MAP_TYPE(std::map)
}

namespace SamEngine
{
    inline static void OpenCoreModule(lua_State *L)
    {
        LuaBinding(L).beginModule("SamEngine")
            .beginClass<ILog>("Log")
                .addStaticFunction("Error", [](std::string message)
                {
                    GetLog().Error(message.c_str());
                }, LUA_ARGS(std::string))
                .addStaticFunction("Warning", [](std::string message)
                {
                    GetLog().Error(message.c_str());
                }, LUA_ARGS(std::string))
                .addStaticFunction("Info", [](std::string message)
                {
                    GetLog().Error(message.c_str());
                }, LUA_ARGS(std::string))
                .addStaticFunction("Debug", [](std::string message)
                {
                    GetLog().Error(message.c_str());
                }, LUA_ARGS(std::string))
            .endClass()
            .beginClass<Data>("Data")
                .addConstructor(LUA_ARGS(_opt<size_t>))
                .addProperty("Size", &Data::GetSize, &Data::SetSize)
                .addFunction("Clear", &Data::Clear)
                .addFunction("Empty", &Data::Empty)
            .endClass()
        .endModule();
    }
}
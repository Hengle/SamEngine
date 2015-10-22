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

    }
}
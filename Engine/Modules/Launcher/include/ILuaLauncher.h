#pragma once

#if SAM_USE_LUA

#include "IApplication"
#include "ILauncher.h"

#include <CoreModule.h>

#include <string>

#if SAM_WINDOWS
#   include <Windows.h>
#   define SamEngineLuaApplication(file, initialize, finalize, draw, tick, width, height, title) \
        int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nShowCmd) \
        { \
            try \
            { \
                SamEngine::GetLauncher().SetApplication(&SamEngine::GetLuaLauncher()); \
                SamEngine::GetLuaLauncher().Create(initialize, finalize, draw, tick, width, height, title); \
                SamEngine::GetLuaLauncher().Run(file); \
                SamEngine::GetLauncher().Run(); \
            } \
            catch (std::exception &e) \
            { \
                s_error(e.what()); \
            } \
            return 0; \
        }
#else
#   define SamEngineLuaApplication(file, initialize, finalize, draw, tick, width, height, title) \
        int main(int argc, char *argv[]) \
        { \
            try \
            { \
                SamEngine::GetLauncher().SetApplication(&SamEngine::GetLuaLauncher()); \
                SamEngine::GetLuaLauncher().Create(initialize, finalize, draw, tick, width, height, title); \
                SamEngine::GetLuaLauncher().Run(file); \
                SamEngine::GetLauncher().Run(); \
            } \
            catch (std::exception &e) \
            { \
                s_error(e.what()); \
            } \
            return 0; \
        }
#endif

#define SamEngineLuaApplicationWithFile(file, width, height, title) \
    SamEngineLuaApplication(file, "Game.Initialize", "Game.Finalize", "Game.Draw", "Game.Tick", width, height, title)

namespace SamEngine
{
    class LAUNCHER_API ILuaLauncher : public IApplication
    {
    public:
        virtual void Create(const std::string &initialize, const std::string &finalize, const std::string &update, const std::string &tick, int32 width, int32 height, const std::string &title) = 0;

        virtual void Run(const std::string &file) = 0;
    };

    extern LAUNCHER_API ILuaLauncher &GetLuaLauncher();
}

#endif
#pragma once

#include "IApplication.h"

#include <CoreModule.h>

#if SAM_WINDOWS
#   include <Windows.h>
#   define SamEngineLuaApplication(file, main, initialize, finalize, update, tick, width, height, title) \
        int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nShowCmd) \
        { \
            SamEngine::GetLauncher().SetApplication(&SamEngine::GetLuaLauncher()); \
            SamEngine::GetLuaLauncher().Create(main, initialize, finalize, update, tick, width, height, title); \
            SamEngine::GetLuaLauncher().Run(file); \
            SamEngine::GetLauncher().Run(); \
            SamEngine::GetLuaLauncher().Destroy(); \
            return 0; \
        }
#else
#   define SamEngineLuaApplication(file, main, initialize, finalize, update, tick, width, height, title) \
        int main(int argc, char *argv[]) \
        { \
            SamEngine::GetLauncher().SetApplication(&SamEngine::GetLuaLauncher()); \
            SamEngine::GetLuaLauncher().Create(main, initialize, finalize, update, tick, width, height, title); \
            SamEngine::GetLuaLauncher().Run(file); \
            SamEngine::GetLauncher().Run(); \
            SamEngine::GetLuaLauncher().Destroy(); \
            return 0; \
        }
#endif

#define SamEngineLuaApplicationWithFile(file, width, height, title) \
    SamEngineLuaApplication(file, "Game", "Initialize", "Finalize", "Update", "Tick", width, height, title)

namespace SamEngine
{
    class LAUNCHER_API ILuaLauncher : public IApplication
    {
    public:
        virtual void Create(const std::string &main, const std::string &initialize, const std::string &finalize, const std::string &update, const std::string &tick, int32 width, int32 height, const std::string &title) = 0;

        virtual void Destroy() = 0;

        virtual void Run(const std::string &file) = 0;
    };

    extern LAUNCHER_API ILuaLauncher &GetLuaLauncher();
}
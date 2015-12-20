#pragma once

#include <CoreModule.h>
#include <LauncherModule.h>

#include <string>

#if SAM_WINDOWS
#   include <Windows.h>
#   define SamEngineV8Application(file, initialize, finalize, draw, tick, width, height, title) \
        int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nShowCmd) \
        { \
            try \
            { \
                SamEngine::GetLauncher().SetApplication(&SamEngine::GetV8Launcher()); \
                SamEngine::GetV8Launcher().Create(initialize, finalize, draw, tick, width, height, title); \
                SamEngine::GetV8Launcher().Run(file); \
                SamEngine::GetLauncher().Run(); \
            } \
            catch (std::exception &e) \
            { \
                s_error(e.what()); \
            } \
            return 0; \
        }
#else
#   define SamEngineV8Application(file, initialize, finalize, draw, tick, width, height, title) \
        int main(int argc, char *argv[]) \
        { \
            try \
            { \
                SamEngine::GetLauncher().SetApplication(&SamEngine::GetV8Launcher()); \
                SamEngine::GetV8Launcher().Create(initialize, finalize, draw, tick, width, height, title); \
                SamEngine::GetV8Launcher().Run(file); \
                SamEngine::GetLauncher().Run(); \
            } \
            catch (std::exception &e) \
            { \
                s_error(e.what()); \
            } \
            return 0; \
        }
#endif

#define SamEngineV8ApplicationWithFile(file, width, height, title) \
    SamEngineV8Application(file, "Initialize", "Finalize", "Draw", "Tick", width, height, title)

namespace SamEngine
{
    class V8_LAUNCHER_API IV8Launcher : public IApplication
    {
    public:
        virtual void Create(const std::string &initialize, const std::string &finalize, const std::string &update, const std::string &tick, int32 width, int32 height, const std::string &title) = 0;

        virtual void Run(const std::string &file) = 0;
    };

    extern V8_LAUNCHER_API IV8Launcher &GetV8Launcher();
}
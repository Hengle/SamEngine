#pragma once

#include "IApplication.h"

#if SAM_WINDOWS
#   include <Windows.h>
#   define SamEngineApplication(clazz) \
        int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nShowCmd) \
        { \
            auto application = new clazz; \
            SamEngine::GetLauncher().SetApplication(application); \
            SamEngine::GetLauncher().Run(); \
            delete application; \
            return 0; \
        }
#else
#   define SamEngineApplication(clazz) \
        int main(int argc, char *argv[]) \
        { \
            auto application = new clazz; \
            SamEngine::GetLauncher().SetApplication(application); \
            SamEngine::GetLauncher().Run(); \
            delete application; \
            return 0; \
        }
#endif

namespace SamEngine
{
    class LAUNCHER_API ILauncher
    {
    public:
        virtual ~ILauncher() {}

        virtual void SetApplication(IApplication *application) = 0;

        virtual void Run() = 0;
    };

    extern LAUNCHER_API ILauncher &GetLauncher();
}
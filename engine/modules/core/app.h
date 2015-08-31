#pragma once

#include "types.h"

#if defined(SAM_WINDOWS)
#   include <Windows.h>
#   define SAM_MAIN(clazz) \
        int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nShowCmd) \
        { \
            clazz *app = new clazz(); \
            app->start(); \
            delete app; \
            return 0; \
        }
#else
#   define SAM_MAIN(clazz) \
        int main(int argc, char *argv[]) \
        { \
            clazz *app = new clazz(); \
            app->start(); \
            delete app; \
            return 0; \
        }
#endif

namespace sam
{
    class app
    {
    public:
        enum class state : int32
        {
            initialize,
            running,
            finalize,
            invalid,
        };

        app();

        virtual ~app();

        void start();

        void quit();

        void main_loop();

        virtual state initialize();

        virtual state running();

        virtual state finalize();

    protected:
        static app *instance;
        state current{ state::initialize };
        state next{ state::invalid };
    };
}
#pragma once

namespace SamEngine
{
    enum class ApplicationState
    {
        INITIALIZE,
        RUNNING,
        FINALIZE,
        EXIT,
    };

    class LAUNCHER_API IApplication
    {
    public:
        virtual ~IApplication() {}

        virtual ApplicationState Initialize() = 0;

        virtual ApplicationState Running() = 0;

        virtual ApplicationState Finalize() = 0;
    };
}
#include "Launcher.h"

namespace SamEngine
{
    void Launcher::SetApplication(IApplication *application)
    {
        mApplication = application;
    }

    void Launcher::Run()
    {
        s_assert(mApplication != nullptr);
        GetThread().Enter();
        while (ApplicationState::EXIT != mApplicationState)
        {
            calculateTime();
            GetThread().GetTicker().Execute(mTotalTickCount, mDeltaTickCount);
            switch (mApplicationState)
            {
            case ApplicationState::INITIALIZE:
                GetLog().Info("[Launcher] application initialze.\n");
                mApplicationState = mApplication->Initialize();
                break;
            case ApplicationState::RUNNING:
                mApplicationState = mApplication->Running();
                break;
            case ApplicationState::FINALIZE:
                GetLog().Info("[Launcher] application finalize.\n");
                mApplicationState = mApplication->Finalize();
                break;
            case ApplicationState::EXIT:
                s_error("[Launcher] should never reach here.\n");
                break;
            }
        }
        GetThread().Exit();
    }
}
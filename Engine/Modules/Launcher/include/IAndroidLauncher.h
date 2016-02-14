#pragma once

#if SAM_ANDROID

#include "IApplication.h"
#include "ILauncher.h"

#include <CoreModule.h>

#include <android_native_app_glue.h>

#define SamEngineAndroidApplication(clazz) \
    android_app *gAndroidApp = nullptr; \
    void android_main(android_app *app) \
    { \
        app_dummy(); \
        gAndroidApp = app; \
        auto application = new clazz; \
        SamEngine::GetLauncher().SetApplication(application); \
        SamEngine::GetLauncher().Run(); \
        delete application; \
        return 0; \
    }

#endif
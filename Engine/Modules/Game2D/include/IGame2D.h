#pragma once

#include "Core/ShaderManager.h"
#include "Display/Sprite.h"

#include <CoreModule.h>
#include <GraphicsModule.h>
#include <LauncherModule.h>

#define Game2DApplication(width, height, title, color, clazz) \
    class Game2DApplication : public SamEngine::IApplication \
    { \
    public: \
        SamEngine::ApplicationState Initialize() override \
        { \
            SamEngine::GetGame2D().Initialize(width, height, title, color, clazz::AsRoot); \
            return SamEngine::ApplicationState::RUNNING; \
        } \
        SamEngine::ApplicationState Running() override \
        { \
            return SamEngine::GetGame2D().Draw() ? SamEngine::ApplicationState::RUNNING : SamEngine::ApplicationState::FINALIZE; \
        } \
        SamEngine::ApplicationState Finalize() override \
        { \
            SamEngine::GetGame2D().Finalize(); \
            return SamEngine::ApplicationState::EXIT; \
        } \
    }; \
    SamEngineApplication(Game2DApplication)

namespace SamEngine
{
    class GAME2D_API IGame2D
    {
    public:
        virtual ~IGame2D() {}

        virtual void Initialize(int32 width, int32 height, const char *title, const Color &backgroundColor, RootCreator creator) = 0;

        virtual void Finalize() = 0;

        virtual bool Available() = 0;

        virtual bool Draw() = 0;

        virtual ShaderManager &GetShaderManager() = 0;

        virtual ResourceID GetDefaultProgram() = 0;

        virtual void UseDefaultShader() = 0;

        virtual glm::mat4 &GetProjectionMatrix() = 0;
    };

    extern GAME2D_API IGame2D &GetGame2D();
}
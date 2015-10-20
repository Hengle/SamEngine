#pragma once

#include "IGame2D.h"

namespace SamEngine
{
    class Game2D : public IGame2D
    {
    public:
        void Initialize(int32 width, int32 height, const char *title, const Color &backgroundColor, RootCreator creator) override;

        void Finalize() override;

        bool Available() override;

        bool Draw() override;

        ShaderManager &GetShaderManager() override;

        ResourceID GetDefaultProgram() override;

        void UseDefaultShader() override;

        glm::mat4 &GetProjectionMatrix() override;

    private:
        SpritePtr mRoot{ nullptr };
        ClearState mClearState;
        ShaderManager mShaderManager;
        ShaderID mDefaultShader{ InvalidShaderID };
        glm::mat4 mProjectionMatrix;
    };

    inline ShaderManager &Game2D::GetShaderManager()
    {
        return mShaderManager;
    }

    inline ResourceID Game2D::GetDefaultProgram()
    {
        return mShaderManager.GetProgram(0);
    }

    inline void Game2D::UseDefaultShader()
    {
        mShaderManager.UseShader(mDefaultShader);
    }

    inline glm::mat4 &Game2D::GetProjectionMatrix()
    {
        return mProjectionMatrix;
    }

    inline GAME2D_API IGame2D &GetGame2D()
    {
        static Game2D instance;
        return instance;
    }
}
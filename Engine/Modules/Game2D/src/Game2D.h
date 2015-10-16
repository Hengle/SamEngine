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

    private:
        SpritePtr mRoot{ nullptr };
        ClearState mClearState;
    };

    inline GAME2D_API IGame2D &GetGame2D()
    {
        static Game2D instance;
        return instance;
    }
}
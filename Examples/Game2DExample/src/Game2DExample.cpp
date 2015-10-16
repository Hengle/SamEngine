#include <Game2DModule.h>

using namespace SamEngine;

class Game2DExample : public Sprite
{
public:
    ROOT_CREATOR_FUNC_DECLEARE(Game2DExample)

    Game2DExample();
};

Game2DExample::Game2DExample()
{
    AddChild(Sprite::Create());
}

Game2DApplication(1024, 768, "Game2DExample", Color(0.5f, 0.5f, 0.5f, 0.5f), Game2DExample)
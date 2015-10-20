#include <Game2DModule.h>
#include <IOModule.h>
#include <HTTPModule.h>

using namespace SamEngine;

class Game2DExample : public Sprite
{
public:
    ROOT_CREATOR_FUNC_DECLEARE(Game2DExample)

    Game2DExample();
};

Game2DExample::Game2DExample()
{
    GetHTTP().Initialize();

    GetIO().SetFilesystemCreator("http", GetHTTPFilesystemCreator());
    GetIO().SetLocationPlaceholder("git", "http://leafnsand.com/");

    GetIO().Read("git:images/mario.png", [&](EventPtr &e)
    {
        if (e->GetStatus() == EventStatus::COMPLETE)
        {
            auto data = std::static_pointer_cast<IORequestReadEvent>(e)->GetData();
            if (data != nullptr)
            {
                AddChild(Image::Create(Texture::Create(data)));
            }
        }
    });
}

Game2DApplication(1024, 768, "Game2DExample", Color(0.5f, 0.5f, 0.5f, 0.5f), Game2DExample)
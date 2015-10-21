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

    SetPositionX(-500);
    SetPositionY(-350);

    GetIO().Read("git:images/mario.png", [&](EventPtr &e)
    {
        if (e->GetStatus() == EventStatus::COMPLETE)
        {
            auto data = std::static_pointer_cast<IORequestReadEvent>(e)->GetData();
            if (data != nullptr)
            {
                auto image = Image::Create(Texture::Create(data));
                image->SetPositionX(500);
                image->SetPositionY(350);
//                image->SetRotation(30);
//                image->SetScaleX(0.8);
//                image->SetScaleY(0.6);
                AddChild(image);
            }
        }
    });
}

Game2DApplication(1024, 768, "Game2DExample", Color(0.5f, 0.5f, 0.5f, 0.5f), Game2DExample)
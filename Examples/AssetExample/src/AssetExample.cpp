#include <CoreModule.h>
#include <LauncherModule.h>
#include <WindowModule.h>
#include <GraphicsModule.h>
#include <HTTPModule.h>
#include <IOModule.h>
#include <AssetModule.h>

using namespace SamEngine;

class AssetExample : public IApplication
{
public:
    ApplicationState Initialize() override;

    ApplicationState Running() override;

    ApplicationState Finalize() override;

private:
    ClearState mClearState;
    ImagePtr mImage{ nullptr };
};

ApplicationState AssetExample::Initialize()
{
    GetHTTP().Initialize();
    GetIO().Initialize();
    GetWindow().Initialize(WindowConfig::ForWindow(800, 600, "AssetExample"));
    GetGraphics().Initialize(GraphicsConfig());
    DefaultShader::Initialize();

    GetIO().SetFilesystemCreator("http", GetHTTPFilesystemCreator());
    GetIO().SetLocationPlaceholder("git", "http://leafnsand.com/");

    mImage = Image::Create(Texture::Create("git:images/mario.png"));

    mClearState.ClearColor = Color(0.5f, 0.5f, 0.5f, 1.0f);

    return ApplicationState::RUNNING;
}

ApplicationState AssetExample::Running()
{
    GetGraphics().GetRenderer().ApplyTarget();
    GetGraphics().GetRenderer().ApplyClearState(mClearState);
    if (mImage)
    {
        mImage->Draw();
    }
    GetGraphics().GetRenderer().Render();
    GetWindow().Present();
    return GetWindow().ShouldClose() ? ApplicationState::FINALIZE : ApplicationState::RUNNING;
}

ApplicationState AssetExample::Finalize()
{
    mImage.reset();
    DefaultShader::Finalize();
    GetHTTP().Finalize();
    GetIO().Finalize();
    GetGraphics().Finalize();
    GetWindow().Finalize();
    return ApplicationState::EXIT;
}

SamEngineApplication(AssetExample)
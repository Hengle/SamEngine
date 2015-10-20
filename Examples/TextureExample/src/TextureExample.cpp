#include <CoreModule.h>
#include <LauncherModule.h>
#include <WindowModule.h>
#include <GraphicsModule.h>
#include <HTTPModule.h>
#include <IOModule.h>
#include <AssetModule.h>

#include <gtc/matrix_transform.hpp>

using namespace SamEngine;

const char* vs =
"#version 150 core\n"
"in vec2 position;\n"
"in vec2 texcoord0;\n"
"uniform mat4 uProjectionMatrix;\n"
"out vec2 Texcoord;\n"
"void main() {\n"
"   Texcoord = texcoord0;\n"
"   gl_Position = uProjectionMatrix * vec4(position, 1.0, 1.0);\n"
"}";
const char* fs =
"#version 150 core\n"
"in vec2 Texcoord;\n"
"uniform sampler2D uTexture;\n"
"out vec4 outColor;\n"
"void main() {\n"
"   outColor = texture(uTexture, Texcoord);\n"
"}";

class TextureExample : public IApplication
{
public:
    ApplicationState Initialize() override;

    ApplicationState Running() override;

    ApplicationState Finalize() override;

private:
    ClearState mClearState;
    Mesh mMesh;
    UniformData mUniformData;
};

ApplicationState TextureExample::Initialize()
{
    GetHTTP().Initialize();
    GetIO().Initialize();
    GetWindow().Initialize(WindowConfig::ForWindow(800, 600, "TextureExample"));
    GetGraphics().Initialize(GraphicsConfig());

    GetIO().SetFilesystemCreator("http", GetHTTPFilesystemCreator());
    GetIO().SetLocationPlaceholder("git", "http://leafnsand.com/");

    TextureLoader::Load("git:images/mario.png", [&](ResourceID texture)
    {
        auto vertexShader = GetGraphics().GetResourceManager().Create(ShaderConfig::FromSource(ShaderType::VERTEX_SHADER, vs), nullptr);
        auto fragmentShader = GetGraphics().GetResourceManager().Create(ShaderConfig::FromSource(ShaderType::FRAGMENT_SHADER, fs), nullptr);
        auto program = GetGraphics().GetResourceManager().Create(ProgramConfig::FromShader(vertexShader, fragmentShader), nullptr);
        GetGraphics().GetRenderer().ApplyProgram(program);

        MeshConfig meshConfig(4, 6, IndexAttributeType::UINT16);
        meshConfig.VertexLayout()
            .Add(VertexAttributeType::POSITION, VertexAttributeFormat::FLOAT2)
            .Add(VertexAttributeType::TEXCOORD0, VertexAttributeFormat::FLOAT2);
        meshConfig.Start()
            .Vertex(0, VertexAttributeType::POSITION, 0.0f, 768.0f)
            .Vertex(0, VertexAttributeType::TEXCOORD0, 0.0f, 0.0f)
            .Vertex(1, VertexAttributeType::POSITION, 610.0f, 768.0f)
            .Vertex(1, VertexAttributeType::TEXCOORD0, 1.0f, 0.0f)
            .Vertex(2, VertexAttributeType::POSITION, 610.0f, 0.0f)
            .Vertex(2, VertexAttributeType::TEXCOORD0, 1.0f, 1.0f)
            .Vertex(3, VertexAttributeType::POSITION, 0.0f, 0.0f)
            .Vertex(3, VertexAttributeType::TEXCOORD0, 0.0f, 1.0f)
            .IndexQuad16(0, 1, 2, 3)
            .Finish()
            .DrawCall(DrawType::TRIANGLES, 0, 6);
        mMesh.Create(meshConfig);

        UniformDataConfig uniformConfig(program);
        uniformConfig.Layout()
            .Add("uProjectionMatrix", UniformAttributeFormat::MATRIX4)
            .Add("uTexture", UniformAttributeFormat::TEXTURE);
        mUniformData.Create(uniformConfig);
        auto projectionMatrix = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
        mUniformData.SetUniformData("uProjectionMatrix", projectionMatrix);
        mUniformData.SetUniformData("uTexture", texture);
    });

    mClearState.ClearColor = Color(0.5f, 0.5f, 0.5f, 1.0f);

    return ApplicationState::RUNNING;
}

ApplicationState TextureExample::Running()
{
    GetGraphics().GetRenderer().ApplyTarget();
    GetGraphics().GetRenderer().ApplyClearState(mClearState);
    mUniformData.Apply();
    mMesh.Draw();
    GetGraphics().GetRenderer().Render();
    GetWindow().Present();
    return GetWindow().ShouldClose() ? ApplicationState::FINALIZE : ApplicationState::RUNNING;
}

ApplicationState TextureExample::Finalize()
{
    mMesh.Destroy();
    mUniformData.Destroy();
    GetHTTP().Finalize();
    GetIO().Finalize();
    GetGraphics().Finalize();
    GetWindow().Finalize();
    return ApplicationState::EXIT;
}

SamEngineApplication(TextureExample)
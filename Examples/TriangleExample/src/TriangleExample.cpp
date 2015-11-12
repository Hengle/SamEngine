#include <CoreModule.h>
#include <LauncherModule.h>
#include <WindowModule.h>
#include <GraphicsModule.h>

using namespace SamEngine;

const char* vs =
"#version 150 core\n"
"in vec2 aPosition;\n"
"in vec4 aColor0;\n"
"out vec4 vColor;\n"
"void main() {\n"
"   vColor = aColor0;\n"
"   gl_Position = vec4(aPosition, 0.0, 1.0);\n"
"}";
const char* fs =
"#version 150 core\n"
"in vec4 vColor;\n"
"out vec4 outColor;\n"
"void main() {\n"
"   outColor = vColor;\n"
"}";

class TriangleExample : public IApplication
{
public:
    ApplicationState Initialize() override;

    ApplicationState Running() override;

    ApplicationState Finalize() override;

private:
    ClearState mClearState;
};

ApplicationState TriangleExample::Initialize()
{
    GetWindow().Initialize(WindowConfig::ForWindow(800, 600, "TriangleExample"));
    GetGraphics().Initialize(GraphicsConfig());

    mClearState.ClearColor = Color(0.5f, 0.5f, 0.5f, 1.0f);

    float vertices[] = {
        0.0f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
    };
    auto data = Data::Create();
    data->Copy(vertices, sizeof(vertices));

    VertexBufferConfig config;
    config.Count = 3;
    config.Layout.Add(VertexAttributeType::POSITION, VertexAttributeFormat::FLOAT2);
    config.Layout.Add(VertexAttributeType::COLOR0, VertexAttributeFormat::FLOAT4);
    auto vertexBuffer = GetGraphics().GetResourceManager().Create(config, data);
    GetGraphics().GetRenderer().ApplyVertexBuffer(vertexBuffer);

    auto vertexShader = GetGraphics().GetResourceManager().Create(ShaderConfig::FromSource(ShaderType::VERTEX_SHADER, vs), nullptr);
    auto fragmentShader = GetGraphics().GetResourceManager().Create(ShaderConfig::FromSource(ShaderType::FRAGMENT_SHADER, fs), nullptr);
    auto program = GetGraphics().GetResourceManager().Create(ProgramConfig::FromShader(vertexShader, fragmentShader), nullptr);
    GetGraphics().GetRenderer().ApplyProgram(program);

    return ApplicationState::RUNNING;
}

ApplicationState TriangleExample::Running()
{
    GetGraphics().GetRenderer().ApplyTarget();
    GetGraphics().GetRenderer().ApplyClearState(mClearState);
    GetGraphics().GetRenderer().Draw(DrawType::TRIANGLES, 0, 3);
    GetGraphics().GetRenderer().Render();
    GetWindow().Present();
    return GetWindow().ShouldClose() ? ApplicationState::FINALIZE : ApplicationState::RUNNING;
}

ApplicationState TriangleExample::Finalize()
{
    GetGraphics().Finalize();
    GetWindow().Finalize();
    return ApplicationState::EXIT;
}

SamEngineApplication(TriangleExample)
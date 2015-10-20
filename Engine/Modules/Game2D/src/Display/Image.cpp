#include "Display/Image.h"

#include "IGame2D.h"

namespace SamEngine
{
    Image::Image(TexturePtr texture)
    {
        SetTexture(texture);
    }

    void Image::Draw()
    {
        mUniformData.SetUniformData("uMVPMatrix", glm::mat4(1.0f));
        mUniformData.Apply();
        mMesh.Draw();
    }

    void Image::SetTexture(TexturePtr value)
    {
        mMesh.Destroy();
        mUniformData.Destroy();
        mTexture = value;
        mWidth = mTexture->GetWidth();
        mHeight = mTexture->GetHeight();

        MeshConfig meshConfig(4, 6, IndexAttributeType::UINT16);
        meshConfig.VertexLayout().Add(VertexAttributeType::POSITION, VertexAttributeFormat::FLOAT2)
            .Add(VertexAttributeType::TEXCOORD0, VertexAttributeFormat::FLOAT2);
        meshConfig.Start()
            .Vertex(0, VertexAttributeType::POSITION, 0.0f, mHeight)
            .Vertex(0, VertexAttributeType::TEXCOORD0, 0.0f, 0.0f)
            .Vertex(1, VertexAttributeType::POSITION, mWidth, mHeight)
            .Vertex(1, VertexAttributeType::TEXCOORD0, 1.0f, 0.0f)
            .Vertex(2, VertexAttributeType::POSITION, mWidth, 0.0f)
            .Vertex(2, VertexAttributeType::TEXCOORD0, 1.0f, 1.0f)
            .Vertex(3, VertexAttributeType::POSITION, 0.0f, 0.0f)
            .Vertex(3, VertexAttributeType::TEXCOORD0, 0.0f, 1.0f)
            .IndexQuad16(0, 1, 2, 3)
            .Finish()
            .DrawCall(DrawType::TRIANGLES, 0, 6);
        mMesh.Create(meshConfig);

        UniformDataConfig uniformConfig(GetGame2D().GetDefaultProgram());
        uniformConfig.Layout()
            .Add("uProjectionMatrix", UniformAttributeFormat::MATRIX4)
            .Add("uMVPMatrix", UniformAttributeFormat::MATRIX4)
            .Add("uTexture", UniformAttributeFormat::TEXTURE);
        mUniformData.Create(uniformConfig);

        mUniformData.SetUniformData("uProjectionMatrix", GetGame2D().GetProjectionMatrix());
        auto texture = mTexture->GetGraphicsTexture();
        mUniformData.SetUniformData("uTexture", texture);
    }
}
#include "Graphics/Image.h"
#include "Graphics/ImageShader.h"

#include <WindowModule.h>

namespace SamEngine
{
    Image::Image(TexturePtr texture) :
        mTexture(texture),
        mWidth(texture->GetWidth()),
        mHeight(texture->GetHeight())
    {
        MeshConfig meshConfig(4, 6, IndexAttributeType::UINT16);
        meshConfig.VertexLayout().Add(VertexAttributeType::POSITION, VertexAttributeFormat::FLOAT2)
            .Add(VertexAttributeType::TEXCOORD0, VertexAttributeFormat::FLOAT2);
        meshConfig.Start()
            .Vertex(0, VertexAttributeType::POSITION, 0.0f, mHeight * mScale.y)
            .Vertex(0, VertexAttributeType::TEXCOORD0, mTexture->GetNormalizedLeft(), mTexture->GetNormalizedTop())
            .Vertex(1, VertexAttributeType::POSITION, mWidth * mScale.x, mHeight * mScale.y)
            .Vertex(1, VertexAttributeType::TEXCOORD0, mTexture->GetNormalizedRight(), mTexture->GetNormalizedTop())
            .Vertex(2, VertexAttributeType::POSITION, mWidth * mScale.x, 0.0f)
            .Vertex(2, VertexAttributeType::TEXCOORD0, mTexture->GetNormalizedRight(), mTexture->GetNormalizedBottom())
            .Vertex(3, VertexAttributeType::POSITION, 0.0f, 0.0f)
            .Vertex(3, VertexAttributeType::TEXCOORD0, mTexture->GetNormalizedLeft(), mTexture->GetNormalizedBottom())
            .IndexQuad16(0, 1, 2, 3)
            .Finish()
            .DrawCall(DrawType::TRIANGLES, 0, 6);
        mMesh.Create(meshConfig);
        UniformDataConfig uniformConfig(ImageShader::GetResourceID());
        uniformConfig.Layout()
            .Add("uProjectionMatrix", UniformAttributeFormat::MATRIX4)
            .Add("uModelViewMatrix", UniformAttributeFormat::MATRIX4)
            .Add("uTexture", UniformAttributeFormat::TEXTURE);
        mUniformData.Create(uniformConfig);
        mUniformData.SetUniformData(0, glm::ortho(0.0f, static_cast<float32>(GetWindow().GetConfig().Width), 0.0f, static_cast<float32>(GetWindow().GetConfig().Height)));
        mUniformData.SetUniformData(2, mTexture);
    }

    void Image::Draw()
    {
        mUniformData.SetUniformData(1, GetModelMatrix());
        mUniformData.Apply();
        mMesh.Draw();
    }

    void Image::UpdateVertices()
    {
        MeshConfig meshConfig(4, 0);
        meshConfig.VertexLayout().Add(VertexAttributeType::POSITION, VertexAttributeFormat::FLOAT2)
            .Add(VertexAttributeType::TEXCOORD0, VertexAttributeFormat::FLOAT2);
        meshConfig.Start()
            .Vertex(0, VertexAttributeType::POSITION, 0.0f, mHeight * mScale.y)
            .Vertex(0, VertexAttributeType::TEXCOORD0, mTexture->GetNormalizedLeft(), mTexture->GetNormalizedTop())
            .Vertex(1, VertexAttributeType::POSITION, mWidth * mScale.x, mHeight * mScale.y)
            .Vertex(1, VertexAttributeType::TEXCOORD0, mTexture->GetNormalizedRight(), mTexture->GetNormalizedTop())
            .Vertex(2, VertexAttributeType::POSITION, mWidth * mScale.x, 0.0f)
            .Vertex(2, VertexAttributeType::TEXCOORD0, mTexture->GetNormalizedRight(), mTexture->GetNormalizedBottom())
            .Vertex(3, VertexAttributeType::POSITION, 0.0f, 0.0f)
            .Vertex(3, VertexAttributeType::TEXCOORD0, mTexture->GetNormalizedLeft(), mTexture->GetNormalizedBottom())
            .Finish();
        mMesh.UpdateVertices(meshConfig);
    }
}
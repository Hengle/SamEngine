#include "2D/Image.h"
#include "2D/ImageShader.h"

namespace SamEngine
{
    Image::Image(TexturePtr texture)
    {
        MeshConfig meshConfig(4, 6, IndexAttributeType::UINT16, BufferUsage::DYNAMIC);
        meshConfig.VertexLayout().Add(VertexAttributeType::POSITION, VertexAttributeFormat::FLOAT2)
            .Add(VertexAttributeType::TEXCOORD0, VertexAttributeFormat::FLOAT2);
        meshConfig.BeginIndex()
            .IndexQuad16(0, 1, 2, 3)
            .EndIndex()
            .DrawCall(DrawType::TRIANGLES, 0, 6);
        mMesh.Create(meshConfig);
        SetTexture(texture);
    }

    void Image::Draw()
    {
        if (mTexture != nullptr)
        {
            Blend::Apply(mBlendMode);
            ImageShader::SetUniformData(1, GetModelMatrix());
            ImageShader::SetUniformData(2, mTexture);
            ImageShader::Apply();
            mMesh.Draw();
        }
    }

    void Image::UpdateVertices()
    {
        if (mTexture != nullptr)
        {
            MeshConfig meshConfig(4, 0);
            meshConfig.VertexLayout().Add(VertexAttributeType::POSITION, VertexAttributeFormat::FLOAT2)
                .Add(VertexAttributeType::TEXCOORD0, VertexAttributeFormat::FLOAT2);
            meshConfig.BeginVertex()
                .Vertex(0, VertexAttributeType::POSITION, 0.0f, mTexture->GetHeight() * std::abs(mScale.y))
                .Vertex(0, VertexAttributeType::TEXCOORD0, mTexture->GetNormalizedLeft(), mTexture->GetNormalizedTop())
                .Vertex(1, VertexAttributeType::POSITION, mTexture->GetWidth() * std::abs(mScale.x), mTexture->GetHeight() * std::abs(mScale.y))
                .Vertex(1, VertexAttributeType::TEXCOORD0, mTexture->GetNormalizedRight(), mTexture->GetNormalizedTop())
                .Vertex(2, VertexAttributeType::POSITION, mTexture->GetWidth() * std::abs(mScale.x), 0.0f)
                .Vertex(2, VertexAttributeType::TEXCOORD0, mTexture->GetNormalizedRight(), mTexture->GetNormalizedBottom())
                .Vertex(3, VertexAttributeType::POSITION, 0.0f, 0.0f)
                .Vertex(3, VertexAttributeType::TEXCOORD0, mTexture->GetNormalizedLeft(), mTexture->GetNormalizedBottom())
                .EndVertex();
            mMesh.UpdateVertices(meshConfig);
        }
    }
}
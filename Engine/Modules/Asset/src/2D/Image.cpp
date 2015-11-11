#include "2D/Image.h"

namespace SamEngine
{
    Image::Image(TexturePtr texture)
    {
        mShader = DefaultShaders::GetShader(DefaultShaderType::IMAGE_TEXTURE);
        VertexBuilder vertex(4, BufferUsage::DYNAMIC);
        vertex.Layout().Add(VertexAttributeType::POSITION, VertexAttributeFormat::FLOAT2)
            .Add(VertexAttributeType::TEXCOORD0, VertexAttributeFormat::FLOAT2);
        IndexBuilder index(6, IndexAttributeType::UINT16);
        index.Begin()
            .IndexQuad16(0, 0, 1, 2, 3)
            .End();
        mMesh = Mesh::Create(vertex, index);
        mMesh->AddDrawCall(DrawType::TRIANGLES, 0, 6);
        SetTexture(texture);
    }

    void Image::Draw()
    {
        if (mTexture != nullptr && mTexture->Available())
        {
            VertexBuilder builder(4, BufferUsage::DYNAMIC);
            builder.Layout().Add(VertexAttributeType::POSITION, VertexAttributeFormat::FLOAT2)
                .Add(VertexAttributeType::TEXCOORD0, VertexAttributeFormat::FLOAT2);
            builder.Begin()
                .Vertex(0, VertexAttributeType::POSITION, 0.0f, mTexture->GetHeight() * std::abs(mScale.y))
                .Vertex(0, VertexAttributeType::TEXCOORD0, mTexture->GetNormalizedLeft(), mTexture->GetNormalizedTop())
                .Vertex(1, VertexAttributeType::POSITION, mTexture->GetWidth() * std::abs(mScale.x), mTexture->GetHeight() * std::abs(mScale.y))
                .Vertex(1, VertexAttributeType::TEXCOORD0, mTexture->GetNormalizedRight(), mTexture->GetNormalizedTop())
                .Vertex(2, VertexAttributeType::POSITION, mTexture->GetWidth() * std::abs(mScale.x), 0.0f)
                .Vertex(2, VertexAttributeType::TEXCOORD0, mTexture->GetNormalizedRight(), mTexture->GetNormalizedBottom())
                .Vertex(3, VertexAttributeType::POSITION, 0.0f, 0.0f)
                .Vertex(3, VertexAttributeType::TEXCOORD0, mTexture->GetNormalizedLeft(), mTexture->GetNormalizedBottom())
                .End();
            mMesh->UpdateVertices(builder);
            Blend::Apply(mBlendMode);
            mShader->SetUniformData(static_cast<uint8>(DefaultShaderUniformIndex::TEXTURE), mTexture);
            mShader->SetUniformData(static_cast<uint8>(DefaultShaderUniformIndex::MODEL_VIEW_MATRIX), GetModelMatrix());
            mShader->Apply();
            mMesh->Draw();
        }
    }
}
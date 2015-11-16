#include "2D/Image.h"
#include "2D/ImageBatcher.h"
#include "2D/DefaultShader.h"
#include "Util/IndexBuilder.h"

namespace SamEngine
{
    ImageBatcher::State *ImageBatcher::mState{ nullptr };

    void ImageBatcher::Initialize()
    {
        s_assert(mState == nullptr);
        s_assert(GetGraphics().Available());
        mState = new State;
        IndexBuilder builder(std::numeric_limits<uint16>::max(), IndexAttributeType::UINT16, BufferUsage::STATIC);
        builder.Begin();
        for (auto i = 0; i < std::numeric_limits<uint16>::max() / 6; ++i)
        {
            builder.IndexQuad16(i * 6, i, i * 4 + 1, i * 4 + 2, i * 4 + 3);
        }
        builder.End();
        mState->mIndexBuffer = GetGraphics().GetResourceManager().Create(builder.GetConfig(), builder.GetData());
        mState->mVertexBuilder.Layout()
            .Add(VertexAttributeType::POSITION, VertexAttributeFormat::FLOAT2)
            .Add(VertexAttributeType::TEXCOORD0, VertexAttributeFormat::FLOAT2)
            .Add(VertexAttributeType::COLOR0, VertexAttributeFormat::FLOAT4);
        mState->mVertexBuffer = GetGraphics().GetResourceManager().Create(mState->mVertexBuilder.GetConfig(), nullptr);
        mState->mVertexBuilder.Begin();
    }

    void ImageBatcher::Finalize()
    {
        s_assert(mState != nullptr);
        s_assert(GetGraphics().Available());
        GetGraphics().GetResourceManager().Destroy(mState->mVertexBuffer);
        GetGraphics().GetResourceManager().Destroy(mState->mIndexBuffer);
        delete mState;
    }

    void ImageBatcher::AddImage(Image *image)
    {
        s_assert(mState != nullptr);
        auto blendMode = image->GetBlendMode();
        auto color = image->GetColor();
        auto texture = image->GetTexture();
        auto matrix = image->GetModelMatrix();
        auto scaleX = std::abs(image->GetScaleX());
        auto scaleY = std::abs(image->GetScaleY());
        auto left = texture->GetOffsetX() * scaleX;
        auto right = (texture->GetWidth() + texture->GetOffsetX()) * scaleX;
        auto top = (texture->GetHeight() + texture->GetOffsetY()) * scaleY;
        auto bottom = texture->GetOffsetY() * scaleY;
        if (mState->mBlendMode != blendMode || mState->mTexture != texture)
        {
            Flush();
            mState->mBlendMode = blendMode;
            mState->mTexture = texture;
        }
        auto position = matrix * glm::vec4(left, top, 1.0f, 1.0f);
        auto uv = texture->TransformUV({ 0.0f, 0.0f });
        mState->mVertexBuilder
            .Vertex(mState->mImageCount * 4, VertexAttributeType::POSITION, position.x, position.y)
            .Vertex(mState->mImageCount * 4, VertexAttributeType::TEXCOORD0, uv.x, uv.y)
            .Vertex(mState->mImageCount * 4, VertexAttributeType::COLOR0, color.r, color.g, color.b, color.a);
        position = matrix * glm::vec4(right, top, 1.0f, 1.0f);
        uv = texture->TransformUV({ 1.0f, 0.0f });
        mState->mVertexBuilder
            .Vertex(mState->mImageCount * 4 + 1, VertexAttributeType::POSITION, position.x, position.y)
            .Vertex(mState->mImageCount * 4 + 1, VertexAttributeType::TEXCOORD0, uv.x, uv.y)
            .Vertex(mState->mImageCount * 4 + 1, VertexAttributeType::COLOR0, color.r, color.g, color.b, color.a);
        position = matrix * glm::vec4(right, bottom, 1.0f, 1.0f);
        uv = texture->TransformUV({ 1.0f, 1.0f });
        mState->mVertexBuilder
            .Vertex(mState->mImageCount * 4 + 2, VertexAttributeType::POSITION, position.x, position.y)
            .Vertex(mState->mImageCount * 4 + 2, VertexAttributeType::TEXCOORD0, uv.x, uv.y)
            .Vertex(mState->mImageCount * 4 + 2, VertexAttributeType::COLOR0, color.r, color.g, color.b, color.a);
        position = matrix * glm::vec4(left, bottom, 1.0f, 1.0f);
        uv = texture->TransformUV({ 0.0f, 1.0f });
        mState->mVertexBuilder
            .Vertex(mState->mImageCount * 4 + 3, VertexAttributeType::POSITION, position.x, position.y)
            .Vertex(mState->mImageCount * 4 + 3, VertexAttributeType::TEXCOORD0, uv.x, uv.y)
            .Vertex(mState->mImageCount * 4 + 3, VertexAttributeType::COLOR0, color.r, color.g, color.b, color.a);
        ++mState->mImageCount;
    }

    void ImageBatcher::Flush()
    {
        s_assert(mState != nullptr);
        if (mState->mImageCount > 0)
        {
            mState->mVertexBuilder.End();
            if (mState->mTexture != nullptr && mState->mTexture->Available())
            {
                Blend::Apply(mState->mBlendMode);
                DefaultShader::GetShader(DefaultShaderType::IMAGE_TEXTURE)->SetUniformData(static_cast<uint8>(DefaultShaderUniformIndex::TEXTURE), mState->mTexture);
                DefaultShader::GetShader(DefaultShaderType::IMAGE_TEXTURE)->SetUniformData(static_cast<uint8>(DefaultShaderUniformIndex::MODEL_VIEW_MATRIX), glm::mat4());
                DefaultShader::GetShader(DefaultShaderType::IMAGE_TEXTURE)->Apply();
                GetGraphics().GetRenderer().UpdateVertexBufferData(mState->mVertexBuffer, 0, mState->mVertexBuilder.GetData()->GetBuffer(), mState->mVertexBuilder.GetData()->GetSize());
                GetGraphics().GetRenderer().ApplyVertexBuffer(mState->mVertexBuffer);
                GetGraphics().GetRenderer().ApplyIndexBuffer(mState->mIndexBuffer);
                GetGraphics().GetRenderer().Draw(DrawType::TRIANGLES, 0, mState->mImageCount * 6);
            }
            mState->mVertexBuilder.Clear();
            mState->mVertexBuilder.Begin();
            mState->mImageCount = 0;
        }
    }
}
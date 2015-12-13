#include "2D/Spine.h"
#include "2D/DefaultShader.h"
#include "Core/Texture.h"

#include <StorageModule.h>

#include <spine/extension.h>
#include <spine/SkeletonJson.h>
#include <spine/AnimationState.h>
#include <spine/Skeleton.h>
#include <spine/Atlas.h>

void _spAtlasPage_createTexture(spAtlasPage *self, const char *path)
{
    auto texture = new SamEngine::Texture(path);
    self->rendererObject = texture;
    self->width = texture->GetWidth();
    self->height = texture->GetHeight();
}

void _spAtlasPage_disposeTexture(spAtlasPage *self)
{
    delete static_cast<SamEngine::Texture *>(self->rendererObject);
}

char *_spUtil_readFile(const char *path, int *length)
{
    return nullptr;
}

namespace SamEngine
{
    SpineAtlas::SpineAtlas(const std::string &atlas)
    {
        auto atlasData = GetIO().Read(atlas);
        if (atlasData)
        {
            auto location = GetIO().ResolveLocation(atlas);
            mAtlas.reset(spAtlas_create(reinterpret_cast<const char *>(atlasData->GetBuffer()), atlasData->GetSize(), location.GetDir().c_str(), nullptr), spAtlas_dispose);
        }
    }

    SpineSkeletonData::SpineSkeletonData(const std::string &json, SpineAtlasPtr atlas)
    {
        s_assert(atlas && atlas->GetAtlas());
        std::shared_ptr<spSkeletonJson> skeletonJson(spSkeletonJson_create(atlas->GetAtlas().get()), spSkeletonJson_dispose);
        auto jsonData = GetIO().Read(json);
        if (jsonData)
        {
            mData.reset(spSkeletonJson_readSkeletonData(skeletonJson.get(), reinterpret_cast<const char *>(jsonData->GetBuffer())), spSkeletonData_dispose);
        }
    }

    Spine::Spine(SpineSkeletonDataPtr skeleton) :
        mSkeletonData(skeleton)
    {
        s_assert(mSkeletonData && mSkeletonData->GetData());
        mSkeleton.reset(spSkeleton_create(mSkeletonData->GetData().get()), spSkeleton_dispose);
        mIndexBuffer = GetGraphics().GetResourceManager().Create(mIndexBuilder.GetConfig(), nullptr);
        mIndexBuilder.Begin();
        mVertexBuilder.Layout()
            .Add(VertexAttributeType::POSITION, VertexAttributeFormat::FLOAT2)
            .Add(VertexAttributeType::TEXCOORD0, VertexAttributeFormat::FLOAT2)
            .Add(VertexAttributeType::COLOR0, VertexAttributeFormat::FLOAT4);
        mVertexBuffer = GetGraphics().GetResourceManager().Create(mVertexBuilder.GetConfig(), nullptr);
        mVertexBuilder.Begin();
        mStateData.reset(spAnimationStateData_create(mSkeleton->data), spAnimationStateData_dispose);
        mState.reset(spAnimationState_create(mStateData.get()), spAnimationState_dispose);
        // add listener
    }

    Spine::~Spine()
    {
        GetGraphics().GetResourceManager().Destroy(mIndexBuffer);
        GetGraphics().GetResourceManager().Destroy(mVertexBuffer);
    }

    void Spine::SetMixTime(const std::string &from, const std::string &to, TickCount time)
    {
        if (mState)
        {
            spAnimationStateData_setMixByName(mState->data, from.c_str(), to.c_str(), time / 1000.0f);
        }
    }

    void Spine::SetAnimation(int32 index, const std::string &name, bool loop)
    {
        if (mState)
        {
            spAnimationState_setAnimationByName(mState.get(), index, name.c_str(), loop);
        }
    }

    void Spine::AddAnimation(int32 index, const std::string &name, bool loop, TickCount delay)
    {
        if (mState)
        {
            spAnimationState_addAnimationByName(mState.get(), index, name.c_str(), loop, delay / 1000.0f);
        }
    }

    std::string Spine::GetAnimation(int32 index)
    {
        std::string name = "";
        if (mState)
        {
            auto entry = spAnimationState_getCurrent(mState.get(), index);
            if (entry)
            {
                auto animation = entry->animation;
                if (animation)
                {
                    name = animation->name;
                }
            }
        }
        return name;
    }

    void Spine::Clear(int32 index)
    {
        if (mState)
        {
            spAnimationState_clearTrack(mState.get(), index);
        }
    }

    void Spine::ClearAll()
    {
        if (mState)
        {
            spAnimationState_clearTracks(mState.get());
        }
    }

    void Spine::Update(TickCount delta)
    {
        if (mSkeleton && mState)
        {
            spSkeleton_update(mSkeleton.get(), delta / 1000.0f);
            spAnimationState_update(mState.get(), delta / 1000.0f);
            spAnimationState_apply(mState.get(), mSkeleton.get());
            spSkeleton_updateWorldTransform(mSkeleton.get());
        }
    }

    void Spine::Draw()
    {
        auto blendMode = BlendMode::PRE_MULTIPLIED;
        Texture *texture = nullptr;
        auto vertexCount = 0;
        auto indexCount = 0;
        for (auto slotIndex = 0; slotIndex < mSkeleton->slotsCount; ++slotIndex)
        {
            auto slot = mSkeleton->drawOrder[slotIndex];
            if (slot && slot->attachment)
            {
                BlendMode slotBlendMode;
                Texture *slotTexture;
                switch (slot->data->blendMode)
                {
                case SP_BLEND_MODE_ADDITIVE:
                    slotBlendMode = BlendMode::ADD;
                    break;
                case SP_BLEND_MODE_MULTIPLY:
                    slotBlendMode = BlendMode::MULTIPLY;
                    break;
                case SP_BLEND_MODE_SCREEN:
                    slotBlendMode = BlendMode::SCREEN;
                    break;
                case SP_BLEND_MODE_NORMAL:
                default:
                    slotBlendMode = BlendMode::PRE_MULTIPLIED;
                    break;
                }
                if (slotBlendMode != blendMode)
                {
                    Flush(texture, blendMode, vertexCount, indexCount);
                    blendMode = slotBlendMode;
                }
                switch (slot->attachment->type)
                {
                case SP_ATTACHMENT_REGION:
                {
                    auto attachment = SUB_CAST(spRegionAttachment, slot->attachment);
                    slotTexture = static_cast<Texture *>(SUB_CAST(spAtlasRegion, attachment->rendererObject)->page->rendererObject);
                    if (slotTexture != texture)
                    {
                        Flush(texture, blendMode, vertexCount, indexCount);
                        texture = slotTexture;
                    }
                    spRegionAttachment_computeWorldVertices(attachment, slot->bone, mWorldVertices.data());
                    auto r = static_cast<uint8>(mSkeleton->r * slot->r * attachment->r);
                    auto g = static_cast<uint8>(mSkeleton->g * slot->g * attachment->g);
                    auto b = static_cast<uint8>(mSkeleton->b * slot->b * attachment->b);
                    auto a = static_cast<uint8>(mSkeleton->a * slot->a * attachment->a);
                    for (auto vertexIndex = 0; vertexIndex < 4; ++vertexIndex)
                    {
                        mVertexBuilder
                            .Vertex(vertexCount + vertexIndex, VertexAttributeType::POSITION, mWorldVertices[vertexIndex * 2], mWorldVertices[vertexIndex * 2 + 1])
                            .Vertex(vertexCount + vertexIndex, VertexAttributeType::TEXCOORD0, attachment->uvs[vertexIndex * 2], attachment->uvs[vertexIndex * 2 + 1])
                            .Vertex(vertexCount + vertexIndex, VertexAttributeType::COLOR0, r, g, b, a);
                    }
                    mIndexBuilder.IndexQuad16(indexCount, vertexCount, vertexCount + 1, vertexCount + 2, vertexCount + 3);
                    vertexCount += 4;
                    indexCount += 6;
                    break;
                }
                case SP_ATTACHMENT_BOUNDING_BOX:
                {
                    auto attachment = SUB_CAST(spBoundingBoxAttachment, slot->attachment);
                    break;
                }
                case SP_ATTACHMENT_MESH:
                {
                    auto attachment = SUB_CAST(spMeshAttachment, slot->attachment);
                    s_assert(attachment->verticesCount < SPINE_MESH_VERTEX_COUNT_MAX);
                    slotTexture = static_cast<Texture *>(SUB_CAST(spAtlasRegion, attachment->rendererObject)->page->rendererObject);
                    if (slotTexture != texture)
                    {
                        Flush(texture, blendMode, vertexCount, indexCount);
                        texture = slotTexture;
                    }
                    spMeshAttachment_computeWorldVertices(attachment, slot, mWorldVertices.data());
                    auto r = static_cast<uint8>(mSkeleton->r * slot->r * attachment->r);
                    auto g = static_cast<uint8>(mSkeleton->g * slot->g * attachment->g);
                    auto b = static_cast<uint8>(mSkeleton->b * slot->b * attachment->b);
                    auto a = static_cast<uint8>(mSkeleton->a * slot->a * attachment->a);
                    for (auto vertexIndex = 0; vertexIndex < attachment->trianglesCount; ++vertexIndex)
                    {
                        auto index = attachment->triangles[vertexIndex] << 1;
                        mVertexBuilder
                            .Vertex(vertexCount, VertexAttributeType::POSITION, mWorldVertices[index], mWorldVertices[index + 1])
                            .Vertex(vertexCount, VertexAttributeType::TEXCOORD0, attachment->uvs[index], attachment->uvs[index + 1])
                            .Vertex(vertexCount, VertexAttributeType::COLOR0, r, g, b, a);
                        mIndexBuilder.IndexUint16(indexCount, vertexCount);
                        ++indexCount;
                        ++vertexCount;
                    }
                    break;
                }
                case SP_ATTACHMENT_SKINNED_MESH:
                {
                    auto attachment = SUB_CAST(spSkinnedMeshAttachment, slot->attachment);
                    s_assert(attachment->uvsCount < SPINE_MESH_VERTEX_COUNT_MAX);
                    slotTexture = static_cast<Texture *>(SUB_CAST(spAtlasRegion, attachment->rendererObject)->page->rendererObject);
                    if (slotTexture != texture)
                    {
                        Flush(texture, blendMode, vertexCount, indexCount);
                        texture = slotTexture;
                    }
                    spSkinnedMeshAttachment_computeWorldVertices(attachment, slot, mWorldVertices.data());
                    auto r = static_cast<uint8>(mSkeleton->r * slot->r * attachment->r);
                    auto g = static_cast<uint8>(mSkeleton->g * slot->g * attachment->g);
                    auto b = static_cast<uint8>(mSkeleton->b * slot->b * attachment->b);
                    auto a = static_cast<uint8>(mSkeleton->a * slot->a * attachment->a);
                    for (auto triangleIndex = 0; triangleIndex < attachment->trianglesCount; ++triangleIndex)
                    {
                        auto index = attachment->triangles[triangleIndex] << 1;
                        mVertexBuilder
                            .Vertex(vertexCount, VertexAttributeType::POSITION, mWorldVertices[index], mWorldVertices[index + 1])
                            .Vertex(vertexCount, VertexAttributeType::TEXCOORD0, attachment->uvs[index], attachment->uvs[index + 1])
                            .Vertex(vertexCount, VertexAttributeType::COLOR0, r, g, b, a);
                        mIndexBuilder.IndexUint16(indexCount, vertexCount);
                        ++indexCount;
                        ++vertexCount;
                    }
                    break;
                }
                default:
                    break;
                }
            }
        }
        Flush(texture, blendMode, vertexCount, indexCount);
    }

    void Spine::Flush(Texture *texture, BlendMode mode, int32 &vertexCount, int32 &indexCount)
    {
        if (vertexCount > 0 && indexCount > 0)
        {
            mIndexBuilder.End();
            mVertexBuilder.End();
            if (texture)
            {
                Blend::Apply(mode);
                DefaultShader::GetShader(DefaultShaderType::IMAGE_TEXTURE)->SetUniformData(static_cast<uint8>(DefaultShaderUniformIndex::TEXTURE), *texture);
                DefaultShader::GetShader(DefaultShaderType::IMAGE_TEXTURE)->SetUniformData(static_cast<uint8>(DefaultShaderUniformIndex::MODEL_VIEW_MATRIX), GetModelMatrix());
                DefaultShader::GetShader(DefaultShaderType::IMAGE_TEXTURE)->Apply();
                GetGraphics().GetRenderer().UpdateIndexBufferData(mIndexBuffer, 0, mIndexBuilder.GetData()->GetBuffer(), indexCount * SizeOfIndexAttributeType(mIndexBuilder.GetConfig().Type));
                GetGraphics().GetRenderer().UpdateVertexBufferData(mVertexBuffer, 0, mVertexBuilder.GetData()->GetBuffer(), vertexCount * mVertexBuilder.GetConfig().Layout.Size());
                GetGraphics().GetRenderer().ApplyVertexBuffer(mVertexBuffer);
                GetGraphics().GetRenderer().ApplyIndexBuffer(mIndexBuffer);
                GetGraphics().GetRenderer().Draw(DrawType::TRIANGLES, 0, indexCount);
            }
            mIndexBuilder.Clear();
            mVertexBuilder.Clear();
            mIndexBuilder.Begin();
            mVertexBuilder.Begin();
            vertexCount = 0;
            indexCount = 0;
        }
    }
}
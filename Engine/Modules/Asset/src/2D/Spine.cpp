#include "2D/Spine.h"
#include "2D/DefaultShader.h"
#include "Core/Texture.h"
#include "Util/TextureLoader.h"

#include <StorageModule.h>

#include <spine/extension.h>
#include <spine/SkeletonJson.h>
#include <spine/AnimationState.h>
#include <spine/Skeleton.h>
#include <spine/Atlas.h>

void _spAtlasPage_createTexture(spAtlasPage *self, const char *path)
{
    auto data = SamEngine::GetStorage().Read(path);
    s_assert(!data->Empty());
    auto id = SamEngine::TextureLoader::LoadFromData(path, data);
    auto texture = new SamEngine::Texture(id);
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
    return _readFile(path, length);
}

namespace SamEngine
{
    Spine::Spine(const std::string &skeletonFile, const std::string &atlasFile)
    {
        mAtlas = spAtlas_createFromFile(atlasFile.c_str(), nullptr);
        s_assert(mAtlas != nullptr);
        auto json = spSkeletonJson_create(mAtlas);
        auto data = spSkeletonJson_readSkeletonDataFile(json, skeletonFile.c_str());
        s_assert(data != nullptr);
        spSkeletonJson_dispose(json);
        mSkeleton = spSkeleton_create(data);
        mWorldVertices = static_cast<float32 *>(malloc(sizeof(float32) * SPINE_MESH_VERTEX_COUNT_MAX));
        mIndexBuffer = GetGraphics().GetResourceManager().Create(mIndexBuilder.GetConfig(), nullptr);
        mIndexBuilder.Begin();
        mVertexBuilder.Layout()
            .Add(VertexAttributeType::POSITION, VertexAttributeFormat::FLOAT2)
            .Add(VertexAttributeType::TEXCOORD0, VertexAttributeFormat::FLOAT2)
            .Add(VertexAttributeType::COLOR0, VertexAttributeFormat::FLOAT4);
        mVertexBuffer = GetGraphics().GetResourceManager().Create(mVertexBuilder.GetConfig(), nullptr);
        mVertexBuilder.Begin();
        mState = spAnimationState_create(spAnimationStateData_create(mSkeleton->data));
        s_assert(mState);
        // add listener
    }

    Spine::~Spine()
    {
        if (mSkeleton)
        {
            spSkeletonData_dispose(mSkeleton->data);
            spSkeleton_dispose(mSkeleton);
        }
        if (mAtlas)
        {
            spAtlas_dispose(mAtlas);
        }
        if (mState)
        {
            spAnimationStateData_dispose(mState->data);
            spAnimationState_dispose(mState);
        }
        free(mWorldVertices);
        GetGraphics().GetResourceManager().Destroy(mIndexBuffer);
        GetGraphics().GetResourceManager().Destroy(mVertexBuffer);
    }

    void Spine::SetMixTime(const std::string &from, const std::string &to, float32 time)
    {
        if (mState)
        {
            spAnimationStateData_setMixByName(mState->data, from.c_str(), to.c_str(), time);
        }
    }

    void Spine::SetAnimation(int32 index, const std::string &name, bool loop)
    {
        if (mState)
        {
            spAnimationState_setAnimationByName(mState, index, name.c_str(), loop);
        }
    }

    void Spine::AddAnimation(int32 index, const std::string &name, bool loop, float32 delay)
    {
        if (mState)
        {
            spAnimationState_addAnimationByName(mState, index, name.c_str(), loop, delay);
        }
    }

    std::string Spine::GetAnimation(int32 index)
    {
        std::string name = "";
        if (mState)
        {
            auto entry = spAnimationState_getCurrent(mState, index);
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
            spAnimationState_clearTrack(mState, index);
        }
    }

    void Spine::ClearAll()
    {
        if (mState)
        {
            spAnimationState_clearTracks(mState);
        }
    }

    void Spine::Update(float32 delta)
    {
        if (mSkeleton && mState)
        {
            spSkeleton_update(mSkeleton, delta);
            spAnimationState_update(mState, delta);
            spAnimationState_apply(mState, mSkeleton);
            spSkeleton_updateWorldTransform(mSkeleton);
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
                case SP_BLEND_MODE_NORMAL:
                    slotBlendMode = BlendMode::ALPHA;
                    break;
                case SP_BLEND_MODE_ADDITIVE:
                    slotBlendMode = BlendMode::ADD;
                    break;
                case SP_BLEND_MODE_MULTIPLY:
                    slotBlendMode = BlendMode::MULTIPLY;
                    break;
                case SP_BLEND_MODE_SCREEN:
                    slotBlendMode = BlendMode::SCREEN;
                    break;
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
                    spRegionAttachment_computeWorldVertices(attachment, slot->bone, mWorldVertices);
                    auto r = static_cast<uint8>(mSkeleton->r * slot->r * attachment->r * 255);
                    auto g = static_cast<uint8>(mSkeleton->g * slot->g * attachment->g * 255);
                    auto b = static_cast<uint8>(mSkeleton->b * slot->b * attachment->b * 255);
                    auto a = static_cast<uint8>(mSkeleton->a * slot->a * attachment->a * 255);
                    for (auto vertexIndex = 0; vertexIndex < 4; ++vertexIndex)
                    {
                        mVertexBuilder
                            .Vertex(vertexCount + vertexIndex, VertexAttributeType::POSITION, mWorldVertices[vertexIndex], mWorldVertices[vertexIndex + 1])
                            .Vertex(vertexCount + vertexIndex, VertexAttributeType::TEXCOORD0, attachment->uvs[vertexIndex], attachment->uvs[vertexIndex + 1])
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
                    spMeshAttachment_computeWorldVertices(attachment, slot, mWorldVertices);
                    auto r = static_cast<uint8>(mSkeleton->r * slot->r * attachment->r * 255);
                    auto g = static_cast<uint8>(mSkeleton->g * slot->g * attachment->g * 255);
                    auto b = static_cast<uint8>(mSkeleton->b * slot->b * attachment->b * 255);
                    auto a = static_cast<uint8>(mSkeleton->a * slot->a * attachment->a * 255);
                    for (auto triangleIndex = 0; triangleIndex < attachment->trianglesCount; ++triangleIndex)
                    {
                        auto index = attachment->triangles[triangleIndex] << 1;
                        mVertexBuilder
                            .Vertex(vertexCount, VertexAttributeType::POSITION, mWorldVertices[index], mWorldVertices[index + 1])
                            .Vertex(vertexCount, VertexAttributeType::TEXCOORD0, attachment->uvs[index] * slotTexture->GetWidth(), attachment->uvs[index + 1] * slotTexture->GetHeight())
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
                    spSkinnedMeshAttachment_computeWorldVertices(attachment, slot, mWorldVertices);
                    auto r = static_cast<uint8>(mSkeleton->r * slot->r * attachment->r * 255);
                    auto g = static_cast<uint8>(mSkeleton->g * slot->g * attachment->g * 255);
                    auto b = static_cast<uint8>(mSkeleton->b * slot->b * attachment->b * 255);
                    auto a = static_cast<uint8>(mSkeleton->a * slot->a * attachment->a * 255);
                    for (auto triangleIndex = 0; triangleIndex < attachment->uvsCount; ++triangleIndex)
                    {
                        auto index = attachment->triangles[triangleIndex] << 1;
                        mVertexBuilder
                            .Vertex(vertexCount, VertexAttributeType::POSITION, mWorldVertices[index], mWorldVertices[index + 1])
                            .Vertex(vertexCount, VertexAttributeType::TEXCOORD0, attachment->uvs[index] * slotTexture->GetWidth(), attachment->uvs[index + 1] * slotTexture->GetHeight())
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
            if (texture && texture->Available())
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
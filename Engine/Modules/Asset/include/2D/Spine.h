#pragma once

#include "Blend.h"
#include "Core/Drawable.h"
#include "Util/IndexBuilder.h"
#include "Util/VertexBuilder.h"

#include <string>

#define SPINE_MESH_VERTEX_COUNT_MAX 1000

struct spAnimationStateData;
struct spAnimationState;
struct spSkeletonData;
struct spSkeleton;
struct spAtlas;

namespace SamEngine
{
    typedef std::shared_ptr<spAnimationStateData> AnimationStateDataPtr;
    typedef std::shared_ptr<spAnimationState> AnimationStatePtr;
    typedef std::shared_ptr<spSkeletonData> SkeletonDataPtr;
    typedef std::shared_ptr<spSkeleton> SkeletonPtr;
    typedef std::shared_ptr<spAtlas> AtlasPtr;

    class Texture;

    class ASSET_API SpineAtlas
    {
    public:
        CREATE_FUNC_DECLARE(SpineAtlas)

        SpineAtlas(const std::string &atlas);

        AtlasPtr GetAtlas() const;

    private:
        AtlasPtr mAtlas{ nullptr };
    };

    inline AtlasPtr SpineAtlas::GetAtlas() const
    {
        return mAtlas;
    }

    typedef std::shared_ptr<SpineAtlas> SpineAtlasPtr;

    class ASSET_API SpineSkeletonData
    {
    public:
        CREATE_FUNC_DECLARE(SpineSkeletonData)

        SpineSkeletonData(const std::string &json, SpineAtlasPtr atlas);

        SkeletonDataPtr GetData() const;

    private:
        SkeletonDataPtr mData{ nullptr };
    };

    inline SkeletonDataPtr SpineSkeletonData::GetData() const
    {
        return mData;
    }

    typedef std::shared_ptr<SpineSkeletonData> SpineSkeletonDataPtr;

    class ASSET_API Spine : public Drawable
    {
    public:
        CREATE_FUNC_DECLARE(Spine)

        explicit Spine(SpineSkeletonDataPtr skeleton);

        virtual ~Spine();

        void SetMixTime(const std::string &from, const std::string &to, TickCount time);

        void SetAnimation(int32 index, const std::string &name, bool loop);

        void AddAnimation(int32 index, const std::string &name, bool loop, TickCount delay = 0);

        std::string GetAnimation(int32 index = 0);

        void Clear(int32 index = 0);

        void ClearAll();

        void Update(TickCount delta);

        virtual void Draw() override;

    protected:
        void Flush(Texture *texture, BlendMode mode, int32 &vertexCount, int32 &indexCount);

    private:
        SpineSkeletonDataPtr mSkeletonData{ nullptr };
        SpineAtlasPtr mAtlas{ nullptr };
        AnimationStateDataPtr mStateData{ nullptr };
        AnimationStatePtr mState{ nullptr };
        SkeletonPtr mSkeleton{ nullptr };
        std::vector<float32> mWorldVertices{ SPINE_MESH_VERTEX_COUNT_MAX };
        IndexBuilder mIndexBuilder{ std::numeric_limits<uint16>::max(), IndexAttributeType::UINT16, BufferUsage::DYNAMIC };
        ResourceID mIndexBuffer{ InvalidResourceID };
        VertexBuilder mVertexBuilder{ 4 * std::numeric_limits<uint16>::max() / 6, BufferUsage::DYNAMIC };
        ResourceID mVertexBuffer{ InvalidResourceID };
    };

    typedef std::shared_ptr<Spine> SpinePtr;
}
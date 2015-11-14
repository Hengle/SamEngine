#pragma once

#include "Blend.h"
#include "Core/Drawable.h"
#include "Util/IndexBuilder.h"
#include "Util/VertexBuilder.h"

#include <string>

#define SPINE_MESH_VERTEX_COUNT_MAX 1000

struct spAnimationState;
struct spSkeleton;
struct spAtlas;

namespace SamEngine
{
    class Texture;

    class ASSET_API Spine : public Drawable
    {
    public:
        CREATE_FUNC_DECLARE(Spine)

        Spine(const std::string &skeletonFile, const std::string &atlasFile);

        virtual ~Spine();

        void SetMixTime(const std::string &from, const std::string &to, TickCount time);

        void SetAnimation(int32 index, const std::string &name, bool loop);

        void AddAnimation(int32 index, const std::string &name, bool loop, TickCount delay = 0);

        std::string GetAnimation(int32 index = 0);

        void Clear(int32 index = 0);

        void ClearAll();

        void Update(TickCount delta);

        void Draw() override;

    protected:
        void Flush(Texture *texture, BlendMode mode, int32 &vertexCount, int32 &indexCount);

    private:
        spAnimationState *mState{ nullptr };
        spSkeleton *mSkeleton{ nullptr };
        spAtlas *mAtlas{ nullptr };
        float32 *mWorldVertices{ nullptr };
        IndexBuilder mIndexBuilder{ std::numeric_limits<uint16>::max(), IndexAttributeType::UINT16, BufferUsage::DYNAMIC };
        ResourceID mIndexBuffer{ InvalidResourceID };
        VertexBuilder mVertexBuilder{ 4 * std::numeric_limits<uint16>::max() / 6, BufferUsage::DYNAMIC };
        ResourceID mVertexBuffer{ InvalidResourceID };
    };

    typedef std::shared_ptr<Spine> SpinePtr;
}
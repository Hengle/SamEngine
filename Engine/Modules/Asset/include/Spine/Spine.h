#pragma once

#include "Graphics/Drawable.h"

#include <string>

struct spAnimationState;
struct spSkeleton;
struct spAtlas;

namespace SamEngine
{
    class ASSET_API Spine : public Drawable
    {
    public:
        CREATE_FUNC_DECLARE(Spine)

        Spine(const std::string &skeletonFile, const std::string &atlasFile);

        virtual ~Spine();

        void SetMixTime(const std::string &from, const std::string &to, float32 time);

        void SetAnimation(int32 index, const std::string &name, bool loop);

        void AddAnimation(int32 index, const std::string &name, bool loop, float32 delay = 0);

        std::string GetAnimation(int32 index = 0);

        void Clear(int32 index = 0);

        void ClearAll();

        void Update(float32 delta);

        void Draw() override;

    private:
        std::shared_ptr<spAnimationState> mState{ nullptr };
        std::shared_ptr<spSkeleton> mSkeleton{ nullptr };
        std::shared_ptr<spAtlas> mAtlas{ nullptr };
    };
}
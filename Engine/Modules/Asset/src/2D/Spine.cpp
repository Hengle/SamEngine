#include "2D/Spine.h"

#include <spine/extension.h>
#include <spine/SkeletonJson.h>
#include <spine/AnimationState.h>
#include <spine/Skeleton.h>
#include <spine/Atlas.h>

void _spAtlasPage_createTexture(spAtlasPage *self, const char *path)
{
    
}

void _spAtlasPage_disposeTexture(spAtlasPage *self)
{
    
}

char *_spUtil_readFile(const char *path, int *length)
{
    return nullptr;
}

namespace SamEngine
{
    Spine::Spine(const std::string &skeletonFile, const std::string &atlasFile)
    {
        mAtlas.reset(spAtlas_createFromFile(atlasFile.c_str(), nullptr));
        s_assert(mAtlas);
        auto json = spSkeletonJson_create(mAtlas.get());
        auto data = spSkeletonJson_readSkeletonDataFile(json, skeletonFile.c_str());
        s_assert(data != nullptr);
        spSkeletonJson_dispose(json);
        mSkeleton.reset(spSkeleton_create(data));
        // malloc world vertices
        // initialize batch
        mState.reset(spAnimationState_create(spAnimationStateData_create(mSkeleton->data)));
        s_assert(mState);
        // add listener
    }

    Spine::~Spine()
    {
        if (mSkeleton)
        {
            spSkeletonData_dispose(mSkeleton->data);
            spSkeleton_dispose(mSkeleton.get());
        }
        if (mAtlas)
        {
            spAtlas_dispose(mAtlas.get());
        }
        if (mState)
        {
            spAnimationStateData_dispose(mState->data);
            spAnimationState_dispose(mState.get());
        }
        // free world vertices
        // dispose batch
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
            spAnimationState_setAnimationByName(mState.get(), index, name.c_str(), loop);
        }
    }

    void Spine::AddAnimation(int32 index, const std::string &name, bool loop, float32 delay)
    {
        if (mState)
        {
            spAnimationState_addAnimationByName(mState.get(), index, name.c_str(), loop, delay);
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

    void Spine::Update(float32 delta)
    {
        if (mSkeleton && mState)
        {
            spSkeleton_update(mSkeleton.get(), delta);
            spAnimationState_update(mState.get(), delta);
            spAnimationState_apply(mState.get(), mSkeleton.get());
            spSkeleton_updateWorldTransform(mSkeleton.get());
        }
    }

    void Spine::Draw()
    {

    }
}
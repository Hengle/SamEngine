#pragma once

#include <GraphicsModule.h>

#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/matrix_transform.hpp>

namespace SamEngine
{
    class ASSET_API Drawable
    {
    public:
        virtual ~Drawable() {}

        virtual void Draw() = 0;

        bool IsVisilble() const;

        void SetVisible(bool value);

        float32 GetOriginX() const;

        void SetOriginX(float32 value);

        float32 GetOriginY() const;

        void SetOriginY(float32 value);

        float32 GetOriginZ() const;

        void SetOriginZ(float32 value);

        float32 GetPositionX() const;

        void SetPositionX(float32 value);

        float32 GetPositionY() const;

        void SetPositionY(float32 value);

        float32 GetPositionZ() const;

        void SetPositionZ(float32 value);

        float32 GetRotationX() const;

        void SetRotationX(float32 value);

        float32 GetRotationY() const;

        void SetRotationY(float32 value);

        float32 GetRotationZ() const;

        void SetRotationZ(float32 value);

        float32 GetScaleX() const;

        void SetScaleX(float32 value);

        float32 GetScaleY() const;

        void SetScaleY(float32 value);

        float32 GetScaleZ() const;

        void SetScaleZ(float32 value);

        glm::mat4 GetModelMatrix();

    protected:
        bool mVisible{ true };
        glm::vec3 mOrigin{ 0.0f };
        glm::vec3 mPosition{ 0.0f };
        glm::vec3 mRotation{ 0.0f };
        glm::vec3 mScale{ 1.0f };

    private:
        bool mMatrixInvalid{ true };
        glm::mat4 mModelMatrix;
    };

    typedef std::shared_ptr<Drawable> DrawablePtr;

    inline bool Drawable::IsVisilble() const
    {
        return mVisible;
    }

    inline void Drawable::SetVisible(bool value)
    {
        mVisible = value;
    }

    inline float32 Drawable::GetOriginX() const
    {
        return mOrigin.x;
    }

    inline void Drawable::SetOriginX(float32 value)
    {
        mOrigin.x = value;
        mMatrixInvalid = true;
    }

    inline float32 Drawable::GetOriginY() const
    {
        return mOrigin.y;
    }

    inline void Drawable::SetOriginY(float32 value)
    {
        mOrigin.y = value;
        mMatrixInvalid = true;
    }

    inline float32 Drawable::GetOriginZ() const
    {
        return mOrigin.z;
    }

    inline void Drawable::SetOriginZ(float32 value)
    {
        mOrigin.z = value;
        mMatrixInvalid = true;
    }

    inline float32 Drawable::GetPositionX() const
    {
        return mPosition.x;
    }

    inline void Drawable::SetPositionX(float32 value)
    {
        mPosition.x = value;
        mMatrixInvalid = true;
    }

    inline float32 Drawable::GetPositionY() const
    {
        return mPosition.y;
    }

    inline void Drawable::SetPositionY(float32 value)
    {
        mPosition.y = value;
        mMatrixInvalid = true;
    }

    inline float32 Drawable::GetPositionZ() const
    {
        return mPosition.z;
    }

    inline void Drawable::SetPositionZ(float32 value)
    {
        mPosition.z = value;
        mMatrixInvalid = true;
    }

    inline float32 Drawable::GetRotationX() const
    {
        return mRotation.x;
    }

    inline void Drawable::SetRotationX(float32 value)
    {
        mRotation.x = value;
        mMatrixInvalid = true;
    }

    inline float32 Drawable::GetRotationY() const
    {
        return mRotation.y;
    }

    inline void Drawable::SetRotationY(float32 value)
    {
        mRotation.y = value;
        mMatrixInvalid = true;
    }

    inline float32 Drawable::GetRotationZ() const
    {
        return mRotation.z;
    }

    inline void Drawable::SetRotationZ(float32 value)
    {
        mRotation.z = value;
        mMatrixInvalid = true;
    }

    inline float32 Drawable::GetScaleX() const
    {
        return mScale.x;
    }

    inline void Drawable::SetScaleX(float32 value)
    {
        mScale.x = value;
        mMatrixInvalid = true;
    }

    inline float32 Drawable::GetScaleY() const
    {
        return mScale.y;
    }

    inline void Drawable::SetScaleY(float32 value)
    {
        mScale.y = value;
        mMatrixInvalid = true;
    }

    inline float32 Drawable::GetScaleZ() const
    {
        return mScale.z;
    }

    inline void Drawable::SetScaleZ(float32 value)
    {
        mScale.z = value;
        mMatrixInvalid = true;
    }

    inline glm::mat4 Drawable::GetModelMatrix()
    {
        if (mMatrixInvalid)
        {
            mModelMatrix = glm::mat4();
            mModelMatrix = glm::translate(mPosition);
            if (mRotation.x != 0.0f)
            {
                mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            }
            if (mRotation.y != 0.0f)
            {
                mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            }
            if (mRotation.z != 0.0f)
            {
                mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
            }
            mModelMatrix = glm::scale(mModelMatrix, mScale);
            mModelMatrix = glm::translate(mModelMatrix, mOrigin);
            mMatrixInvalid = false;
        }
        return mModelMatrix;
    }
}
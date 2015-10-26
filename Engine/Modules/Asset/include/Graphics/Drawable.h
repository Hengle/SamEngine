#pragma once

#include <CoreModule.h>

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

        virtual bool IsVisilble() const;

        virtual void SetVisible(bool value);

        virtual float32 GetOriginX() const;

        virtual void SetOriginX(float32 value);

        virtual float32 GetOriginY() const;

        virtual void SetOriginY(float32 value);

        virtual float32 GetOriginZ() const;

        virtual void SetOriginZ(float32 value);

        virtual float32 GetPositionX() const;

        virtual void SetPositionX(float32 value);

        virtual float32 GetPositionY() const;

        virtual void SetPositionY(float32 value);

        virtual float32 GetPositionZ() const;

        virtual void SetPositionZ(float32 value);

        virtual float32 GetRotationX() const;

        virtual void SetRotationX(float32 value);

        virtual float32 GetRotationY() const;

        virtual void SetRotationY(float32 value);

        virtual float32 GetRotationZ() const;

        virtual void SetRotationZ(float32 value);

        virtual float32 GetScaleX() const;

        virtual void SetScaleX(float32 value);

        virtual float32 GetScaleY() const;

        virtual void SetScaleY(float32 value);

        virtual float32 GetScaleZ() const;

        virtual void SetScaleZ(float32 value);

        glm::mat4 GetModelMatrix() const;

    protected:
        bool mVisible{ true };
        glm::vec3 mOrigin{ 0.0f };
        glm::vec3 mPosition{ 0.0f };
        glm::vec3 mRotation{ 0.0f };
        glm::vec3 mScale{ 1.0f };
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
    }

    inline float32 Drawable::GetOriginY() const
    {
        return mOrigin.y;
    }

    inline void Drawable::SetOriginY(float32 value)
    {
        mOrigin.y = value;
    }

    inline float32 Drawable::GetOriginZ() const
    {
        return mOrigin.z;
    }

    inline void Drawable::SetOriginZ(float32 value)
    {
        mOrigin.z = value;
    }

    inline float32 Drawable::GetPositionX() const
    {
        return mPosition.x;
    }

    inline void Drawable::SetPositionX(float32 value)
    {
        mPosition.x = value;
    }

    inline float32 Drawable::GetPositionY() const
    {
        return mPosition.y;
    }

    inline void Drawable::SetPositionY(float32 value)
    {
        mPosition.y = value;
    }

    inline float32 Drawable::GetPositionZ() const
    {
        return mPosition.z;
    }

    inline void Drawable::SetPositionZ(float32 value)
    {
        mPosition.z = value;
    }

    inline float32 Drawable::GetRotationX() const
    {
        return mRotation.x;
    }

    inline void Drawable::SetRotationX(float32 value)
    {
        mRotation.x = value;
    }

    inline float32 Drawable::GetRotationY() const
    {
        return mRotation.y;
    }

    inline void Drawable::SetRotationY(float32 value)
    {
        mRotation.y = value;
    }

    inline float32 Drawable::GetRotationZ() const
    {
        return mRotation.z;
    }

    inline void Drawable::SetRotationZ(float32 value)
    {
        mRotation.z = value;
    }

    inline float32 Drawable::GetScaleX() const
    {
        return mScale.x;
    }

    inline void Drawable::SetScaleX(float32 value)
    {
        mScale.x = value;
    }

    inline float32 Drawable::GetScaleY() const
    {
        return mScale.y;
    }

    inline void Drawable::SetScaleY(float32 value)
    {
        mScale.y = value;
    }

    inline float32 Drawable::GetScaleZ() const
    {
        return mScale.z;
    }

    inline void Drawable::SetScaleZ(float32 value)
    {
        mScale.z = value;
    }

    inline glm::mat4 Drawable::GetModelMatrix() const
    {
        auto matrix = glm::translate(mOrigin);
        if (mRotation.x != 0.0f)
        {
            matrix = glm::rotate(matrix, glm::radians(mRotation.x), glm::vec3(1.0f, 0.0f, 1.0f));
        }
        if (mRotation.y != 0.0f)
        {
            matrix = glm::rotate(matrix, glm::radians(mRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        if (mRotation.z != 0.0f)
        {
            matrix = glm::rotate(matrix, glm::radians(mRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        }
        matrix = glm::scale(matrix, mScale);
        matrix = glm::translate(matrix, mPosition);
        return matrix;
    }
}
#pragma once

#include <CoreModule.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace SamEngine
{
    class GAME2D_API Drawable
    {
    public:
        virtual ~Drawable() {}

        virtual void Draw(glm::mat4 matrix) = 0;

        bool IsVisilble() const;

        void SetVisible(bool value);

        float32 GetPositionX() const;

        void SetPositionX(float32 value);

        float32 GetPositionY() const;

        void SetPositionY(float32 value);

        float32 GetRotation() const;

        void SetRotation(float32 value);

        float32 GetScaleX() const;

        void SetScaleX(float32 value);

        float32 GetScaleY() const;

        void SetScaleY(float32 value);

        glm::mat4 GetModelMatrix(glm::mat4 matrix) const;

    protected:
        bool mVisible{ true };
        float32 mPositionX{ 0.0f };
        float32 mPositionY{ 0.0f };
        float32 mRotation{ 0.0f };
        float32 mScaleX{ 1.0f };
        float32 mScaleY{ 1.0f };
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

    inline float32 Drawable::GetPositionX() const
    {
        return mPositionX;
    }

    inline void Drawable::SetPositionX(float32 value)
    {
        mPositionX = value;
    }

    inline float32 Drawable::GetPositionY() const
    {
        return mPositionY;
    }

    inline void Drawable::SetPositionY(float32 value)
    {
        mPositionY = value;
    }

    inline float32 Drawable::GetRotation() const
    {
        return mRotation;
    }

    inline void Drawable::SetRotation(float32 value)
    {
        mRotation = value;
    }

    inline float32 Drawable::GetScaleX() const
    {
        return mScaleX;
    }

    inline void Drawable::SetScaleX(float32 value)
    {
        mScaleX = value;
    }

    inline float32 Drawable::GetScaleY() const
    {
        return mScaleY;
    }

    inline void Drawable::SetScaleY(float32 value)
    {
        mScaleY = value;
    }

    inline glm::mat4 Drawable::GetModelMatrix(glm::mat4 matrix) const
    {
        if (mRotation != 0.0f)
        {
            matrix = glm::rotate(matrix, glm::radians(mRotation), glm::vec3(0.0f, 0.0f, 1.0f));
        }
        if (mScaleX != 0.0f || mScaleY != 0.0f)
        {
            matrix = glm::scale(matrix, glm::vec3(mScaleX, mScaleY, 1.0f));
        }
        if (mPositionX != 0.0f || mPositionY != 0.0f)
        {
            matrix = glm::translate(matrix, glm::vec3(mPositionX, mPositionY, 0.0f));
        }
        return matrix;
    }
}
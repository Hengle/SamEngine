#pragma once

#include "Core/Shader.h"

namespace SamEngine
{
    enum class DefaultShaderUniformIndex : uint8
    {
        PROJECTION_MATRIX,
        MODEL_VIEW_MATRIX,
        TEXTURE,
    };

    enum class DefaultShaderType : uint8
    {
        IMAGE_TEXTURE,

        COUNT,
    };

    class ASSET_API DefaultShader
    {
    public:
        static void Initialize();

        static void Finalize();

        static ShaderPtr GetShader(DefaultShaderType type);

    private:
        static ShaderPtr mShaderCache[static_cast<uint8>(DefaultShaderType::COUNT)];
    };
}
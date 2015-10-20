#pragma once

#include <CoreModule.h>
#include <ResourceModule.h>

#include <queue>

#define MAX_SHADER_COUNT 128

namespace SamEngine
{
    typedef int32 ShaderID;

    enum : ShaderID
    {
        InvalidShaderID = -1,
    };

    class GAME2D_API ShaderManager
    {
    public:
        ShaderManager();

        void Destroy();

        ShaderID AddShader(const std::string &vertexSource, const std::string &fragmentSource);

        void DeleteShader(ShaderID id);

        void UseShader(ShaderID id);

        ResourceID GetProgram(ShaderID id);

    private:
        std::queue<ShaderID> mInvalidID;
        ResourceID mProgram[MAX_SHADER_COUNT];
    };
}
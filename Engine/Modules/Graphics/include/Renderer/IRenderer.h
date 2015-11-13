#pragma once

#include <ResourceModule.h>

namespace SamEngine
{
    struct RasterizerState;
    struct DepthStencilState;
    struct BlendState;
    struct ClearState;
    struct GraphicsConfig;

    class GRAPHICS_API IRenderer
    {
    public:
        virtual ~IRenderer() {}

        virtual void Initialize(const GraphicsConfig &config) = 0;

        virtual void Finalize() = 0;

        virtual void Render() = 0;

        virtual void ApplyTarget(ResourceID id = InvalidResourceID) = 0;

        virtual void ApplyClearState(const ClearState &state) = 0;

        virtual void ApplyBlendState(const BlendState &blendState) = 0;

        virtual void ResetBlendState() = 0;

        virtual void ApplyDepthStencilState(const DepthStencilState &depthStencilState) = 0;

        virtual void ResetDepthStencilState() = 0;

        virtual void ApplyRasterizerState(const RasterizerState &rasterizerState) = 0;

        virtual void ResetRasterizerState() = 0;

        virtual void ApplyViewPort(int32 x, int32 y, int32 width, int32 height) = 0;

        virtual void ApplyScissor(int32 x, int32 y, int32 width, int32 height) = 0;

        virtual void ApplyVertexBuffer(ResourceID id) = 0;

        virtual void ResetVertexBuffer() = 0;

        virtual void ApplyIndexBuffer(ResourceID id) = 0;

        virtual void ResetIndexBuffer() = 0;

        virtual void ApplyProgram(ResourceID id) = 0;

        virtual void ResetProgram() = 0;

        virtual void ApplyTexture(int32 index, ResourceID id) = 0;

        virtual void ResetTexture() = 0;

        virtual void Draw(DrawType type, int32 first, int32 count) = 0;

        virtual void Reset() = 0;

        virtual void UpdateIndexBufferData(ResourceID id, int32 offset, void *buffer, size_t size) = 0;

        virtual void UpdateVertexBufferData(ResourceID id, int32 offset, void *buffer, size_t size) = 0;
    };
}
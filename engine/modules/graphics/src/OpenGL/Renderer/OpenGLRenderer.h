#pragma once

#include "OpenGLDefine.h"
#include "OpenGL/Resource/OpenGLResource.h"

#include "Renderer/IRenderer.h"

namespace SamEngine
{
    class OpenGLRenderer : public IRenderer
    {
    public:
        static OpenGLRenderer &Get();

        void Initialize(const GraphicsConfig &config) override;

        void Finalize() override;

        void Render() override;

        void ApplyTarget(ResourceID id = InvalidResourceID) override;

        void ApplyClearState(const ClearState &state) override;

        void ApplyBlendState(const BlendState &blendState) override;

        void ResetBlendState() override;

        void ApplyDepthStencilState(const DepthStencilState &depthStencilState) override;

        void ResetDepthStencilState() override;

        void ApplyRasterizerState(const RasterizerState &rasterizerState) override;

        void ResetRasterizerState() override;

        void ApplyViewPort(int32 x, int32 y, int32 width, int32 height) override;

        void ApplyScissor(int32 x, int32 y, int32 width, int32 height) override;

        void ApplyVertexBuffer(ResourceID id) override;

        void ResetVertexBuffer() override;

        void ApplyIndexBuffer(ResourceID id) override;

        void ResetIndexBuffer() override;

        void ApplyUniformBuffer(ResourceID id) override;

        void ApplyProgram(ResourceID id) override;

        void ResetProgram() override;

        void ApplyTexture(int32 index, ResourceID id) override;

        void ResetTexture() override;

        void ApplyDrawCall(ResourceID id) override;

        void Reset() override;

        void BindVertexBuffer(GLuint buffer);

        void BindIndexBuffer(GLuint buffer);

        void BindProgram(GLuint program);

        void BindTexture(int32 index, GLenum target, GLuint texture);

        #ifdef GLAD_DEBUG
        static void PreOpenGLCallback(const char *name, void *funcptr, int len_args, ...);

        static void PostOpenGLCallback(const char *name, void *funcptr, int len_args, ...);
        #endif

    private:
        static OpenGLRenderer *sInstance;
        OpenGLRendererCache mCache;
        OpenGLTexture *mRenderTarget{ nullptr };
    };
}
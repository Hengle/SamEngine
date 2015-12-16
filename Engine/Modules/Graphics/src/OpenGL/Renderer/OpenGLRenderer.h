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

        virtual void Initialize(const GraphicsConfig &config) override;

        virtual void Finalize() override;

        virtual void Render() override;

        virtual void ApplyTarget(ResourceID id = InvalidResourceID) override;

        virtual void ApplyClearState(const ClearState &state) override;

        virtual void ApplyBlendState(const BlendState &blendState) override;

        virtual void ResetBlendState() override;

        virtual void ApplyDepthStencilState(const DepthStencilState &depthStencilState) override;

        virtual void ResetDepthStencilState() override;

        virtual void ApplyRasterizerState(const RasterizerState &rasterizerState) override;

        virtual void ResetRasterizerState() override;

        virtual void ApplyViewPort(int32 x, int32 y, int32 width, int32 height) override;

        virtual void ApplyScissor(int32 x, int32 y, int32 width, int32 height) override;

        virtual void ApplyVertexBuffer(ResourceID id) override;

        virtual void ResetVertexBuffer() override;

        virtual void ApplyIndexBuffer(ResourceID id) override;

        virtual void ResetIndexBuffer() override;

        virtual void ApplyProgram(ResourceID id) override;

        virtual void ResetProgram() override;

        virtual void ApplyTexture(int32 index, ResourceID id) override;

        virtual void ResetTexture() override;

        virtual void Draw(DrawType type, int32 first, int32 count) override;

        virtual void Reset() override;

        virtual void UpdateIndexBufferData(ResourceID id, int32 offset, void *buffer, size_t size) override;

        virtual void UpdateVertexBufferData(ResourceID id, int32 offset, void *buffer, size_t size) override;

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
        const OpenGLTexture *mRenderTarget{ nullptr };
    };
}
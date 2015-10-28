#include "OpenGLRenderer.h"
#include "OpenGL/Resource/OpenGLGraphicsResourceManager.h"

#include "State/ClearState.h"

namespace SamEngine
{
    OpenGLRenderer *OpenGLRenderer::sInstance = nullptr;

    OpenGLRenderer &OpenGLRenderer::Get()
    {
        s_assert(sInstance != nullptr);
        return *sInstance;
    }

    void OpenGLRenderer::Initialize(const GraphicsConfig &config)
    {
        sInstance = this;
        mRenderTarget = nullptr;
        if (gladLoadGL() == 0)
        {
            s_error("OpenGL init error!\n");
        }
        #ifdef GLAD_DEBUG
        glad_set_pre_callback(PreOpenGLCallback);
        glad_set_post_callback(PostOpenGLCallback);
        #endif
        glGenVertexArrays(1, &mCache.VAO);
        glBindVertexArray(mCache.VAO);
        Reset();
    }

    void OpenGLRenderer::Finalize()
    {
        Reset();
        glDeleteVertexArrays(1, &mCache.VAO);
        mCache.VAO = 0;
        mRenderTarget = nullptr;
        sInstance = nullptr;
    }

    void OpenGLRenderer::Render()
    {
        mRenderTarget = nullptr;
    }

    void OpenGLRenderer::ApplyTarget(ResourceID id)
    {
        auto texture = OpenGLGraphicsResourceManager::Get().GetTexture(id);
        if (mRenderTarget != texture)
        {
            if (texture == nullptr)
            {
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                ApplyViewPort(0, 0, GetWindow().GetConfig().Width, GetWindow().GetConfig().Height);
            }
            else
            {
                glBindFramebuffer(GL_FRAMEBUFFER, texture->FrameBufferID);
                ApplyViewPort(0, 0, texture->Config.Width, texture->Config.Height);
            }
            mRenderTarget = texture;
        }
    }

    void OpenGLRenderer::ApplyClearState(const ClearState &state)
    {
        if (mCache.RasterizerStateCache.ScissorTestEnable)
        {
            mCache.RasterizerStateCache.ScissorTestEnable = false;
            glDisable(GL_SCISSOR_TEST);
        }

        GLbitfield clearMask = 0;

        if (static_cast<uint8>(state.Type) & static_cast<uint8>(ClearType::COLOR))
        {
            clearMask |= GL_COLOR_BUFFER_BIT;
            glClearColor(state.ClearColor.r, state.ClearColor.g, state.ClearColor.b, state.ClearColor.a);
            if (mCache.BlendStateCache.ColorMask != PixelChannel::RGBA)
            {
                mCache.BlendStateCache.ColorMask = PixelChannel::RGBA;
                glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
            }
        }

        if (static_cast<uint8>(state.Type) & static_cast<uint8>(ClearType::DEPTH))
        {
            clearMask |= GL_DEPTH_BUFFER_BIT;
            glClearDepth(state.Depth);
            if (!mCache.DepthStencilStateCache.DepthEnable)
            {
                mCache.DepthStencilStateCache.DepthEnable = true;
                glDepthMask(GL_TRUE);
            }
        }

        if (static_cast<uint8>(state.Type) & static_cast<uint8>(ClearType::STENCIL))
        {
            clearMask |= GL_STENCIL_BUFFER_BIT;
            glClearStencil(state.Stencil);
            if (mCache.DepthStencilStateCache.StencilWriteMask != 0xff)
            {
                mCache.DepthStencilStateCache.StencilWriteMask = 0xff;
                glStencilMask(0xff);
            }
        }

        if (clearMask != 0)
        {
            glClear(clearMask);
        }
    }

    void OpenGLRenderer::ApplyBlendState(const BlendState &blendState)
    {
        if (mRenderTarget != nullptr)
        {
            s_assert(blendState.ColorFormat == mRenderTarget->Config.ColorFormat);
            s_assert(blendState.DepthFormat == mRenderTarget->Config.DepthFormat);
        }
        else
        {
            s_assert(blendState.ColorFormat == GetWindow().GetConfig().ColorFormat);
            s_assert(blendState.DepthFormat == GetWindow().GetConfig().DepthFormat);
        }
        if (blendState.BlendColor != mCache.BlendColor)
        {
            mCache.BlendColor = blendState.BlendColor;
            glBlendColor(blendState.BlendColor.r, blendState.BlendColor.g, blendState.BlendColor.b, blendState.BlendColor.a);
        }
        if (blendState.Enabled != mCache.BlendStateCache.Enabled)
        {
            if (blendState.Enabled)
            {
                glEnable(GL_BLEND);
            }
            else
            {
                glDisable(GL_BLEND);
            }
        }
        if (blendState.SrcRGBFactor != mCache.BlendStateCache.SrcRGBFactor ||
            blendState.DstRGBFactor != mCache.BlendStateCache.DstRGBFactor ||
            blendState.SrcAlphaFactor != mCache.BlendStateCache.SrcAlphaFactor ||
            blendState.DstAlphaFactor != mCache.BlendStateCache.DstAlphaFactor)
        {
            glBlendFuncSeparate(GLEnumFromBlendFactor(blendState.SrcRGBFactor),
                GLEnumFromBlendFactor(blendState.DstRGBFactor),
                GLEnumFromBlendFactor(blendState.SrcAlphaFactor),
                GLEnumFromBlendFactor(blendState.DstAlphaFactor));
        }
        if (blendState.RGBOperation != mCache.BlendStateCache.RGBOperation ||
            blendState.AlphaOperation != mCache.BlendStateCache.AlphaOperation)
        {
            glBlendEquationSeparate(GLEnumFromBlendOperation(blendState.RGBOperation), GLEnumFromBlendOperation(blendState.AlphaOperation));
        }
        if (blendState.ColorMask != mCache.BlendStateCache.ColorMask)
        {
            glColorMask((static_cast<uint8>(blendState.ColorMask) & static_cast<uint8>(PixelChannel::RED)) != 0,
                (static_cast<uint8>(blendState.ColorMask) & static_cast<uint8>(PixelChannel::GREEN)) != 0,
                (static_cast<uint8>(blendState.ColorMask) & static_cast<uint8>(PixelChannel::BLUE)) != 0,
                (static_cast<uint8>(blendState.ColorMask) & static_cast<uint8>(PixelChannel::ALPHA)) != 0);
        }
        mCache.BlendStateCache = blendState;
    }

    void OpenGLRenderer::ResetBlendState()
    {
        mCache.BlendStateCache = BlendState();
        glDisable(GL_BLEND);
        glBlendFuncSeparate(GL_ONE, GL_ZERO, GL_ONE, GL_ZERO);
        glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        mCache.BlendColor = Color(1.0f, 1.0f, 1.0f, 1.0f);
        glBlendColor(1.0f, 1.0f, 1.0f, 1.0f);
    }

    void OpenGLRenderer::ApplyDepthStencilState(const DepthStencilState &depthStencilState)
    {
        if (mCache.DepthStencilStateCache != depthStencilState)
        {
            if (mCache.DepthStencilStateCache.Value != depthStencilState.Value)
            {
                if (depthStencilState.Compare != mCache.DepthStencilStateCache.Compare)
                {
                    glDepthFunc(GLEnumFromCompareFunction(depthStencilState.Compare));
                }
                if (depthStencilState.DepthEnable != mCache.DepthStencilStateCache.DepthEnable)
                {
                    glDepthMask(depthStencilState.DepthEnable);
                }
                if (depthStencilState.StencilEnable != mCache.DepthStencilStateCache.StencilEnable)
                {
                    if (depthStencilState.StencilEnable)
                    {
                        glEnable(GL_STENCIL_TEST);
                    }
                    else
                    {
                        glDisable(GL_STENCIL_TEST);
                    }
                }
            }
            if (mCache.DepthStencilStateCache.Front != depthStencilState.Front)
            {
                if (depthStencilState.Front.Compare != mCache.DepthStencilStateCache.Compare ||
                    depthStencilState.StencilValue != mCache.DepthStencilStateCache.StencilValue ||
                    depthStencilState.StencilReadMask != mCache.DepthStencilStateCache.StencilReadMask)
                {
                    glStencilFuncSeparate(GL_FRONT,
                        GLEnumFromCompareFunction(depthStencilState.Front.Compare),
                        depthStencilState.StencilValue,
                        depthStencilState.StencilReadMask);
                }
                if (depthStencilState.Front.Compare == mCache.DepthStencilStateCache.Compare)
                {
                    glStencilOpSeparate(GL_FRONT,
                        GLEnumFromStencilOperation(depthStencilState.Front.Fail),
                        GLEnumFromStencilOperation(depthStencilState.Front.DepthFail),
                        GLEnumFromStencilOperation(depthStencilState.Front.Pass));
                }
                if (depthStencilState.StencilWriteMask != mCache.DepthStencilStateCache.StencilWriteMask)
                {
                    glStencilMaskSeparate(GL_FRONT, depthStencilState.StencilWriteMask);
                }
            }
            if (mCache.DepthStencilStateCache.Back != depthStencilState.Back)
            {
                if (depthStencilState.Back.Compare != mCache.DepthStencilStateCache.Compare ||
                    depthStencilState.StencilValue != mCache.DepthStencilStateCache.StencilValue ||
                    depthStencilState.StencilReadMask != mCache.DepthStencilStateCache.StencilReadMask)
                {
                    glStencilFuncSeparate(GL_BACK,
                        GLEnumFromCompareFunction(depthStencilState.Back.Compare),
                        depthStencilState.StencilValue,
                        depthStencilState.StencilReadMask);
                }
                if (depthStencilState.Back.Compare == mCache.DepthStencilStateCache.Compare)
                {
                    glStencilOpSeparate(GL_BACK,
                        GLEnumFromStencilOperation(depthStencilState.Back.Fail),
                        GLEnumFromStencilOperation(depthStencilState.Back.DepthFail),
                        GLEnumFromStencilOperation(depthStencilState.Back.Pass));
                }
                if (depthStencilState.StencilWriteMask != mCache.DepthStencilStateCache.StencilWriteMask)
                {
                    glStencilMaskSeparate(GL_BACK, depthStencilState.StencilWriteMask);
                }
            }
            mCache.DepthStencilStateCache = depthStencilState;
        }
    }

    void OpenGLRenderer::ResetDepthStencilState()
    {
        mCache.DepthStencilStateCache = DepthStencilState();
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);
        glDepthMask(GL_FALSE);
        glDisable(GL_STENCIL_TEST);
        glStencilFunc(GL_ALWAYS, 0, 0xFFFFFFFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        glStencilMask(0xFFFFFFFF);
    }

    void OpenGLRenderer::ApplyRasterizerState(const RasterizerState &rasterizerState)
    {
        if (mCache.RasterizerStateCache != rasterizerState)
        {
            auto enable_mask = 0;
            auto disable_mask = 0;
            if (rasterizerState.CullFaceEnable)
            {
                enable_mask |= GL_CULL_FACE;
            }
            else
            {
                disable_mask |= GL_CULL_FACE;
            }
            if (rasterizerState.DepthOffsetEnable)
            {
                enable_mask |= GL_POLYGON_OFFSET_FILL;
            }
            else
            {
                disable_mask |= GL_POLYGON_OFFSET_FILL;
            }
            if (rasterizerState.ScissorTestEnable)
            {
                enable_mask |= GL_SCISSOR_TEST;
            }
            else
            {
                disable_mask |= GL_SCISSOR_TEST;
            }
            if (rasterizerState.DitherEnable)
            {
                enable_mask |= GL_DITHER;
            }
            else
            {
                disable_mask |= GL_DITHER;
            }
            if (rasterizerState.AlphaToCoverageEnable)
            {
                enable_mask |= GL_SAMPLE_ALPHA_TO_COVERAGE;
            }
            else
            {
                disable_mask |= GL_SAMPLE_ALPHA_TO_COVERAGE;
            }
            if (rasterizerState.Sample > 1)
            {
                enable_mask |= GL_MULTISAMPLE;
            }
            else
            {
                disable_mask |= GL_MULTISAMPLE;
            }

            glDisable(disable_mask);

            glEnable(enable_mask);

            if (rasterizerState.CullFace != mCache.RasterizerStateCache.CullFace)
            {
                if (rasterizerState.CullFaceEnable)
                {
                    glCullFace(GLEnumFromFaceSide(rasterizerState.CullFace));
                }
            }
            mCache.RasterizerStateCache = rasterizerState;
        }
    }

    void OpenGLRenderer::ResetRasterizerState()
    {
        mCache.RasterizerStateCache = RasterizerState();
        glDisable(GL_CULL_FACE);
        glFrontFace(GL_CW);
        glCullFace(GL_BACK);
        glDisable(GL_POLYGON_OFFSET_FILL);
        glDisable(GL_SCISSOR_TEST);
        glEnable(GL_DITHER);
        glEnable(GL_MULTISAMPLE);
    }

    void OpenGLRenderer::ApplyViewPort(int32 x, int32 y, int32 width, int32 height)
    {
        if (mCache.ViewportX != x || mCache.ViewportY != y || mCache.ViewportWidth != width || mCache.ViewportHeight != height)
        {
            mCache.ViewportX = x;
            mCache.ViewportY = y;
            mCache.ViewportWidth = width;
            mCache.ViewportHeight = height;
            glViewport(x, y, width, height);
        }
    }

    void OpenGLRenderer::ApplyScissor(int32 x, int32 y, int32 width, int32 height)
    {
        if (mCache.ScissorX != x || mCache.ScissorY != y || mCache.ScissorWidth != width || mCache.ScissorHeight != height)
        {
            mCache.ScissorX = x;
            mCache.ScissorY = y;
            mCache.ScissorWidth = width;
            mCache.ScissorHeight = height;
            glScissor(x, y, width, height);
        }
    }

    void OpenGLRenderer::ApplyVertexBuffer(ResourceID id)
    {
        auto vertexBuffer = OpenGLGraphicsResourceManager::Get().GetVertexBuffer(id);
        s_assert(vertexBuffer != nullptr);
        BindVertexBuffer(vertexBuffer->VertexBufferID[vertexBuffer->CurrentVertexBuffer]);
        for (auto i = 0; i < GraphicsConfig::MaxVertexNodeCount; ++i)
        {
            auto &attributeParam = vertexBuffer->VertexAttributeParam[i];
            if (attributeParam != mCache.VertexAttributeParamCache[i])
            {
                if (attributeParam.Enabled)
                {
                    glVertexAttribPointer(attributeParam.Index, attributeParam.Size, attributeParam.Type, attributeParam.Normalized, attributeParam.Stride, attributeParam.Offset);
                    if (!mCache.VertexAttributeParamCache[i].Enabled)
                    {
                        glEnableVertexAttribArray(attributeParam.Index);
                    }
                }
                else
                {
                    if (mCache.VertexAttributeParamCache[i].Enabled)
                    {
                        glDisableVertexAttribArray(attributeParam.Index);
                    }
                }
                // TODO divisor
                mCache.VertexAttributeParamCache[i] = attributeParam;
            }
        }
    }

    void OpenGLRenderer::ResetVertexBuffer()
    {
        mCache.VertexBufferCache = 0;
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        for (auto i = 0; i < GraphicsConfig::MaxVertexNodeCount; ++i)
        {
            mCache.VertexAttributeParamCache[i] = OpenGLVertexAttributeParam();
            glDisableVertexAttribArray(i);
        }
    }

    void OpenGLRenderer::ApplyIndexBuffer(ResourceID id)
    {
        auto indexBuffer = OpenGLGraphicsResourceManager::Get().GetIndexBuffer(id);
        s_assert(indexBuffer != nullptr);
        BindIndexBuffer(indexBuffer->IndexBufferID);
        if (mCache.IndexBufferType != indexBuffer->Config.Type)
        {
            mCache.IndexBufferType = indexBuffer->Config.Type;
        }
    }

    void OpenGLRenderer::ResetIndexBuffer()
    {
        mCache.IndexBufferCache = 0;
        mCache.IndexBufferType = IndexAttributeType::NONE;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void OpenGLRenderer::ApplyUniformBuffer(ResourceID id)
    {
        auto uniformBuffer = OpenGLGraphicsResourceManager::Get().GetUniformBuffer(id);
        s_assert(mCache.ProgramCache != 0);
        auto &config = uniformBuffer->Config;
        auto &layout = config.Layout;
        auto textureIndex = 0;
        for (auto i = 0; i < layout.Length(); ++i)
        {
            auto &node = layout.At(i);
            if (uniformBuffer->NeedUpdate[i])
            {
                uniformBuffer->NeedUpdate[i] = false;
                auto location = uniformBuffer->UniformLocations[i];
                auto offset = uniformBuffer->UniformDataOffset[i];
                auto buffer = uniformBuffer->UniformData.GetBuffer(offset);
                switch (node.GetType())
                {
                case UniformAttributeFormat::INT:
                    glUniform1iv(location, 1, reinterpret_cast<const GLint *>(buffer));
                    break;
                case UniformAttributeFormat::BOOL:
                    glUniform1iv(location, 1, reinterpret_cast<const GLint *>(buffer));
                    break;
                case UniformAttributeFormat::VECTOR1:
                    glUniform1fv(location, 1, reinterpret_cast<const GLfloat *>(buffer));
                    break;
                case UniformAttributeFormat::VECTOR2:
                    glUniform2fv(location, 1, reinterpret_cast<const GLfloat *>(buffer));
                    break;
                case UniformAttributeFormat::VECTOR3:
                    glUniform3fv(location, 1, reinterpret_cast<const GLfloat *>(buffer));
                    break;
                case UniformAttributeFormat::VECTOR4:
                    glUniform4fv(location, 1, reinterpret_cast<const GLfloat *>(buffer));
                    break;
                case UniformAttributeFormat::MATRIX2:
                    glUniformMatrix2fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat *>(buffer));
                    break;
                case UniformAttributeFormat::MATRIX3:
                    glUniformMatrix3fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat *>(buffer));
                    break;
                case UniformAttributeFormat::MATRIX4:
                    glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat *>(buffer));
                    break;
                case UniformAttributeFormat::TEXTURE:
                {
                    auto textureID = *reinterpret_cast<const ResourceID *>(buffer);
                    ApplyTexture(textureIndex, textureID);
                    ++textureIndex;
                    break;
                }
                default:
                    break;
                }
            }
        }
    }

    void OpenGLRenderer::ApplyProgram(ResourceID id)
    {
        auto program = OpenGLGraphicsResourceManager::Get().GetProgram(id);
        s_assert(program != nullptr);
        BindProgram(program->ProgramID);
    }

    void OpenGLRenderer::ResetProgram()
    {
        mCache.ProgramCache = 0;
        glUseProgram(0);
    }

    void OpenGLRenderer::ApplyTexture(int32 index, ResourceID id)
    {
        auto texture = OpenGLGraphicsResourceManager::Get().GetTexture(id);
        s_assert(texture != nullptr);
        BindTexture(index, texture->Target, texture->TextureID);
    }

    void OpenGLRenderer::ResetTexture()
    {
        for (auto index = 0; index < GraphicsConfig::MaxTextureCount; ++index)
        {
            if (mCache.Texture2DCache[index] != 0)
            {
                glActiveTexture(GL_TEXTURE0 + index);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
            if (mCache.TextureCubeCache[index] != 0)
            {
                glActiveTexture(GL_TEXTURE0 + index);
                glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
            }
        }
        std::memset(mCache.Texture2DCache, 0, sizeof(mCache.Texture2DCache));
        std::memset(mCache.TextureCubeCache, 0, sizeof(mCache.TextureCubeCache));
    }

    void OpenGLRenderer::ApplyDrawCall(ResourceID id)
    {
        auto drawCall = OpenGLGraphicsResourceManager::Get().GetDrawCall(id);
        s_assert(drawCall != nullptr);
        if (mCache.IndexBufferType == IndexAttributeType::NONE)
        {
            glDrawArrays(GLEnumFromDrawType(drawCall->Config.Type), drawCall->Config.First, drawCall->Config.Count);
        }
        else
        {
            glDrawElements(GLEnumFromDrawType(drawCall->Config.Type), drawCall->Config.Count, GLEnumFromIndexAttributeType(mCache.IndexBufferType), reinterpret_cast<GLvoid *>(drawCall->Config.First * SizeOfIndexAttributeType(mCache.IndexBufferType)));
        }
    }

    void OpenGLRenderer::Reset()
    {
        ResetBlendState();
        ResetDepthStencilState();
        ResetRasterizerState();
        ResetVertexBuffer();
        ResetIndexBuffer();
        ResetProgram();
        ResetTexture();
    }

    void OpenGLRenderer::UpdateVertexBufferData(ResourceID id, int32 offset, DataPtr data)
    {
        auto buffer = OpenGLGraphicsResourceManager::Get().GetVertexBuffer(id);
        s_assert(buffer != nullptr);
        auto &config = buffer->Config;
        s_assert(config.Size() >= offset + data->GetSize());
        s_assert(config.Usage == BufferUsage::STREAM || config.Usage == BufferUsage::STATIC || config.Usage == BufferUsage::DYNAMIC);
        if (config.Usage == BufferUsage::STREAM)
        {
            buffer->CurrentVertexBuffer = (buffer->CurrentVertexBuffer + 1) % buffer->VertexBufferCount;
        }
        BindVertexBuffer(buffer->VertexBufferID[buffer->CurrentVertexBuffer]);
        glBufferSubData(GL_ARRAY_BUFFER, offset, data->GetSize(), data->GetBuffer());
    }

    void OpenGLRenderer::BindVertexBuffer(GLuint buffer)
    {
        if (buffer != mCache.VertexBufferCache)
        {
            mCache.VertexBufferCache = buffer;
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
        }
    }

    void OpenGLRenderer::BindIndexBuffer(GLuint buffer)
    {
        if (buffer != mCache.IndexBufferCache)
        {
            mCache.IndexBufferCache = buffer;
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        }
    }

    void OpenGLRenderer::BindProgram(GLuint program)
    {
        if (program != mCache.ProgramCache)
        {
            mCache.ProgramCache = program;
            glUseProgram(program);
        }
    }

    void OpenGLRenderer::BindTexture(int32 index, GLenum target, GLuint texture)
    {
        s_assert_range(index, 0, GraphicsConfig::MaxTextureCount);
        s_assert(target == GL_TEXTURE_2D || target == GL_TEXTURE_CUBE_MAP);

        auto *cache = target == GL_TEXTURE_2D ? mCache.Texture2DCache : mCache.TextureCubeCache;
        if (texture != cache[index])
        {
            cache[index] = texture;
            glActiveTexture(GL_TEXTURE0 + index);
            glBindTexture(target, texture);
        }
    }

#ifdef GLAD_DEBUG
    void OpenGLRenderer::PreOpenGLCallback(const char *name, void *funcptr, int len_args, ...)
    {
        GLenum errorCode;
        errorCode = glad_glGetError();
        if (errorCode != GL_NO_ERROR)
        {
            GetLog().Error("[OpenGLRenderer::PreOpenGLCallback] ERROR 0x%04x in %s\n", errorCode, name);
            SAM_TRAP();
        }
    }

    void OpenGLRenderer::PostOpenGLCallback(const char *name, void *funcptr, int len_args, ...)
    {
        GLenum errorCode;
        errorCode = glad_glGetError();
        if (errorCode != GL_NO_ERROR)
        {
            GetLog().Error("[OpenGLRenderer::PostOpenGLCallback] ERROR 0x%04x in %s\n", errorCode, name);
            SAM_TRAP();
        }
    }
    #endif
}
#include "OpenGLVertexBufferFactory.h"

#include "OpenGL/Renderer/OpenGLRenderer.h"

namespace SamEngine
{
    ResourceStatus OpenGLVertexBufferFactory::Create(OpenGLVertexBuffer &resource, DataPtr data)
    {
        auto &config = resource.Config;

        void *buffer = nullptr;
        if (data != nullptr && !data->Empty())
        {
            s_assert(config.Size() <= data->GetSize());
            buffer = data->GetBuffer();
        }

        if (config.Usage == BufferUsage::STREAM)
        {
            resource.VertexBufferCount = GraphicsConfig::MaxStreamVertexBufferCount;
        }

        for (auto i = 0; i < resource.VertexBufferCount; ++i)
        {
            GLuint vertexBuffer;
            glGenBuffers(1, &vertexBuffer);
            s_assert(vertexBuffer != 0);
            OpenGLRenderer::Get().BindVertexBuffer(vertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, config.Size(), buffer, GLEnumFromBufferUsage(config.Usage));
            OpenGLRenderer::Get().ResetVertexBuffer();
            resource.VertexBufferID[i] = vertexBuffer;
        }

        auto offset = 0;
        for (auto j = 0; j < config.Layout.Length(); ++j)
        {
            auto &vertexNode = config.Layout.At(j);
            auto &vertexAttributeParam = resource.VertexAttributeParam[static_cast<uint8>(vertexNode.Attribute)];
            s_assert(!vertexAttributeParam.Enabled);
            vertexAttributeParam.Index = j;
            vertexAttributeParam.Enabled = true;
            vertexAttributeParam.Streaming = config.Usage == BufferUsage::STREAM;
            // TODO divisor
            vertexAttributeParam.Stride = config.Layout.Size();
            vertexAttributeParam.Offset = reinterpret_cast<GLvoid *>(offset);
            vertexAttributeParam.Size = VertexCountFromVertexAttributeFormat(vertexNode.Format);
            vertexAttributeParam.Type = GLEnumFromVertexAttributeFormat(vertexNode.Format);
            vertexAttributeParam.Normalized = IsNormalizedFromVertexAttributeFormat(vertexNode.Format);
            offset += vertexNode.Size();
        }

        return ResourceStatus::COMPLETED;
    }

    void OpenGLVertexBufferFactory::Destroy(OpenGLVertexBuffer &resource)
    {
        OpenGLRenderer::Get().ResetVertexBuffer();
        glDeleteBuffers(resource.VertexBufferCount, resource.VertexBufferID);
    }
}
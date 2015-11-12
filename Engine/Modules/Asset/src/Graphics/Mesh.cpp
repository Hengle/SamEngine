#include "Graphics/Mesh.h"

namespace SamEngine
{
    Mesh::Mesh(const VertexBuilder &vertex, const IndexBuilder &index)
    {
        mVertexBuffer = GetGraphics().GetResourceManager().Create(vertex.GetConfig(), vertex.GetData());
        mIndexBuffer = GetGraphics().GetResourceManager().Create(index.GetConfig(), index.GetData());
    }

    Mesh::~Mesh()
    {
        if (mVertexBuffer != InvalidResourceID)
        {
            GetGraphics().GetResourceManager().Destroy(mVertexBuffer);
        }
        if (mIndexBuffer != InvalidResourceID)
        {
            GetGraphics().GetResourceManager().Destroy(mIndexBuffer);
        }
        mDrawCallCount = 0;
    }

    void Mesh::UpdateVertices(const VertexBuilder &vertex)
    {
        s_assert(mVertexBuffer != InvalidResourceID);
        GetGraphics().GetRenderer().UpdateVertexBufferData(mVertexBuffer, 0, vertex.GetData()->GetBuffer(), vertex.GetData()->GetSize());
    }

    void Mesh::AddDrawCall(DrawType type, int32 first, int32 count)
    {
        s_assert(mDrawCallCount < MaxDrawCallInMesh);
        mDrawCall[mDrawCallCount++] = { type, first, count };
    }

    void Mesh::Draw()
    {
        if (mVertexBuffer != InvalidResourceID)
        {
            GetGraphics().GetRenderer().ApplyVertexBuffer(mVertexBuffer);
        }
        if (mIndexBuffer != InvalidResourceID)
        {
            GetGraphics().GetRenderer().ApplyIndexBuffer(mIndexBuffer);
        }
        for (auto index = 0; index < mDrawCallCount; ++index)
        {
            GetGraphics().GetRenderer().Draw(mDrawCall[index].Type, mDrawCall[index].First, mDrawCall[index].Count);
        }
    }
}
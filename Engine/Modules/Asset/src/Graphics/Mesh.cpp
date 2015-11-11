#include "Graphics/Mesh.h"

#include <GraphicsModule.h>

namespace SamEngine
{
    void Mesh::Create(const MeshConfig &config)
    {
        mVertexBuffer = GetGraphics().GetResourceManager().Create(config.mVertexBufferConfig, config.mVertexData);
        mIndexBuffer = GetGraphics().GetResourceManager().Create(config.mIndexBufferConfig, config.mIndexData);
        s_assert(config.mDrawCallCount < MaxDrawCallInMesh);
        mDrawCallCount = config.mDrawCallCount;
        for (auto index = 0; index < mDrawCallCount; ++index)
        {
            mDrawCall[index] = config.mDrawCallConfig[index];
        }
    }

    void Mesh::UpdateVertices(const MeshConfig &config)
    {
        s_assert(mVertexBuffer != InvalidResourceID);
        GetGraphics().GetRenderer().UpdateVertexBufferData(mVertexBuffer, 0, config.mVertexData);
    }

    void Mesh::Destroy()
    {
        if (mVertexBuffer != InvalidResourceID)
        {
            GetGraphics().GetResourceManager().Destroy(mVertexBuffer);
        }
        if (mIndexBuffer != InvalidResourceID)
        {
            GetGraphics().GetResourceManager().Destroy(mIndexBuffer);
        }
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
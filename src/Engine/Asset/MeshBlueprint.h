#pragma once


#include "Platform\PlatformVideo.h"
#include "Engine\Engine.h"
#include "Core\CoreLite.h"

#include "AssetBlueprint.h"
#include "Mesh.h"

BEGIN_TRITRANIUM

/**
 * Mesh asset blueprint. Will build a mesh.
 */
class PMeshBlueprint : public PAssetBlueprint
{
public:
	PMeshBlueprint(PEngine *engine, const PString &name, const PString &meshFile) :
		PAssetBlueprint(engine, name),
		mMeshFilePath(meshFile)
	{ }

	bool RequireAsyncLoad() OVERRIDE
	{
		return true;
	}

	void AsyncLoad() OVERRIDE
	{
		// Extract mesh data
		PImporter::ParseObjFile(mMeshFilePath, mMeshData);
	}

	void VidInit() OVERRIDE
	{
		if (mMeshData.vertex.Size() > 0)
		{
			PVidBuffer *buff = mVidCommands->Allocate(mMeshData.vertex.GetAllocation(), mMeshData.vertex.GetCountSize(), EBufferUsage::BU_STATIC_DRAW);
			mBufferVertex = mVidCommands->AllocateVertexBuffer(buff);
			mBufferVertex->mCoordsPerVertex = 3;
			mBufferVertex->mOffset = 0;
			mBufferVertex->mStride = sizeof(PVec3);

			mDrawCount = mMeshData.vertex.Size();
		}
		else
			mBufferVertex = NULL;

		if (mMeshData.uv.Size() > 0)
		{
			PVidBuffer *buff = mVidCommands->Allocate(mMeshData.uv.GetAllocation(), mMeshData.uv.GetCountSize(), EBufferUsage::BU_STATIC_DRAW);
			mBufferUv = mVidCommands->AllocateVertexBuffer(buff);
			mBufferUv->mCoordsPerVertex = 2;
			mBufferUv->mOffset = 0;
			mBufferUv->mStride = sizeof(PVec2);
		}
		else
			mBufferUv = NULL;

		if (mMeshData.normal.Size() > 0)
		{
			PVidBuffer *buff = mVidCommands->Allocate(mMeshData.normal.GetAllocation(), mMeshData.normal.GetCountSize(), EBufferUsage::BU_STATIC_DRAW);
			mBufferNormal = mVidCommands->AllocateVertexBuffer(buff);
			mBufferNormal->mCoordsPerVertex = 3;
			mBufferNormal->mOffset = 0;
			mBufferNormal->mStride = sizeof(PVec3);
		}
		else
			mBufferNormal = NULL;

		mBufferTangent = NULL;
	}

	PMesh *Build() OVERRIDE
	{		
		// Return a new mesh asset
		return new PMesh(mEngine, mBufferVertex, mBufferUv, mBufferNormal, mBufferTangent, mDrawCount);
	}

private:
	PString mMeshFilePath;
	PMeshImportedData mMeshData;

	// Buffers
	PVidVertexBuffer *mBufferVertex;
	PVidVertexBuffer *mBufferUv;
	PVidVertexBuffer *mBufferNormal;
	PVidVertexBuffer *mBufferTangent;
	uint32 mDrawCount;
};

END_TRITRANIUM
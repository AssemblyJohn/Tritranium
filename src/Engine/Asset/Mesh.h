/** Copyright (c) 2016 Lazu Ioan-Bogdan */

#pragma once

#include "Platform\Platform.h"
#include "Platform\PlatformVideo.h"

#include "Importer.h"

#include "Asset.h"

BEGIN_TRITRANIUM

class PMesh : public PAsset 
{
public:
	PMesh(PEngine *engine, PVidVertexBuffer *inBuffVertex, PVidVertexBuffer *inBuffUv, PVidVertexBuffer *inBuffNormal, PVidVertexBuffer *inBuffTangent, uint32 inDrawCount) : 
		PAsset(engine),
		mHasVertex(inBuffVertex != NULL),
		mHasUv(inBuffUv != NULL),
		mHasNormal(inBuffNormal != NULL),
		mHasTangent(inBuffTangent != NULL),
		mBuffVertex(inBuffVertex),
		mBuffUv(inBuffUv),
		mBuffNormal(inBuffNormal),
		mBuffTangent(inBuffTangent),
		mDrawCount(inDrawCount)
	{ }

	~PMesh()
	{
		// Delete pointers
		if (mBuffVertex)  delete mBuffVertex;
		if (mBuffUv) delete mBuffUv;
		if (mBuffNormal) delete mBuffNormal;
		if (mBuffTangent) delete mBuffTangent;
	}

	virtual void ReleaseGPU() OVERRIDE
	{
		// Release all video resources		
		if (mBuffVertex) mVidCommands->Free(mBuffVertex->mBuffer);
		if (mBuffUv) mVidCommands->Free(mBuffUv->mBuffer);
		if (mBuffNormal) mVidCommands->Free(mBuffNormal->mBuffer);
		if (mBuffTangent) mVidCommands->Free(mBuffTangent->mBuffer);
	}

public: /* Buffer accessors */

	bool HasBuffVertex()
	{
		return mHasVertex;
	}

	bool HasBuffUv()
	{
		return mHasUv;
	}

	bool HasBuffNormal()
	{
		return mHasNormal;
	}

	bool HasBuffTangent()
	{
		return mHasTangent;
	}

	const PVidVertexBuffer *GetBuffVertex() const
	{
		return mBuffVertex;
	}

	const PVidVertexBuffer *GetBuffUv() const
	{
		return mBuffUv;
	}

	const PVidVertexBuffer *GetBuffNormal() const
	{
		return mBuffNormal;
	}

	const PVidVertexBuffer *GetBuffTangent() const
	{
		return mBuffTangent;
	}

	uint32 GetDrawCount() const
	{
		return mDrawCount;
	}

private:
	bool mHasVertex;
	bool mHasUv;
	bool mHasNormal;
	bool mHasTangent;

	PVidVertexBuffer *mBuffVertex;
	PVidVertexBuffer *mBuffUv;
	PVidVertexBuffer *mBuffNormal;
	PVidVertexBuffer *mBuffTangent;

	// Draw size
	uint32 mDrawCount;
};

END_TRITRANIUM
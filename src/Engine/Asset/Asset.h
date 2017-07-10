#pragma once

#include "Platform\Platform.h"
#include "Engine\Engine.h"

BEGIN_TRITRANIUM

// TODO: since it's part of the game hierarchy see if we should make this a YAsset instead of a PAsset

/**
 * Asset that is loaded on the CPU and initialized on the GPU if required.
 *
 * Can be a shader program, a mesh, a texture, a sound or anything else that can be used in any way
 * by a game component. 
 *
 * Will be managed by a general asset manager so that when a level is quit or anything like it the asset is released.
 */
class PAsset {
public:
	PAsset(PEngine *engine) :
		mEngine(engine),
		mVidCommands(engine->GetVidCommands())
	{ }

	virtual ~PAsset() { }

	/**
	 * Release GPU held data.
	 */
	virtual void ReleaseGPU() { }

	/**
	 * Release any CPU held data.
	 */
	virtual void ReleaseCPU() { }

public:
	uint32 GetUsedCPU()
	{
		return mUsedCPU;
	}

	uint32 GetUsedGPU()
	{
		return mUsedGPU;
	}

	// Fiend class so that we can set the used CPU and GPU data.
	friend class PAssetBlueprint;

protected:
	PString mName;

protected:
	PEngine *mEngine;
	PVidCommands *mVidCommands;	

	// Set by the friend class
private:
	uint32 mUsedCPU;
	uint32 mUsedGPU;
};

// typedef PAsset* CPAsset;
// typedef eastl::shared_ptr<CPAsset> SCPAsset;

END_TRITRANIUM

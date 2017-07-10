#pragma once

#include "Platform\Platform.h"
#include "Engine\Engine.h"

#include "Core\Commons\String.h"

#include "Asset.h"


BEGIN_TRITRANIUM

/**
 * An asset blueprint builds an asset. An asset is a piece of game resource that can be loaded
 * and is centrally managed by the engine's 'AssetManager'. It can be a 'Mesh' a 'Shader' a 'Texture'
 * or any other data.
 *
 * While the blueprint is not an asset it can build the aforementioned assets.
 */
class PAssetBlueprint 
{
public:
	PAssetBlueprint(PEngine *engine, const PString &name)
	{
		// Name
		mName = name;

		// Engine data
		mEngine = engine;
		mVidCommands = engine->GetVidCommands();
	}
	
	const PString &GetName() const
	{
		return mName;
	}
	
	/** Loads async any data required by this asset. */
	virtual void AsyncLoad() { }

	/** Initialize that takes place on the async thread */
	virtual void AsyncInit() { }

	/** Init that takes place on the video thread. Will be called after the AsyncInit. */
	virtual void VidInit() { }

	/** Init that takes place on the game thread. Will be called after the video init is finished. */
	virtual void Init() { }

	/**  Called after the {@link #Init()} on the game thread. */
	virtual PAsset *Build() = 0;

	/** Called after build to set the size params to the asset. */
	void PostBuild(PAsset *asset)
	{
		// So that we don't have to remember to do it all the times...
		asset->mUsedCPU = GetCPUSize();
		asset->mUsedGPU = GetGPUSize();

		// Set name too, just in case that we need it
		asset->mName = mName;
	}

	/**  Called after the asset is built. Called on the game thread */
	virtual void Release() { }

	/**  If this asset requires an async load and async initialize or just a initialize, video initialize and build. */
	virtual bool RequireAsyncLoad() { return false; }	

protected:
	/** Returns the size that this asset will take in CPU memory. */
	virtual uint32 GetCPUSize() { return 0; }

	/** Returns the size that this asset will take in GPU memory. */
	virtual uint32 GetGPUSize() { return 0; }

protected:
	PString mName;

	PEngine *mEngine;
	PVidCommands *mVidCommands;
};

END_TRITRANIUM

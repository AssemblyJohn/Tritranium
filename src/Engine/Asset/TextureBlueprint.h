#pragma once

#include"Core\CoreLite.h"
#include "Platform\PlatformVideo.h"
#include "Engine\Engine.h"
#include "Importer.h"

#include "AssetBlueprint.h"
#include "Texture.h"

BEGIN_TRITRANIUM

/**
* Mesh asset blueprint. Will build a mesh.
*/
class PTextureBlueprint : public PAssetBlueprint
{
public:
	PTextureBlueprint(PEngine *engine, const PString &name, const PString &textureFile) :
		PAssetBlueprint(engine, name),
		mTextureFilePath(textureFile)
	{ }

	bool RequireAsyncLoad() OVERRIDE
	{
		return true;
	}

	void AsyncLoad() OVERRIDE
	{
		// Extract texture data
		if (PImporter::ParseTexture(mTextureFilePath, mTextureData))
		{
			mTexture = new PTexture(mEngine);

			mTexture->mWidth = mTextureData.mWidth;
			mTexture->mHeight = mTextureData.mHeight;
			mTexture->mTextureType = mTextureData.mType;

			mData = mTextureData.mData;
		}
	}

	void VidInit() OVERRIDE
	{
		// Init it on the video thread
		mTexture->mTexture = mVidCommands->AllocateTexture(mTexture->mWidth, mTexture->mHeight, mTexture->mTextureType, mData.GetBytes());
	}

	PTexture *Build() OVERRIDE
	{
		// Return a new texture asset
		return mTexture;
	}

private:
	// Load data
	PString mTextureFilePath;
	PTextureImportedData mTextureData;

	// Texture data
	PTexture *mTexture;

	// Auto free
	PData mData;
};

END_TRITRANIUM
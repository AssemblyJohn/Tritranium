/**
* Copyright (c) 2015 Lazu Ioan-Bogdan
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, without any restrictions.
*/

#ifndef EN_TEXTURE_H
#define EN_TEXTURE_H

#include "Platform\Platform.h"
#include "Platform\PlatformMemory.h"
#include "Engine\Object\Object.h"

#include "Asset.h"

BEGIN_TRITRANIUM;

class PTexture : public PAsset 
{
public:
	PTexture(PEngine *engine) :
		PAsset(engine)
	{ }

	PTexture(PEngine *engine, PVidTexture *inTexture, EVidPixelType inTextureType, uint16 inWidth, uint16 inHeight) : 
		PAsset(engine),
		mTexture(inTexture),
		mTextureType(inTextureType),
		mWidth(inWidth),
		mHeight(inHeight)
	{ }

	~PTexture()
	{
		delete mTexture;
	}

public:
	virtual void ReleaseGPU() OVERRIDE
	{
		mVidCommands->FreeTexture(mTexture);
	}
public:
	uint16 GetWidth() const
	{
		return mWidth;
	}

	uint16 GetHeight() const
	{
		return mHeight;
	}

	EVidPixelType GetTextureType() const
	{
		return mTextureType;
	}

	const PVidTexture *GetVidTexture() const
	{
		return mTexture;
	}

public:
	// So the blueprint can acess it's internals
	friend class PTextureBlueprint;

private:
	PVidTexture *mTexture;

	EVidPixelType mTextureType;
	uint16 mWidth;
	uint16 mHeight;
};

END_TRITRANIUM

#endif
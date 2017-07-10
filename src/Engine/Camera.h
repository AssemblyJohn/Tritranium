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

#ifndef __TRITRANIUM_CAMERA_H__
#define __TRITRANIUM_CAMERA_H__

#include "Core\CoreLite.h"
#include "Engine\Object\GameObject.h"

BEGIN_TRITRANIUM

enum ECameraType
{
	CT_PERSPECTIVE,
	CT_ORTHOGRAPHIC
};

struct PClipping
{
	float mNear;
	float mFar;
};

/**
 * Everything is resolution independent, values are [0..1] normalized, 1 being maxRes
 */
struct PViewportRectangle
{
	float mX;
	float mY;

	float mWidth;
	float mHeight;
};

class YCamera : public YGameObject
{
public:
	YOBJECT_VARS(YCamera);

	YCamera() :
		mCameraType(ECameraType::CT_PERSPECTIVE),
		mFov(60.0f),  mSize(5.0f),
		mClipping(PClipping{ 0.1f, 1000.0f }),
		mRectangle(PViewportRectangle{0, 0, 1.0f, 1.0f})
	{  }

	virtual void Init(PEngine *engine) OVERRIDE
	{
		YGameObject::Init(engine);

		RecalculateProjection();
	}

public: /* Data */

	void SetFov(float32 v)
	{
		mFov = v;

		// Mark dirty and recalculate

	}

	const float GetFov() const
	{
		return mFov;
	}
		
	const PMat4x4 &GetMtxCamera() const
	{
		return mMtxLookAt;
	}
	
	const PMat4x4 &GetMtxProjection() const
	{
		return mMtxProjection;
	}

	const PMat4x4 &GetInvMtxCamera() const
	{
		return mInvMtxLookAt;
	}

	const PMat4x4 &GetInvMtxProjection() const
	{
		return mInvMtxProjection;
	}

	float Yaw() const;
	float Pitch() const;
	float Roll() const;

public:
	// Steps the camera
	void Step();

private:
	void RecalculateProjection();

private:
	// Camera type
	ECameraType mCameraType;
	// For perspective
	float32 mFov;
	// For orthographic
	float32 mSize;

	PClipping mClipping;
	PViewportRectangle mRectangle;

	// Matrix data
	PMat4x4 mMtxLookAt;	
	PMat4x4 mMtxProjection;
	PMat4x4 mMtxViewProjection;

	// Inverses
	PMat4x4 mInvMtxLookAt;
	PMat4x4 mInvMtxProjection;
};

END_TRITRANIUM

#endif
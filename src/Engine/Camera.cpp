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

#include "Core\CoreLite.h"

#include "Engine.h"
#include "Camera.h"

BEGIN_TRITRANIUM

YOBJECT_FUNCTIONS(YCamera, YGameObject);

void YCamera::RecalculateProjection()
{
	float ratio = GetEngine()->GetViewData().mAspectRatio;

	switch (mCameraType)
	{
	case ECameraType::CT_PERSPECTIVE:
		mMtxProjection = PMath::Perspective(mFov, ratio, mClipping.mNear, mClipping.mFar);
		break;
	case ECameraType::CT_ORTHOGRAPHIC:
		mMtxProjection = PMath::Orthographic(-ratio * mSize, ratio * mSize, -1 * mSize, 1 * mSize, mClipping.mNear, mClipping.mFar);
		break;
	}
}

void YCamera::Step()
{
	// enEntity::Step();

	// Don't forget about the gimbal lock problem. That's why it's Y * X not X * Y
	// Direction orientation
	PMat3x3 rot = PMath::Rotation(transform.rotation.y, Y) * PMath::Rotation(transform.rotation.x, X);

	PVec3 direction(rot * PVec3(0, 0, 1));
	PVec3 right(direction.Cross(PVec3(0, 1, 0)));
	PVec3 center = transform.position + direction;

	mMtxLookAt = PMath::LookAt(
		transform.position,
		center,
		PVec3(0, 1, 0)
	);
	
	if (PMath::InvertMatrix(mMtxLookAt.ToPtr(), mInvMtxLookAt.ToPtr()) == false)
		LogError("Could not invert lookat!");
	if(PMath::InvertMatrix(mMtxProjection.ToPtr(), mInvMtxProjection.ToPtr()) == false)
		LogError("Could not invert proj!");
}

END_TRITRANIUM
/** Copyright (c) Lazu Ioan-Bogdan */

#include "Math.h"

#include "Scalar.h"

BEGIN_TRITRANIUM

PMat4x4 PMath::Position(const PVec3 &axis, float angle, const PVec3 &position, const PVec3 &scale)
{
	PMat3x3 rot = PMath::Rotation(angle, axis);
	PMat4x3 trans = PMath::Translation(position);
	PMat3x3 scl = PMath::Scale(scale);

	return scl.ToMat4x4() * rot.ToMat4x4() * trans.ToMat4x4();
}

PMat4x3 PMath::Camera(const PVec3 &pos, float phi, float theta)
{
	theta = PScalar::DegToRad(theta);
	phi = PScalar::DegToRad(phi);

	float cosT = PScalar::Cos(theta);
	float sinT = PScalar::Sin(theta);
	float cosP = PScalar::Cos(phi);
	float sinP = PScalar::Sin(phi);

	float cosTcosP = cosT * cosP;
	float cosTsinP = cosT * sinP;
	float _sinT = -sinT;
	float _sinP = -sinP;	

	return PMat4x3(
		// Rotation
		cosT,	_sinT * sinP,	_sinT * cosP,
		0,		cosP,			_sinP,
		sinT,	cosTsinP,		cosTcosP,
		// Position
		-pos.x, -pos.y,			-pos.z
	);
}

void PMath::Translate(PMat4x4 &mtx, PVec3 &t)
{
	
	mtx[3].x += mtx[0].x * t.x + mtx[1].x * t.y + mtx[2].x * t.z;
	mtx[3].y += mtx[0].y * t.x + mtx[1].y * t.y + mtx[2].y * t.z;
	mtx[3].z += mtx[0].z * t.x + mtx[1].z * t.y + mtx[2].z * t.z;
	mtx[3].w += mtx[0].w * t.x + mtx[1].w * t.y + mtx[2].w * t.z;
}

PMat4x4 PMath::LookAt(const PVec3 &eye, const PVec3 &center, const PVec3 &up)
{
	// Direction
	PVec3 d = center - eye;
	d.Normalize();

	// Right
	PVec3 r = d.Cross(up);
	r.Normalize();

	// Up perpendicular on d and r
	PVec3 u = r.Cross(d);
	
	return PMat4x4(
		r.x, u.x, -d.x, 0.0f,
		r.y, u.y, -d.y, 0.0f,
		r.z, u.z, -d.z, 0.0f,
		// Translation part		
		r.x * -eye.x + r.y * -eye.y + r.z * -eye.z,
		u.x * -eye.x + u.y * -eye.y + u.z * -eye.z,
		-d.x * -eye.x + -d.y * -eye.y + -d.z * -eye.z,
		1.0f
	);
}

PMat4x4 PMath::Perspective(float fovY, float aspect, float nPlane, float fPlane)
{
	fovY = PScalar::DegToRad(fovY);

	float cosFov = PScalar::Cos(fovY * 0.5f);
	float sinFov = PScalar::Sin(fovY * 0.5f);

	float height = cosFov / sinFov;
	float width = height / aspect;

	float temp1 = (nPlane + fPlane) / (nPlane - fPlane);
	float temp2 = (2.0f * nPlane * fPlane) / (nPlane - fPlane);

	return PMat4x4(
		width, 0, 0, 0,
		0, height, 0, 0,
		0, 0, temp1, -1,
		0, 0, temp2, 0
	);
}

// Call with '-mRatio, mRatio, -1, 1, mNear, mFar' for a square orthographic matrix
PMat4x4 PMath::Orthographic(float left, float right, float bottom, float top, float nPlane, float fPlane)
{
	float r_width = 1.0f / (right - left);
	float r_height = 1.0f / (top - bottom);
	float r_depth = 1.0f / (fPlane - nPlane);
	float x = 2.0f * (r_width);
	float y = 2.0f * (r_height);
	float z = -2.0f * (r_depth);
	float tx = -(right + left) * r_width;
	float ty = -(top + bottom) * r_height;
	float tz = -(fPlane + nPlane) * r_depth;

	PMat4x4 mtx;

	mtx[0] = x;
	mtx[5] = y;
	mtx[10] = z;
	mtx[12] = tx;
	mtx[13] = ty;
	mtx[14] = tz;
	mtx[15] = 1.0f;
	mtx[1] = 0.0f;
	mtx[2] = 0.0f;
	mtx[3] = 0.0f;
	mtx[4] = 0.0f;
	mtx[6] = 0.0f;
	mtx[7] = 0.0f;
	mtx[8] = 0.0f;
	mtx[9] = 0.0f;
	mtx[11] = 0.0f;

	return mtx;
}

PMat4x4 PMath::Clip(float fovY, float aspect, float nPlane, float fPlane)
{
	fovY = PScalar::DegToRad(fovY);

	float cosFov = PScalar::Cos(fovY * 0.5f);
	float sinFov = PScalar::Sin(fovY * 0.5f);

	float height = cosFov / sinFov;
	float width = height / aspect;

	float temp1 = (nPlane + fPlane) / (nPlane - fPlane);
	float temp2 = (2.0f * nPlane * fPlane) / (nPlane - fPlane);

	return PMat4x4(
		width, 0, 0, 0,
		0, height, 0, 0,
		0, 0, temp1, -1,
		0, 0, temp2, 0
	);

	/*
	// Outch... i was building a DirectX style matrix here... hehe
	fovY = DEG2RAD(fovY);
	
	float cosFov = enCos(fovY * 0.5f);
	float sinFov = enSin(fovY * 0.5f);

	float height = cosFov / sinFov;
	float width = height / aspect;

	float temp1 = fPlane / (fPlane - nPlane);
	float temp2 = nPlane * fPlane / (nPlane - fPlane);
	
	return enMat4x4(
		width, 0, 0, 0,
		0, height, 0, 0,
		0, 0, temp1, 1,
		0, 0, temp2, 0
	);
	*/
}

PVec4 PMath::ToClipSpace(const PVec3 &v, const PMat4x4 &m)
{
	PVec4 temp(
		v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0],
		v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1],
		v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2],
		v.z
	);

	float w = v.z;

	temp.x /= w;
	temp.y /= w;
	temp.z /= w;
	temp.w = w;

	return temp;
}

PVec4 PMath::ToClipSpaceNoWDiv(const PVec3 &v, const PMat4x4 &m)
{
	return PVec4(
		v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0],
		v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1],
		v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2],
		v.z
	);
}

PMat4x3 PMath::Translation(const PVec3 &v)
{
	return PMat4x3(
		1,	 0,   0,
		0,	 1,   0,
		0,	 0,	  1,
		v.x, v.y, v.z
	);
}

PMat3x3 PMath::Scale(const PVec3 &v)
{
	return PMat3x3(
		v.x, 0, 0,
		0, v.y, 0,
		0, 0, v.z
	);
}

PMat3x3 PMath::Rotation(const float angle, const PVec3 &axis)
{
	// Setup
	float ang = PScalar::DegToRad(angle);
	
	float cosO = PScalar::Cos(ang);
	float sinO = PScalar::Sin(ang);
	float _cosO = (1.0f - cosO);

	return PMat3x3(
		(axis.x * axis.x) * _cosO + cosO,		   (axis.x * axis.y) * _cosO + axis.z * sinO, (axis.x * axis.z) * _cosO - axis.y * sinO,
		(axis.x * axis.y) * _cosO - axis.z * sinO, (axis.y * axis.y) * _cosO + cosO,		  (axis.y * axis.z) * _cosO + axis.x * sinO,
		(axis.x * axis.z) * _cosO + axis.y * sinO, (axis.y * axis.z) * _cosO - axis.x * sinO, (axis.z * axis.z) * _cosO + cosO
	);
}

PMat3x3 PMath::Rotation(float angle, const EAxe axe)
{
	float ang = PScalar::DegToRad(angle);
	float cA = PScalar::Cos(ang);
	float sA = PScalar::Sin(ang);
	float _sA = -PScalar::Sin(ang);

	switch (axe)
	{
	case X:
		return PMat3x3(
			1,  0,  0,
			0,  cA, sA,
			0, _sA, cA
		);
		break;
	case Y:
		return PMat3x3(
			cA, 0, _sA,
			0,  1,  0,
			sA, 0,  cA
		);
		break;
	case Z:
		return PMat3x3(
			cA, sA,  0,
			_sA, cA, 0,
			0,   0,  1
		);
		break;
	default: return NULL;
	}
}

PMat3x3 PMath::Orientation(const PVec3 &v)
{
	PMat3x3 tempX, tempY, tempZ;

	tempX = Rotation(v.x, X);
	tempY = Rotation(v.y, Y);
	tempZ = Rotation(v.z, Z);

	return (tempY * tempX * tempZ);
}

INLINE bool PMath::CameraFacing(const PVec3 &plane, const PVec3 &camera)
{
	if ((plane * camera) < 0)
		return true;

	return false;
}

END_TRITRANIUM
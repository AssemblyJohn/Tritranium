/** Copyright (c) Lazu Ioan-Bogdan */

#ifndef __TRITRANIUM_MATH_H__
#define __TRITRANIUM_MATH_H__

#include "Platform\Platform.h"

#include "Vector.h"
#include "Matrix.h"

BEGIN_TRITRANIUM

typedef enum EAxe {
	X = 'x',
	Y = 'y',
	Z = 'z'
} EAxe;

class PMath
{
public: /* Order */

	static bool InvertMatrix(const float m[16], float invOut[16])
	{
		float inv[16], det;
		int i;

		inv[0] = m[5] * m[10] * m[15] -
			m[5] * m[11] * m[14] -
			m[9] * m[6] * m[15] +
			m[9] * m[7] * m[14] +
			m[13] * m[6] * m[11] -
			m[13] * m[7] * m[10];

		inv[4] = -m[4] * m[10] * m[15] +
			m[4] * m[11] * m[14] +
			m[8] * m[6] * m[15] -
			m[8] * m[7] * m[14] -
			m[12] * m[6] * m[11] +
			m[12] * m[7] * m[10];

		inv[8] = m[4] * m[9] * m[15] -
			m[4] * m[11] * m[13] -
			m[8] * m[5] * m[15] +
			m[8] * m[7] * m[13] +
			m[12] * m[5] * m[11] -
			m[12] * m[7] * m[9];

		inv[12] = -m[4] * m[9] * m[14] +
			m[4] * m[10] * m[13] +
			m[8] * m[5] * m[14] -
			m[8] * m[6] * m[13] -
			m[12] * m[5] * m[10] +
			m[12] * m[6] * m[9];

		inv[1] = -m[1] * m[10] * m[15] +
			m[1] * m[11] * m[14] +
			m[9] * m[2] * m[15] -
			m[9] * m[3] * m[14] -
			m[13] * m[2] * m[11] +
			m[13] * m[3] * m[10];

		inv[5] = m[0] * m[10] * m[15] -
			m[0] * m[11] * m[14] -
			m[8] * m[2] * m[15] +
			m[8] * m[3] * m[14] +
			m[12] * m[2] * m[11] -
			m[12] * m[3] * m[10];

		inv[9] = -m[0] * m[9] * m[15] +
			m[0] * m[11] * m[13] +
			m[8] * m[1] * m[15] -
			m[8] * m[3] * m[13] -
			m[12] * m[1] * m[11] +
			m[12] * m[3] * m[9];

		inv[13] = m[0] * m[9] * m[14] -
			m[0] * m[10] * m[13] -
			m[8] * m[1] * m[14] +
			m[8] * m[2] * m[13] +
			m[12] * m[1] * m[10] -
			m[12] * m[2] * m[9];

		inv[2] = m[1] * m[6] * m[15] -
			m[1] * m[7] * m[14] -
			m[5] * m[2] * m[15] +
			m[5] * m[3] * m[14] +
			m[13] * m[2] * m[7] -
			m[13] * m[3] * m[6];

		inv[6] = -m[0] * m[6] * m[15] +
			m[0] * m[7] * m[14] +
			m[4] * m[2] * m[15] -
			m[4] * m[3] * m[14] -
			m[12] * m[2] * m[7] +
			m[12] * m[3] * m[6];

		inv[10] = m[0] * m[5] * m[15] -
			m[0] * m[7] * m[13] -
			m[4] * m[1] * m[15] +
			m[4] * m[3] * m[13] +
			m[12] * m[1] * m[7] -
			m[12] * m[3] * m[5];

		inv[14] = -m[0] * m[5] * m[14] +
			m[0] * m[6] * m[13] +
			m[4] * m[1] * m[14] -
			m[4] * m[2] * m[13] -
			m[12] * m[1] * m[6] +
			m[12] * m[2] * m[5];

		inv[3] = -m[1] * m[6] * m[11] +
			m[1] * m[7] * m[10] +
			m[5] * m[2] * m[11] -
			m[5] * m[3] * m[10] -
			m[9] * m[2] * m[7] +
			m[9] * m[3] * m[6];

		inv[7] = m[0] * m[6] * m[11] -
			m[0] * m[7] * m[10] -
			m[4] * m[2] * m[11] +
			m[4] * m[3] * m[10] +
			m[8] * m[2] * m[7] -
			m[8] * m[3] * m[6];

		inv[11] = -m[0] * m[5] * m[11] +
			m[0] * m[7] * m[9] +
			m[4] * m[1] * m[11] -
			m[4] * m[3] * m[9] -
			m[8] * m[1] * m[7] +
			m[8] * m[3] * m[5];

		inv[15] = m[0] * m[5] * m[10] -
			m[0] * m[6] * m[9] -
			m[4] * m[1] * m[10] +
			m[4] * m[2] * m[9] +
			m[8] * m[1] * m[6] -
			m[8] * m[2] * m[5];

		det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

		if (det == 0)
			return false;

		det = 1.0f / det;

		for (i = 0; i < 16; i++)
			invOut[i] = inv[i] * det;

		return true;
	}

public:
	// Basic translation
	static PMat4x3 Translation(const PVec3 &);
	static void Translate(PMat4x4 &, PVec3 &);
	// Scale
	static PMat3x3 Scale(const PVec3 &);
	// Basic rotation around an axis
	static PMat3x3 Rotation(float, const EAxe);
	// Rotation around an arbitrary axis
	static PMat3x3 Rotation(const float, const PVec3 &);
	// Rotation around 3 axes
	static PMat3x3 Orientation(const PVec3 &);
	// Rotation around axis with the angle and position
	static PMat4x4 Position(const PVec3 &, float, const PVec3 &, const PVec3 &);

	static PMat4x3 Camera(const PVec3 &, float, float);
	static bool CameraFacing(const PVec3 &, const PVec3 &);

	static PMat4x4 LookAt(const PVec3 &eye, const PVec3 &center, const PVec3 &up);
	// Same as clip, but the name is more like GLUT
	static PMat4x4 Perspective(float fovY, float aspect, float nPlane, float fPlane);
	static PMat4x4 Orthographic(float left, float right, float bottom, float top, float nPlane, float fPlane);

	/**
	 * Generates a 4x4 clip matrix
	 *
	 * @param fovY
	 *				Field of view Y
	 * @param aspect
	 *				Aspect ratio
	 * @param nPlane
	 *				Near plane
	 * @param fPlane
	 *				Far plane
	 */
	static PMat4x4 Clip(float fovY, float aspect, float nPlane, float fPlane);
	
	// Transofrms a vector to clip space
	static PVec4 ToClipSpace(const PVec3 &, const PMat4x4 &);
	// Transofrm a vector to clip space without dividing with the 'w' component
	static PVec4 ToClipSpaceNoWDiv(const PVec3 &, const PMat4x4 &);

	static float Lerp(float a, float b, float t)
	{
		return a + ((b - a) * t);
	}
};

END_TRITRANIUM

#endif
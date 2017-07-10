/** Copyright (c) Lazu Ioan-Bogdan */

#ifndef EN_SCALAR_H
#define EN_SCALAR_H

#include "Platform\Platform.h"

// Should be available everywhere...
#include <math.h>

BEGIN_TRITRANIUM

const float PI = 3.141592653589793238f;
const float D2R = PI / 180.0f;
const float R2D = 180.0f / PI;

/**
 * Wraper for basics so that we don't have that circular dependency problem.
 */
struct PScalar
{
	static FORCEINLINE float PScalar::DegToRad(float deg)
	{
		return (deg * D2R);
	}

	static FORCEINLINE float PScalar::RadToDeg(float rad)
	{
		return (rad * R2D);
	}

	static FORCEINLINE float PScalar::Sqrt(float x)
	{
		return sqrtf(x);
	}

	static FORCEINLINE float PScalar::Fabs(float x)
	{		
		return fabsf(x);
	}

	static FORCEINLINE float PScalar::Cos(float x)
	{
		return cosf(x);
	}

	static FORCEINLINE float PScalar::Sin(float x)
	{
		return sinf(x);
	}

	static FORCEINLINE float PScalar::Acos(float x)
	{
		return acosf(x);
	}

	static FORCEINLINE float PScalar::Asin(float x)
	{
		return asinf(x);
	}

	static FORCEINLINE float PScalar::Clamp(float v, float min, float max)
	{
		if (v < min) return min;
		if (v > max) return max;

		return v;
	}

	static FORCEINLINE float PScalar::Fmodf(float v, float d)
	{
		return fmodf(v, d);
	}
};

END_TRITRANIUM

#endif
/** Copyright (c) Lazu Ioan-Bogdan */

#ifndef __TRITRANIUM_VECTOR_H__
#define __TRITRANIUM_VECTOR_H__


#include "Platform\Platform.h"

#include "Scalar.h"

BEGIN_TRITRANIUM

// #include <EASTL\internal\type_pod.h>

// All vectors are column, OpenGL convention

/**
 * Begin enVector2
 */

struct PVec2
{	
public:
	float x, y;

	PVec2();
	PVec2(float, float);
	PVec2(const PVec2 &);

	void Set(float, float);
	void Zero();
	
	bool Equals(PVec2);
	bool Equals(PVec2, float);

	float Distance(PVec2 &);
	void Normalize();
	float Magnitude();

	const float *ToPtr() const;
	float *ToPtr();
	
	// Usefull for matrices
	float operator[](int32) const;
	float &operator[](int32);
	// Dot product between this vector and the other
	float operator*(const PVec2 &) const;
	// Negate operation
	PVec2 operator-() const;
	PVec2 operator*(float) const;
	PVec2 operator/(float) const;
	PVec2 operator+(const PVec2 &) const;
	PVec2 operator-(const PVec2 &) const;
	PVec2 &operator+=(const PVec2 &);
	PVec2 &operator-=(const PVec2 &);
	PVec2 &operator/=(const PVec2 &);
	PVec2 &operator/=(float);
	PVec2 &operator*=(float);

	static float Dot(PVec2 &, PVec2 &);
	static float Distance(PVec2 &, PVec2 &);
};

// EASTL_DECLARE_TRIVIAL_RELOCATE(PVec2);

INLINE PVec2::PVec2() { }

INLINE PVec2::PVec2(const PVec2 &v)
{
	x = v.x; y = v.y;
}

INLINE PVec2::PVec2(float x, float y)
{
	this->x = x; this->y = y;
}

INLINE float PVec2::operator[](int32 i) const {
	return (&x)[i];
}

INLINE float &PVec2::operator[](int32 i) {
	return (&x)[i];
}

INLINE PVec2 PVec2::operator-() const
{
	return PVec2(-x, -y);
}

INLINE float PVec2::operator*(const PVec2 &v) const
{
	return x * v.x + y * v.y;
}

INLINE PVec2 PVec2::operator*(float v) const
{
	return PVec2(x * v, y * v);
}

INLINE PVec2 PVec2::operator/(float v) const
{
	float val = 1.0f / v;
	return PVec2(x * val, y * val);
}

INLINE PVec2 PVec2::operator+(const PVec2 &v) const
{
	return PVec2(x + v.x, y + v.y);
}

INLINE PVec2 PVec2::operator-(const PVec2 &v) const
{
	return PVec2(x - v.x, y - v.y);
}

INLINE PVec2 &PVec2::operator+=(const PVec2 &v)
{
	x += v.x;
	y += v.y;

	return *this;
}

INLINE PVec2 &PVec2::operator-=(const PVec2 &v)
{
	x -= v.x;
	y -= v.y;

	return *this;
}

INLINE PVec2 &PVec2::operator/=(const PVec2 &v)
{
	x /= v.x;
	y /= v.y;

	return *this;
}

INLINE PVec2 &PVec2::operator/=(float v)
{
	float val = 1.0f / v;
	x *= val;
	y *= val;

	return *this;
}

INLINE PVec2 &PVec2::operator*=(float v)
{
	x *= v;
	y *= v;

	return *this;
}

INLINE void PVec2::Normalize()
{
	float magSq = x * x + y * y;
	if (magSq > 0.0f)
	{
		// Don't use sqrt, use our one
		float oneOverMag = (float)(1.0f / PScalar::Sqrt(magSq));
		x *= oneOverMag;
		y *= oneOverMag;
	}
}

INLINE float PVec2::Magnitude()
{
	return PScalar::Sqrt(x * x + y * y);
}

INLINE const float *PVec2::ToPtr(void) const
{
	return &x;
}

INLINE float *PVec2::ToPtr(void)
{
	return &x;
}

INLINE float PVec2::Dot(PVec2 &a, PVec2 &b)
{
	return a.x * b.x + a.y * b.y;
}

INLINE float PVec2::Distance(PVec2 &a, PVec2 &b)
{
	return PScalar::Sqrt(
		(a.x - b.x) * (a.x - b.x) +
		(a.y - b.y) * (a.y - b.y)
	);
}

INLINE void PVec2::Set(float x, float y)
{
	this->x = x; this->y = y;
}

INLINE void PVec2::Zero()
{
	x = y = 0;
}

INLINE float PVec2::Distance(PVec2 &v)
{
	return PScalar::Sqrt(
		(x - v.x) * (x - v.x) +
		(y - v.y) * (y - v.y)
	);
}

INLINE bool PVec2::Equals(PVec2 v)
{
	return (x == v.x) && (x == v.y);
}

INLINE bool PVec2::Equals(PVec2 v, float epsilon)
{
	return (PScalar::Fabs(x - v.x) < epsilon) && (PScalar::Fabs(y - v.y) < epsilon);
}

/**
 * End enVector2
 */


/**
 * Begin enVector3
 */

struct PVec3
{
public:
	float x, y, z;

	PVec3();
	PVec3(float);
	PVec3(float, float, float);
	PVec3(const PVec3 &);
	/**
	 * Builds the vector from a pointer to 3 floats
	 */
	PVec3(const float *);

	void Set(float, float, float);
	void Zero();

	bool Equals(PVec3);
	bool Equals(PVec3, float);

	PVec3 Cross(const PVec3 &);
	float Distance(const PVec3 &);
	void Normalize();
	float Magnitude();

	const float *ToPtr(void) const;
	float *ToPtr(void);

	// Usefull for matrices
	float operator[](int32) const;
	float &operator[](int32);
	// Dot product between this vector and the other
	float operator*(const PVec3 &) const;
	// Negate operation
	PVec3 operator-() const;
	PVec3 operator*(float) const;
	PVec3 operator/(float) const;
	PVec3 operator+(const PVec3 &) const;
	PVec3 operator-(const PVec3 &) const;
	PVec3 &operator+=(const PVec3 &);
	PVec3 &operator-=(const PVec3 &);
	PVec3 &operator/=(const PVec3 &);
	PVec3 &operator/=(float);
	PVec3 &operator*=(float);

	static float Dot(const PVec3 &, const PVec3 &);
	/**
	 * Computes the angle between two vectors. The vectors will be normalized.
	 *
	 * @return The angle between the two provided vectors.
	 */
	static float Angle(PVec3 &, PVec3 &);
	static PVec3 Cross(const PVec3 &, const PVec3 &);
	static float Distance(const PVec3 &, const PVec3 &);
};

INLINE PVec3::PVec3() { }

INLINE PVec3::PVec3(const PVec3 &v)
{
	x = v.x; y = v.y; z = v.z;
}

INLINE PVec3::PVec3(float v)
{
	x = y = z = v;
}

INLINE PVec3::PVec3(float x, float y, float z)
{
	this->x = x; this->y = y; this->z = z;
}

INLINE PVec3::PVec3(const float *v)
{
	x = v[0]; y = v[1]; z = v[2];
}

INLINE float PVec3::operator[](int32 i) const {
	return (&x)[i];
}

// So we can use vector[i] += something. In case the expresion must be an modifiable lvalue
INLINE float &PVec3::operator[](int32 i) {
	return (&x)[i];
}

INLINE PVec3 PVec3::operator-() const
{
	return PVec3(-x, -y, -z);
}

INLINE float PVec3::operator*(const PVec3 &v) const
{
	return x * v.x + y * v.y + z * v.z;
}

INLINE PVec3 PVec3::operator*(float v) const
{
	return PVec3(x * v, y * v, z * v);
}

INLINE PVec3 PVec3::operator/(float v) const
{
	float val = 1.0f / v;
	return PVec3(x * val, y * val, z * val);
}

INLINE PVec3 PVec3::operator+(const PVec3 &v) const
{
	return PVec3(x + v.x, y + v.y, z + v.z);
}

INLINE PVec3 PVec3::operator-(const PVec3 &v) const
{
	return PVec3(x - v.x, y - v.y, z - v.z);
}

INLINE PVec3 &PVec3::operator+=(const PVec3 &v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

INLINE PVec3 &PVec3::operator-=(const PVec3 &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

INLINE PVec3 &PVec3::operator/=(const PVec3 &v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;

	return *this;
}

INLINE PVec3 &PVec3::operator/=(float v)
{
	float val = 1.0f / v;
	x *= val;
	y *= val;
	z *= val;

	return *this;
}

INLINE PVec3 &PVec3::operator*=(float v)
{
	x *= v;
	y *= v;
	z *= v;

	return *this;
}

INLINE void PVec3::Normalize()
{
	float magSq = x * x + y * y + z * z;
	if (magSq > 0.0f)
	{
		// Don't use sqrt, use our one
		float oneOverMag = (float)(1.0f / PScalar::Sqrt(magSq));
		x *= oneOverMag;
		y *= oneOverMag;
		z *= oneOverMag;
	}
}

INLINE float PVec3::Magnitude()
{
	return PScalar::Sqrt(x * x + y * y + z * z);
}

INLINE const float *PVec3::ToPtr(void) const
{
	return &x;
}

INLINE float *PVec3::ToPtr(void)
{
	return &x;
}

INLINE float PVec3::Dot(const PVec3 &a, const PVec3 &b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

INLINE float PVec3::Angle(PVec3 &a, PVec3 &b)
{
	PVec3 a1 = a;
	PVec3 b1 = b;
	a1.Normalize();
	b1.Normalize();
	
	return PScalar::RadToDeg(PScalar::Acos(a1 * b1));
}

INLINE PVec3 PVec3::Cross(const PVec3 &a, const PVec3 &b)
{
	return PVec3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

INLINE float PVec3::Distance(const PVec3 &a, const PVec3 &b)
{
	return PScalar::Sqrt(
		(a.x - b.x) * (a.x - b.x) +
		(a.y - b.y) * (a.y - b.y) +
		(a.z - b.z) * (a.z - b.z)
	);
}

INLINE void PVec3::Set(float x, float y, float z)
{
	this->x = x; this->y = y; this->z = z;
}

INLINE void PVec3::Zero()
{
	x = y = z = 0;
}

INLINE PVec3 PVec3::Cross(const PVec3 &v)
{
	return PVec3(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x
	);
}

INLINE float PVec3::Distance(const PVec3 &v)
{
	return PScalar::Sqrt(
		(x - v.x) * (x - v.x) +
		(y - v.y) * (y - v.y) +
		(z - v.z) * (z - v.z)
	);
}

INLINE bool PVec3::Equals(PVec3 v)
{
	return (x == v.x) && (x == v.y) && (z == v.z);
}

INLINE bool PVec3::Equals(PVec3 v, float epsilon)
{
	return (PScalar::Fabs(x - v.x) < epsilon) && (PScalar::Fabs(y - v.y) < epsilon) && (PScalar::Fabs(z - v.z) < epsilon);
}

/**
 * End enVector3
 */

/**
 * Begin enVector4
 */

// About the same as vector3...
struct PVec4
{
public:
	float x, y, z, w;

	PVec4();
	PVec4(float);
	PVec4(float, float, float, float);
	PVec4(const PVec4 &);
	/** Last 'w' component is initialized to 1.0 */
	PVec4(const PVec3 &);

	void Set(float, float, float, float);
	void Zero();

	bool Equals(PVec4);
	bool Equals(PVec4, float);

	PVec4 Cross(const PVec4 &);
	float Distance(const PVec4 &);
	void Normalize();
	float Magnitude();

	const float *ToPtr(void) const;
	float *ToPtr(void);

	// Usefull for matrices
	float operator[](int32) const;
	float &operator[](int32);
	// Dot product between this vector and the other
	float operator*(const PVec4 &) const;
	PVec4 operator-() const;
	PVec4 operator*(float) const;
	PVec4 operator/(float) const;
	PVec4 operator+(const PVec4 &) const;
	PVec4 operator-(const PVec4 &) const;
	PVec4 &operator+=(const PVec4 &);
	PVec4 &operator-=(const PVec4 &);
	PVec4 &operator/=(const PVec4 &);
	PVec4 &operator/=(float);
	PVec4 &operator*=(float);
	operator PVec3() const;

	static float Dot(PVec4 &, PVec4 &);
	// Only uses 3 parts (no w)
	static PVec4 Cross(PVec4 &, PVec4 &);
	// Only uses 3 parts (no w)
	static float Distance(PVec4 &, PVec4 &);
};



INLINE PVec4::PVec4() { }

INLINE PVec4::PVec4(const PVec4 &v)
{
	x = v.x; y = v.y; z = v.z; w = v.w;
}

INLINE PVec4::PVec4(const PVec3 &v)
{
	x = v.x; y = v.y; z = v.z; w = 1.0f;
}

INLINE PVec4::PVec4(float v)
{
	x = y = z = w = v;
}

INLINE PVec4::PVec4(float x, float y, float z, float w)
{
	this->x = x; this->y = y; this->z = z; this->w = w;
}

INLINE float PVec4::operator[](int32 i) const {
	return (&x)[i];
}

INLINE float &PVec4::operator[](int32 i) {
	return (&x)[i];
}

INLINE PVec4 PVec4::operator-() const
{
	return PVec4(-x, -y, -z, -w);
}

INLINE float PVec4::operator*(const PVec4 &v) const
{
	return x * v.x + y * v.y + z * v.z + w * v.w;
}

INLINE PVec4 PVec4::operator*(float v) const
{
	return PVec4(x * v, y * v, z * v, w * v);
}

INLINE PVec4 PVec4::operator/(float v) const
{
	float val = 1.0f / v;
	return PVec4(x * val, y * val, z * val, w * val);
}

INLINE PVec4 PVec4::operator+(const PVec4 &v) const
{
	return PVec4(x + v.x, y + v.y, z + v.z, w + v.w);
}

INLINE PVec4 PVec4::operator-(const PVec4 &v) const
{
	return PVec4(x - v.x, y - v.y, z - v.z, w - v.w);
}

INLINE PVec4 &PVec4::operator+=(const PVec4 &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;

	return *this;
}

INLINE PVec4 &PVec4::operator-=(const PVec4 &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;

	return *this;
}

INLINE PVec4 &PVec4::operator/=(const PVec4 &v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w /= v.w;

	return *this;
}

INLINE PVec4 &PVec4::operator/=(float v)
{
	float val = 1.0f / v;
	x *= val;
	y *= val;
	z *= val;
	w *= val;

	return *this;
}

INLINE PVec4 &PVec4::operator*=(float v)
{
	x *= v;
	y *= v;
	z *= v;
	w *= v;

	return *this;
}

INLINE PVec4::operator PVec3() const
{
	return PVec3(
		x, y, z
	);
}

INLINE void PVec4::Normalize()
{
	float magSq = x * x + y * y + z * z;
	if (magSq > 0.0f)
	{
		// Don't use sqrt, use our one
		float oneOverMag = (float)(1.0f / PScalar::Sqrt(magSq));
		x *= oneOverMag;
		y *= oneOverMag;
		z *= oneOverMag;
		w *= oneOverMag;
	}
}

INLINE float PVec4::Magnitude()
{
	return PScalar::Sqrt(x * x + y * y + z * z + w * w);
}

INLINE const float *PVec4::ToPtr(void) const
{
	return &x;
}

INLINE float *PVec4::ToPtr(void)
{
	return &x;
}

INLINE float PVec4::Dot(PVec4 &a, PVec4 &b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

INLINE PVec4 PVec4::Cross(PVec4 &a, PVec4 &b)
{
	// Take only 3 parts of it
	return PVec4(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x,
		1.0f
	);
}

INLINE float PVec4::Distance(PVec4 &a, PVec4 &b)
{
	// Take only the 3 parts of it
	return PScalar::Sqrt(
		(a.x - b.x) * (a.x - b.x) +
		(a.y - b.y) * (a.y - b.y) +
		(a.z - b.z) * (a.z - b.z)
	);
}

INLINE void PVec4::Set(float x, float y, float z, float w)
{
	this->x = x; this->y = y; this->z = z; this->w = w;
}

INLINE void PVec4::Zero()
{
	x = y = z = w = 0;
}

INLINE PVec4 PVec4::Cross(const PVec4 &v)
{
	// Take only 3 parts of it
	return PVec4(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x,
		1.0f
	);
}

INLINE float PVec4::Distance(const PVec4 &v)
{
	return PScalar::Sqrt(
		(x - v.x) * (x - v.x) +
		(y - v.y) * (y - v.y) +
		(z - v.z) * (z - v.z)
	);
}

INLINE bool PVec4::Equals(PVec4 v)
{
	return (x == v.x) && (x == v.y) && (z == v.z) && (w == v.w);
}

INLINE bool PVec4::Equals(PVec4 v, float epsilon)
{	
	return (PScalar::Fabs(x - v.x) < epsilon) && (PScalar::Fabs(y - v.y) < epsilon) && (PScalar::Fabs(z - v.z) < epsilon) && (PScalar::Fabs(w - v.w) < epsilon);
}

/**
* End enVector4
*/

END_TRITRANIUM

#endif 
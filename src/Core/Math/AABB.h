/** Copyright (c) Lazu Ioan-Bogdan */

#ifndef __TRITRANIUM_AABB_H__
#define __TRITRANIUM_AABB_H__

#include "Platform\Platform.h"

#include "Vector.h"

#undef min
#undef max

BEGIN_TRITRANIUM

class PMat3x3;
class PMat4x3;
class PMat4x4;

struct PAabb 
{	
public:
	PVec3 min;
	PVec3 max;

	PAabb() {}
	PAabb(const PVec3 min, const PVec3 max) : min(min), max(max) {}
	PAabb(const PVec3 *vectors, size_t count);
	
	/**
	 * Transfroms an AABB from local space to clip space.
	 *
	 * @param p
	 *				Projection matrix
	 */
	PAabb ToClip(const PMat4x4 &p) const;

	bool Intersects(const PAabb &other) const;

	/**
	 *
	 */
	static PAabb RecomputeBox(const PAabb &box, const PMat4x4 &m);

	static const PAabb FRUSTUM;
private:
};

END_TRITRANIUM

#endif
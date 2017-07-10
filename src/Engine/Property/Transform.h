#pragma once

#include "Platform\Platform.h"
#include "Core\Math\Vector.h"

BEGIN_TRITRANIUM

struct PTransform
{
	PVec3 position;
	PVec3 rotation;
	PVec3 scale;
};

END_TRITRANIUM

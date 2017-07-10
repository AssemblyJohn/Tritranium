/** Copyright (c) Lazu Ioan-Bogdan */

#include "Matrix.h"

BEGIN_TRITRANIUM

PMat3x3 identity3x3(PVec3(1, 0, 0), PVec3(0, 1, 0), PVec3(0, 0, 1));
PMat4x3 identity4x3(PVec3(1, 0, 0), PVec3(0, 1, 0), PVec3(0, 0, 1), PVec3(0, 0, 0));
PMat4x4 identity4x4(PVec4(1, 0, 0, 0), PVec4(0, 1, 0, 0), PVec4(0, 0, 1, 0), PVec4(0, 0, 0, 1));

END_TRITRANIUM
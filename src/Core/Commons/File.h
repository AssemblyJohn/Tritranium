#pragma once

#include "Platform\Platform.h"

BEGIN_TRITRANIUM

class PString;
struct PData;

class PFileUtils
{
public:
	static PString ReadEntireFile(const PString &path);
	static PData ReadEntireFileData(const PString &path);
};


END_TRITRANIUM
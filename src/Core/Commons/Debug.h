#pragma once

#include "Platform\Platform.h"

BEGIN_TRITRANIUM

class IDebug
{
public:
	static void IdeBreak() {  }
	static void LogFail(const CHAR *err, const CHAR *file, const int line) {  }	
	static void Assert(bool val, const CHAR *exp) {  }
};

END_TRITRANIUM
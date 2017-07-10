#pragma once

#include "Core\Commons\Debug.h"

BEGIN_TRITRANIUM

class PWindowsDebug : public IDebug
{
public:
	static void IdeBreak();
	static void LogFail(const CHAR *err, const CHAR *file, const int line);
	static void Assert(bool val, const CHAR *exp);
};

typedef PWindowsDebug PDebug;

END_TRITRANIUM
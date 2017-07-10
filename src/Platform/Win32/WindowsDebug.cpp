#pragma once

#include "Platform\Platform.h"
#include "WindowsDebug.h"

#include <Windows.h>
#include <iostream>
#include <assert.h>

BEGIN_TRITRANIUM

void PWindowsDebug::IdeBreak()
{
	if (::IsDebuggerPresent())
	{
		::DebugBreak();
	}
}

void PWindowsDebug::LogFail(const CHAR *err, const CHAR *file, const int line)
{
	printf("[ERROR] At exp: %s in file: %s at line: %d", err, file, line);
}

void PWindowsDebug::Assert(bool val, const CHAR *exp)
{
	assert(exp);
}

END_TRITRANIUM
#pragma once

#include "Platform\Platform.h"
#include "Platform\PlatformAssertion.h"

#include "Core\Commons\String.h"

BEGIN_TRITRANIUM

class ILog
{
public:
	static void LogVerbose(const PString &format) { CHK(0); }
	static void LogDebug(const PString &format) { CHK(0); }
	static void LogWarning(const PString &format) { CHK(0); }
	static void LogError(const PString &format) { CHK(0); }

	static void LogVerbose(const TCHAR *format, ...) { CHK(0); }
	static void LogDebug(const TCHAR *format, ...) { CHK(0); }
	static void LogWarning(const TCHAR *format, ...) { CHK(0); }
	static void LogError(const TCHAR *format, ...) { CHK(0); }
};

END_TRITRANIUM
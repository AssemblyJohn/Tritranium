#pragma once

#include "Core\Debug\Log.h"

BEGIN_TRITRANIUM

class WindowsLog : public ILog
{
public:
	static void LogVerbose(const PString &format);
	static void LogDebug(const PString &format);
	static void LogWarning(const PString &format);
	static void LogError(const PString &format);

	static void LogVerbose(const TCHAR *format, ...);
	static void LogDebug(const TCHAR *format, ...);
	static void LogWarning(const TCHAR *format, ...);
	static void LogError(const TCHAR *format, ...);
};

typedef WindowsLog PLog;

END_TRITRANIUM
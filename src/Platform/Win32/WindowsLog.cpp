#pragma once

#include "WindowsLog.h"

#include <stdio.h>
#include <stdarg.h>
#include <wchar.h>

BEGIN_TRITRANIUM

static void LogGeneral(const TCHAR *DATA, const TCHAR *format, va_list args);
static void LogGeneral(const TCHAR *DATA, const PString &format);

void WindowsLog::LogVerbose(const PString &format)
{	
	LogGeneral(TXT("VERBOSE"), format);
}

void WindowsLog::LogDebug(const PString &format)
{	
	LogGeneral(TXT("DEBUG"), format);
}

void WindowsLog::LogWarning(const PString &format)
{
	LogGeneral(TXT("WARNING"), format);
}

void WindowsLog::LogError(const PString &format)
{
	LogGeneral(TXT("ERROR"), format);
}

void WindowsLog::LogVerbose(const TCHAR *format, ...)
{
	va_list args;
	va_start(args, format);

	LogGeneral(TXT("VERBOSE"), format, args);

	va_end(args);
}

void WindowsLog::LogDebug(const TCHAR *format, ...)
{
	va_list args;
	va_start(args, format);

	LogGeneral(TXT("DEBUG"), format, args);

	va_end(args);
}

void WindowsLog::LogWarning(const TCHAR *format, ...)
{
	va_list args;
	va_start(args, format);

	LogGeneral(TXT("WARNING"), format, args);

	va_end(args);
}

void WindowsLog::LogError(const TCHAR *format, ...)
{
	va_list args;
	va_start(args, format);

	LogGeneral(TXT("ERROR"), format, args);

	va_end(args);
}

static inline void LogGeneral(const TCHAR *DATA, const TCHAR *format, va_list args)
{
	printf(TXT("[%s] "), DATA);

	if (args != NULL)
	{		
		vprintf(format, args);
	}
	else
	{		
		printf(format);
	}

	printf("\n");
}

static inline void LogGeneral(const TCHAR *DATA, const PString &format)
{
	printf(TXT("[%s] "), DATA);
	printf(format.c_str());
	printf("\n");
}

END_TRITRANIUM
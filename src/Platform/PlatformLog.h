#pragma once

#include "Platform.h"

#ifdef PLATFORM_WINDOWS
	#include "Win32\WindowsLog.h"
#endif

#ifdef PLATFORM_ANDROID
	#include "AndroidLog.h"
#endif

#ifdef PLATFORM_IOS
	#include "iOSLog.h"
#endif

#ifdef PLATFORM_MAC
	#include "MacLog.h"
#endif

BEGIN_TRITRANIUM

#ifdef TRITRANIUM_LOG
	#define LogVerbose(format, ...)	PLog::LogVerbose(format, __VA_ARGS__)
	#define LogDebug(format, ...) PLog::LogDebug(format, __VA_ARGS__)
	#define LogWarning(format, ...)	PLog::LogWarning(format, __VA_ARGS__)
	#define LogError(format, ...) PLog::LogError(format, __VA_ARGS__)
#else	
	#define LogVerbose(format, ...)	do { } while(0)
	#define LogDebug(format, ...) do { } while(0)
	#define LogWarning(format, ...) do { } while(0)
	#define LogError(format, ...) do { } while(0)
#endif

END_TRITRANIUM
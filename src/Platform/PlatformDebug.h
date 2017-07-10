#pragma once

#ifdef PLATFORM_WINDOWS
	#include "Win32\WindowsDebug.h"
#endif

#ifdef PLATFORM_ANDROID
	#include "AndroidDebug.h"
#endif

#ifdef PLATFORM_IOS
	#include "iOSDebug.h"
#endif

#ifdef PLATFORM_MAC
	#include "MacDebug.h"
#endif
#pragma once

#ifdef PLATFORM_WINDOWS
	#include "Win32\WindowsMemory.h"
#endif

#ifdef PLATFORM_ANDROID
	#include "Android\AndroidMemory.h"
#endif

#ifdef PLATFORM_IOS
	#include "iOS\iOSMemory.h"
#endif

#ifdef PLATFORM_MAC
	#include "Mac\MacMemory.h"
#endif
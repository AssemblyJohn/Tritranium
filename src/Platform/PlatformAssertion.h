#pragma once

#include "PlatformDebug.h"

BEGIN_TRITRANIUM

#ifdef TRITRANIUM_DEBUG
	#define CHK(x) do { if(!(x)) { PDebug::IdeBreak(); PDebug::LogFail(#x, __FILE__, __LINE__); Tritranium::PDebug::Assert(x, #x); } } while(0)
#else	
	#define CHK(x)
#endif

END_TRITRANIUM
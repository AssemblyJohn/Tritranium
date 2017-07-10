#pragma once

#if defined(__clang__)
	#define GCC_PACK(n) __attribute__((packed,aligned(n)))
	#define GCC_ALIGN(n) __attribute__((aligned(n)))
#else
	#define MS_ALIGN(n) __declspec(align(n))
#endif

#undef CDECL
#undef STDCALL
#undef FORCEINLINE
#undef FORCENOINLINE
#undef RESTRICT
#undef OVERRIDE

/* Some standard defines */
#define CDECL			__cdecl					
#define STDCALL			__stdcall				
#define FORCEINLINE		__forceinline			
#define FORCENOINLINE	__declspec(noinline)
#define RESTRICT		__restrict
#define OVERRIDE		override

// #include <tchar.h>
// #define TXT(x) _TEXT(x)

/* Text */
// #define TXT(x) L##x
#define TXT(x) x

#define EOL			TXT("\r\n")
#define EOL_ASCII	"\r\n"

#include "Platform\Common\CommonPlatform.h"

/* Types */
struct PWindowsTypes : public PCommonTypes
{
};

typedef PWindowsTypes PTypes;
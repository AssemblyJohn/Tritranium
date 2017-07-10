#pragma once

#define GCC_PACK(n)			__attribute__((packed,aligned(n)))
#define GCC_ALIGN(n)		__attribute__((aligned(n)))

/* Some standard defines */
#define CDECL													
#define STDCALL													
#define FORCEINLINE inline __attribute__ ((always_inline))		
#define FORCENOINLINE __attribute__((noinline))					

#include "CommonPlatform.h"

/* Types */
struct PAndroidTypes : public PCommonTypes
{
};

typedef PAndroidTypes PTypes;
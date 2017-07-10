#ifndef __TRITRANIUM__PLATFORM_MACROS__
#define __TRITRANIUM__PLATFORM_MACROS__

/*
 * Contains general compiler definitions and all the types for all the systems.
 */

#ifdef PLATFORM_WINDOWS
	#include "Win32\WindowsPlatform.h"
#endif

#ifdef PLATFORM_ANDROID
	#include "Android\AndroidPlatform.h"
#endif

#ifdef PLATFORM_IOS
	#include "iOS\iOSPlatform.h"
#endif

#ifdef PLATFORM_MAC
	#include "Mac\MacPlatform.h"
#endif

#ifdef PLATFORM_LINUX
	#include "Linux\LinuxPlatform"
#endif

// So that we have a all these defined all the time. They won't do anything tho.

#ifndef GCC_PACK
	#define GCC_PACK(n)
#endif

#ifndef GCC_ALIGN
	#define GCC_ALIGN(n)
#endif

#ifndef MS_ALIGN
	#define MS_ALIGN(n)
#endif

#ifndef CDECL
	#define CDECL
#endif

#ifndef STDCALL
	#define STDCALL 
#endif

#ifndef FORCEINLINE
	#define FORCEINLINE
#endif

#ifndef FORCENOINLINE
	#define FORCENOINLINE 
#endif

#ifndef INLINE
	#define INLINE inline
#endif

#ifndef OVERRIDE
	#define OVERRIDE
#endif

// Keyword to tell the compiler that the target of the pointer will only be accesses through that pointer
#ifndef RESTRICT
	#define RESTRICT
#endif

// Converting to wide test
#ifndef TXT
	#define TXT(x) x
#endif

#ifndef EOL
	#define EOL TXT("\n")
#endif

#ifndef EOL_ASCII
	#define EOL_ASCII "\n"
#endif

/* Namespace support and basic types */

// If we wish to add an 'extern 'C'' or something

#define BEGIN_TRITRANIUM	namespace Tritranium  {
#define END_TRITRANIUM		}

#define USING_NS_TRITRANIUM		using namespace Tritranium

/* Types */

BEGIN_TRITRANIUM

// Unsigned
typedef PTypes::uint8		uint8;
typedef PTypes::uint16		uint16;
typedef PTypes::uint32		uint32;
typedef PTypes::uint64		uint64;

// Signed								
typedef	PTypes::int8		int8;
typedef PTypes::int16		int16;
typedef PTypes::int32		int32;
typedef PTypes::int64		int64;
	
// Char
typedef PTypes::ASCIICHAR	CHAR;
typedef PTypes::WIDECHAR	WCHAR;
typedef PTypes::SWITCHCHAR  TCHAR;

// Pointers
typedef PTypes::PTR			ptr;
typedef PTypes::UPTR		uptr;
typedef PTypes::size_t		SIZE_T;

// TODO: remove slowly since it's deprecated and change to float32. Replace with scalar
typedef float				enScalar;

typedef float				scalar;

// Floating point
typedef float				float32;
typedef double				float64;

// Changeable floating point for different engine precision
typedef float32				PFloat;

/* Limits copied from 'limits.h' and 'float.h' */
#define MIN_SINT8			((int8)(-128))
#define MAX_SINT8			((int8)127)

#define MIN_UINT8			((uint8)0x00)
#define MAX_UINT8			((uint8)0xFF)

#define MIN_SINT16			((int16)(-32768))
#define MAX_SINT16			((int16)32767)

#define MIN_UINT16			((uint16)0x0000)
#define MAX_UINT16			((uint16)0xFFFF)

#define MIN_SINT32			((int32)(-2147483648))
#define MAX_SINT32			((int32)2147483647)

#define MIN_UINT32			((uint32)0x0000)
#define MAX_UINT32			((uint32)0xFFFF)

#define MIN_SINT64			((int64)(-9223372036854775808i64))
#define MAX_SINT64			((int64)9223372036854775807i64)

#define MIN_UINT64			((uint64)0x00000000)
#define MAX_UINT64			((uint64)0xFFFFFFFF)

#define MIN_FLOAT			(1.175494351e-38F)
#define MAX_FLOAT			(3.402823466e+38F)

#define MIN_DOUBLE			(2.2250738585072014e-308)
#define MAX_DOUBLE			(1.7976931348623158e+308)

// Tests
class ___Tests
{
private:
	// Ctor, I just need a context
	___Tests()
	{		
		// Hope all are cool on all platforms, else tweak

		static_assert(sizeof(uint8) == 1, "uint8 not 1 byte!");
		static_assert(sizeof(uint16) == 2, "uint16 not 2 bytes!");
		static_assert(sizeof(uint32) == 4, "uint16 not 4 bytes!");
		static_assert(sizeof(uint64) == 8, "uint16 not 8 bytes!");

		static_assert(sizeof(int8) == 1, "int8 not 1 byte!");
		static_assert(sizeof(int16) == 2, "int16 not 2 bytes!");
		static_assert(sizeof(int32) == 4, "int16 not 4 bytes!");
		static_assert(sizeof(int64) == 8, "int16 not 8 bytes!");

		static_assert(sizeof(float32) == 4, "float32 not 4 bytes!");
		static_assert(sizeof(float64) == 8, "float32 not 4 bytes!");

		static_assert(sizeof(CHAR) == 1, "ascii not 1 byte!");
		static_assert(sizeof(CHAR) != sizeof(WCHAR), "wchar must not be equal with ascii!");		

		// Platform char
		static_assert(sizeof(TCHAR) == sizeof(CHAR) || sizeof(TCHAR) == sizeof(WCHAR), "switchable char not wide or ascii!");

		// Ptr
		static_assert(sizeof(ptr) == sizeof(void *), "signed ptr not (void *) bytes!");
		static_assert(sizeof(uptr) == sizeof(void *), "ptr not (void *) bytes!");
		static_assert(sizeof(size_t) == sizeof(void *), "size_t not (void *) bytes!");
	}
};

END_TRITRANIUM

#endif
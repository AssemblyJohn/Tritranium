#pragma once

#ifndef NULL
	#ifdef __cplusplus
		#define NULL    0
	#else
		#define NULL    ((void *)0)
	#endif
#endif

// Static template specialization like Alexandrescu's book

template<typename T32, typename T68, int NOT4OR8>
struct StaticPtr
{
	// Will fail
};

template<typename T32, typename T64>
struct StaticPtr<T32, T64, 8>
{
	typedef T64 PTR;
};

template<typename T32, typename T64>
struct StaticPtr<T32, T64, 4>
{
	typedef T32 PTR;
};

// Common types
struct PCommonTypes
{
	// Unsigned
	typedef unsigned char		byte;
	typedef unsigned char 		uint8;
	typedef unsigned short int	uint16;
	typedef unsigned int		uint32;
	typedef unsigned long long	uint64;

	// Signed							
	typedef	signed char			int8;
	typedef signed short int	int16;
	typedef signed int	 		int32;
	typedef signed long long	int64;

	// Chars										
	typedef char				ASCIICHAR;
	// Carefull with this one, it's not consistent on all machines.
	typedef wchar_t				WIDECHAR;
	// Platform char that is wide or ascii based on platform
	// typedef WIDECHAR			SWITCHCHAR;

	// Too many headackes, ascii will do atm
	typedef ASCIICHAR			SWITCHCHAR;

	// Pointers
	typedef StaticPtr<uint32, uint64, sizeof(void*)>::PTR	UPTR;
	typedef StaticPtr<int32, int64, sizeof(void*)>::PTR		PTR;

	typedef UPTR				size_t;
};

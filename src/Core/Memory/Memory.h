/** Copyright (c) Lazu Ioan-Bogdan */

#ifndef EN_MEMORY_H
#define EN_MEMORY_H


#include "Platform\Platform.h"
#include "Platform\PlatformAssertion.h"

BEGIN_TRITRANIUM

enum EMemoryTag {
#define MEM_TAG( x )	MTAG_##x,	
	MEM_TAG(UNKNOWN) // Better not use this unknown
	MEM_TAG(YCLASS)
	MEM_TAG(NEW)
	MEM_TAG(YGAMEOBJECT)
	MEM_TAG(LIST)
	MEM_TAG(ARRAY)
	MTAG_NUM_TAGS,
#undef MEM_TAG
};

enum
{
	DEFAULT_ALIGNMENT = 8,
	MIN_ALIGNMENT = 8,
};

/**
 * Memory interface.
 */
class IMemory
{
public:
	static void *Memmove(void *dst, const void *src, size_t count) { CHK(0); }
	static int32 Memcmp(const void *ptr1, const void *ptr2, size_t count) { CHK(0); }
	static void *Memset(void *dst, uint8 val, size_t count) { CHK(0); }
	static void *Memzero(void *dst, size_t Count) { CHK(0); }
	static void *Memcpy(void *dst, const void* src, size_t count) { CHK(0); }
	/** Carefull with this once since it might cause a stack overflow. Don't swap big stuff. */
	static void Memswap(void* ptr1, void* ptr2, size_t size) { CHK(0); }

	// Could trick these ones
	
	template<typename T>
	static FORCEINLINE void MemSet(T &src, uint8 val)
	{
		Memset(&src, val, sizeof(T));
	}

	template<typename T>
	static FORCEINLINE void MemZero(T &src)
	{		
		Memset(&src, 0, sizeof(T));
	}

	template<typename T>
	static FORCEINLINE void MemCopy(T &dst, const T &src)
	{
		Memcpy(&dst, &src, sizeof(T));
	}

	// C Runtime malloc and free
	static void *CMalloc(size_t size) { CHK(0); }
	static void CFree(void *ptr) { CHK(0); }

	// TODO: see for this memory tag if it's a good idea
	// Most important. 
	static void *Malloc(size_t size, uint32 alignment = DEFAULT_ALIGNMENT, EMemoryTag tag = MTAG_UNKNOWN) { CHK(0); }
	static void *Realloc(void *ptr, size_t size, uint32 alignment = DEFAULT_ALIGNMENT, EMemoryTag tag = MTAG_UNKNOWN) { CHK(0); }
	static void Free(void *ptr) { CHK(0); }

	// TODO: better deprecate this guy... I don't this this is really smart...
	// Allocation size, see if we can get it somehow, or if we really need it
	static size_t GetAllocSize(void* original) { CHK(0); }

	// TODO: see for this one, since we need some kind of log or output device to write errors to. Log tags and stuff
	static void LogMemoryStats() { CHK(0); }
};

END_TRITRANIUM

#endif
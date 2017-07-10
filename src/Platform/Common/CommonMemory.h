#pragma once

#include "Platform\Platform.h"
#include "Core\Memory\Memory.h"

#include <string>

BEGIN_TRITRANIUM

// Tritranium memory definition
#define Y_MEMORY_DEF()										\
	void *operator new(size_t size) {						\
		void *ptr = PMemory::Malloc(size);					\
		return ptr;											\
	}														\
	void operator delete(void *ptr, size_t size) {			\
		if (ptr) PMemory::Free(ptr);						\
	}


// We must be carefull in the place where we use this to have a implementation of '_alloca' or 'alloc'
#ifdef PLATFORM_WINDOWS
	#define __Alloca_Func _alloca
#else
	#define __Alloca_Func alloca
#endif

#define PMemory_StackAlloc(size) ((size==0) ? 0 : (void*)(__Alloca_Func(size)))

class PCommonMemory : public IMemory
{
public:
	static FORCEINLINE void *PCommonMemory::Memmove(void *dst, const void *src, size_t count)
	{
		return memmove(dst, src, count);
	}

	static FORCEINLINE int32 PCommonMemory::Memcmp(const void *ptr1, const void *ptr2, size_t count)
	{
		return memcmp(ptr1, ptr2, count);
	}

	static FORCEINLINE void *PCommonMemory::Memset(void *dst, uint8 val, size_t count)
	{
		return memset(dst, val, count);
	}

	static FORCEINLINE void *PCommonMemory::Memzero(void *dst, size_t count)
	{
		return memset(dst, 0, count);
	}

	static FORCEINLINE void *PCommonMemory::Memcpy(void *dst, const void* src, size_t count)
	{
		return memcpy(dst, src, count);
	}

	static FORCEINLINE void PCommonMemory::Memswap(void* ptr1, void* ptr2, size_t size)
	{
		void *temp = PMemory_StackAlloc(size);

		Memcpy(temp, ptr1, size);
		Memcpy(ptr1, ptr2, size);
		Memcpy(ptr2, temp, size);
	}


	static void *CMalloc(size_t size);
	static void CFree(void *ptr);

	static void* Malloc(size_t size, uint32 alignment = DEFAULT_ALIGNMENT, EMemoryTag tag = MTAG_UNKNOWN);
	static void* Realloc(void *ptr, size_t size, uint32 alignment = DEFAULT_ALIGNMENT, EMemoryTag tag = MTAG_UNKNOWN);
	static void Free(void *ptr);

	static size_t GetAllocSize(void* original);
};

END_TRITRANIUM
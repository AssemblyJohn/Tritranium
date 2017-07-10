#include "WindowsMemory.h"

BEGIN_TRITRANIUM

void *WindowsMemory::Malloc(size_t size, uint32 alignment, EMemoryTag tag)
{		
	return _aligned_malloc(size, alignment);
}

void *WindowsMemory::Realloc(void *ptr, size_t size, uint32 alignment, EMemoryTag tag)
{
	return _aligned_realloc(ptr, size, alignment);
}

void WindowsMemory::Free(void *ptr)
{
	_aligned_free(ptr);
}

END_TRITRANIUM
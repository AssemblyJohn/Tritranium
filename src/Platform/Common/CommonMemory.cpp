#include "CommonMemory.h"

BEGIN_TRITRANIUM

void *PCommonMemory::CMalloc(size_t size)
{
	return malloc(size);
}

void PCommonMemory::CFree(void *ptr)
{
	free(ptr);
}

void *PCommonMemory::Malloc(size_t size, uint32 alignment, EMemoryTag tag)
{
	return malloc(size);
}

void *PCommonMemory::Realloc(void *ptr, size_t size, uint32 alignment, EMemoryTag tag)
{
	return realloc(ptr, size);
}

void PCommonMemory::Free(void *ptr)
{
	free(ptr);
}

size_t PCommonMemory::GetAllocSize(void* original)
{
	return 0;
}

END_TRITRANIUM
#pragma once

#include "Platform\Common\CommonMemory.h"

#include <malloc.h>

BEGIN_TRITRANIUM

class WindowsMemory : public PCommonMemory
{
public:
	static void* Malloc(size_t size, uint32 alignment = DEFAULT_ALIGNMENT, EMemoryTag tag = MTAG_UNKNOWN);
	static void* Realloc(void *ptr, size_t size, uint32 alignment = DEFAULT_ALIGNMENT, EMemoryTag tag = MTAG_UNKNOWN);
	static void Free(void *ptr);
};

typedef WindowsMemory PMemory;

END_TRITRANIUM
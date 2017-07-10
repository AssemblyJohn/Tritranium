#ifndef __TRITRANIUM_C_STRING__
#define __TRITRANIUM_C_STRING__

#include "Platform\Platform.h"

#include <string>

BEGIN_TRITRANIUM

FORCEINLINE int StrCmp(const CHAR *s1, const CHAR *s2)
{
	return strcmp(s1, s2);
}

FORCEINLINE int StrCmp(const WCHAR *s1, const WCHAR *s2)
{
	return wcscmp(s1, s2);
}

END_TRITRANIUM

#endif

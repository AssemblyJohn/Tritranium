/**
* Copyright (c) 2015 Lazu Ioan-Bogdan
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, without any restrictions.
*/

#include "glinclude.h"

#include "Core\Utils\Profiler.h"

#include <SDL_video.h>

#include "Platform\PlatformAssertion.h"
#include "Platform\PlatformLog.h"

void *EnOpenGLGetProc(const char *proc)
{
	void *ptr = SDL_GL_GetProcAddress(proc);

	if (!ptr)
	{
		USING_NS_TRITRANIUM;
		LogDebug(TXT("Bad address for: %s\n"), proc);
	}	

	return ptr;
}

void InitializeRendererVideo()
{
	static bool initialized = false;

	USING_NS_TRITRANIUM;
	CHK(initialized == false);

	gl3wInit();

	int major, minor;

	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	LogDebug(TXT("OpenGL major: %d minor: %d"), major, minor);

	initialized = true;
}
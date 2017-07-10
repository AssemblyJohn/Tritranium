#pragma once

#ifdef TRITRANIUM_OPENGL
	#include "Rendering\Driver\OpenGL\OpenGLVideo.h"
#elif TRITRANIUM_OPENGL_ES2
	#include "OpenGLES2Video.h"
#elif TRITRANIUM_DIRECTX
	#include "DirectXVideo.h"
#elif TRITRANIUM_METAL
	#include "MetalVideo.h"
#else
	#error Error for compiling video
#endif
/** Copyright (c) 2016 Lazu Ioan-Bogdan */

#pragma once

#include "glinclude.h"

#include "Rendering\VidResources.h"

BEGIN_TRITRANIUM

class OpenGLVidShaderProgram : public PVidShaderProgram
{
public:
	GLint mProgram;
};

class OpenGLVidBuffer : public PVidBuffer
{
public:
	OpenGLVidBuffer(uint32 inSize, EBufferUsage inUsage) :
		PVidBuffer(inSize, inUsage)
	{ }

public:
	GLuint mBuffer;
};

class OpenGLVidVertexBuffer : public PVidVertexBuffer
{
public:
	OpenGLVidVertexBuffer(PVidBuffer *inBuffer) :
		PVidVertexBuffer(inBuffer)
	{ }
};

class OpenGLVidTexture : public PVidTexture
{
public:
	OpenGLVidTexture(ETextureBinding inTarget) :
		PVidTexture(inTarget)
	{ }
public:
	GLuint mTexture;
};

class OpenGLVidShaderParameter : public PVidShaderParameter
{
public:
	OpenGLVidShaderParameter(const PString &inName, EVidShaderBindingType inBindingType, EVidShaderParamType inParamType) :
		PVidShaderParameter(inName, inBindingType, inParamType)
	{ }
	
public:
	GLint mPosition;
};

class OpenGLVidShaderParameterTexture : public OpenGLVidShaderParameter
{
public:
	OpenGLVidShaderParameterTexture(const PString &inName, EVidShaderBindingType inBindingType, EVidShaderParamType inParamType) :
		OpenGLVidShaderParameter(inName, inBindingType, inParamType)
	{ }
public:
	// If it is the first texture, the second and so on... so we can set GL_ACTIVE_TEXTURE correctly
	uint8 mOrder;
};

// Do not forget to define for DX, Metal too
typedef OpenGLVidShaderParameter MatVidShaderParameter;
typedef OpenGLVidShaderParameterTexture MatVidShaderParameterTexture;

END_TRITRANIUM
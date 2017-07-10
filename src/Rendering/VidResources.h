/** Copyright (c) 2016 Lazu Ioan-Bogdan */

#pragma once

#include "Platform\Platform.h"
#include "Core\CoreLite.h"

#include "VidDefines.h"

BEGIN_TRITRANIUM

/**
 * TODO: make this video resource reference counted
 */
class PVidResource
{
public:
	PVidResource() { }
	virtual ~PVidResource() { }

public:
	/**
	* Video thread init called only on the render thread.
	*/
	virtual void InitVidResource() { }

	/**
	* Video thread release called only on the render thread.
	*/
	virtual void ReleaseVidResource() { }
};

class PVidBuffer : public PVidResource {
public:
	PVidBuffer(uint32 inSize, EBufferUsage inUsage) :
		mSize(inSize),
		mUsage(inUsage)
	{ }	
public:
	/** Returns the size in bytes of this buffer */
	uint32 GetSize() 
	{
		return mSize;
	}

	EBufferUsage GetUsage()
	{
		return mUsage;
	}
protected:
	/** Vertex buffer size in bytes */
	uint32 mSize;
	/** Vertex buffer usage flag */
	EBufferUsage mUsage;
};

/**
 * Video holder for vertex buffer. See if this has to be more abstract for DX.
 *
 * Will delete the buffer that it is holding if it is not null on the dtor.
 */
class PVidVertexBuffer : public PVidResource
{
public:
	PVidVertexBuffer(PVidBuffer *inBuffer) :
		mBuffer(inBuffer)
	{ }

	virtual ~PVidVertexBuffer()
	{
		if (mBuffer)
		{
			delete mBuffer;
			mBuffer = NULL;
		}
	}

public:
	uint32 mCoordsPerVertex;
	uint32 mStride;
	uint32 mOffset;

	// Underlaying buffer
	PVidBuffer *mBuffer;
};

class PVidTexture : public PVidResource
{
public:
	PVidTexture(ETextureBinding inTarget) :
		mTarget(inTarget)
	{ }

protected:
	ETextureBinding mTarget;
};

struct PVidShaderProgramBuilder 
{
	PString mVertexShaderCode;
	PString mFragmentShaderCode;
	PString mGeometryShaderCode;
	// PString mTesselationShaderCode;
};

/**
 * Represents a raw video resource
 */
class PVidShaderProgram : public PVidResource
{

};

/**
 * Standard shader input parameter. Will represent a data type that
 * can be bound to the shader at the specified location.
 */
class PVidShaderParameter {
public:
	PVidShaderParameter(const PString &inName, EVidShaderBindingType inBindingType, EVidShaderParamType inParamType) :
		mName(inName),
		mBindingType(inBindingType),
		mParamType(inParamType)
	{ }

	virtual ~PVidShaderParameter() { }

	const EVidShaderBindingType GetBindingType() const
	{
		return mBindingType;
	}

	const EVidShaderParamType GetParamType() const
	{
		return mParamType;
	}

	const PString &GetName() const
	{
		return mName;
	}

private:
	PString mName;

	EVidShaderBindingType mBindingType;
	EVidShaderParamType mParamType;
};

/**
 * Resource holder for a shader parameter. Why so many specializations and not uniform buffer blocks?
 * Because many devices use es 2.0 and we don't have that...
 *
 * Our job to specialize this for various backends.
 */
template<typename Resource, typename ShaderParameter>
class PVidShaderParamResourceHolder : public ShaderParameter
{
public:
	PVidShaderParamResourceHolder(const ShaderParameter *owner) :
		ShaderParameter(*owner)
	{ }

	void SetResource(const Resource &resource)
	{
		mResource = resource;
	}

	const Resource &GetResource() const
	{
		return mResource;
	}

	Resource &GetResource()
	{
		return mResource;
	}

private:
	Resource mResource;
};

struct PShaderProgramBuilder
{
	PVidShaderProgram *mShader;
	TList<PVidShaderParameter *> mParameters;
};

END_TRITRANIUM
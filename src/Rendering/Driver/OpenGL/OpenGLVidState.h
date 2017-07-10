/** Copyright (c) 2016 Lazu Ioan-Bogdan */

#pragma once

#include "glinclude.h"

#include "Core\CoreLite.h"

BEGIN_TRITRANIUM

class OpenGLVidState 
{
	
	class OpenGLVidRasterState 
	{
	public:
		OpenGLVidRasterState()
		{ }

	public:
		GLint mFillMode; // Point, line, triangle
		GLint mCullMode; // CCW, CW
	};

	class OpenGLVidBlendState 
	{
	public:
		OpenGLVidBlendState() :
			mBlend(false),
			mColorBlendOp(GL_FUNC_ADD),
			mColorSrc(0),
			mColorDst(0),

			mBlendAlphaSeparate(false),
			mAlphaBlendOp(0),
			mAlphaSrc(0),
			mAlphaDst(0),

			colorWriteR(true),
			colorWriteG(true),
			colorWriteB(true),
			colorWriteA(true)
		{ }

	public:
		/*
		* If the blending state is enabled and if yes the blend operation, and the source and dest color.
		*/
		bool mBlend; // We're not blending
		GLint mColorBlendOp; // Default color add
		GLint mColorSrc; // None
		GLint mColorDst; // None

		/*
		 * If we should blend the alpha in a separate moode, and it's operations
		 */
		bool mBlendAlphaSeparate;
		GLint mAlphaBlendOp;
		GLint mAlphaSrc;
		GLint mAlphaDst;

		/*
		* If we should write the red, green, blue and alpha channel on the framebuffer
		*/
		bool colorWriteR;
		bool colorWriteG;
		bool colorWriteB;
		bool colorWriteA;
	};

	class OpenGLVidDepthState 
	{
	public:
		OpenGLVidDepthState() :
			mZTestEnabled(false),
			mZWriteEnabled(false),
			mZFunction(GL_LESS),

			mDepthMaxZ(1.0f),
			mDepthMinZ(0.0f),
			mDepthClear(0.0f)
		{ }

	public:
		bool mZTestEnabled; // glEnable(GL_DEPTH)
		bool mZWriteEnabled; // initially it is enabled, but let it false.
		int mZFunction; // GL_LESS, GL_EQUAL, etc...

		// Depth sizes
		float mDepthMaxZ;
		float mDepthMinZ;
		float mDepthClear;
	};

	/*
	 * The current OpenGL state. We check on the CPU first if we change something. Should provided debug data and be faster.
	 */

public:
	OpenGLVidState() :
		mFramebuffer(0),
		mRenderbuffer(0),
		mProgram(0),

		mActiveTexture(0),
		mBoundTexture2D(0),
		mBoundTextureCube(0),

		mBoundArrayBuffer(0),
		mBoundElementBuffer(0),

		mClearColor(0, 0, 0, 1)
	{ }

public:
	OpenGLVidDepthState mDepthState;
	OpenGLVidBlendState mBlendState;
	OpenGLVidRasterState mRasterState;

	// Current framebuffer
	GLint mFramebuffer;
	// Current renderbuffer
	GLint mRenderbuffer;
	// Current program
	GLint mProgram;

	// Active texture
	GLint mActiveTexture;

	// TODO: fix, wrong since for different bound active textures we can have different textures
	// Bound texture 2D and cube
	GLint mBoundTexture2D;
	GLint mBoundTextureCube;
	// Bound arrays
	GLint mBoundArrayBuffer;
	GLint mBoundElementBuffer;
	// Viewport sizes
	GLint mViewportX;
	GLint mViewportY;
	GLint mViewportW;
	GLint mViewportH;

	// Clear color
	PVec4 mClearColor;
};

END_TRITRANIUM
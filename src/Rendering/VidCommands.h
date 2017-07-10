#pragma once

#include "VidDefines.h"
#include "VidResources.h"

BEGIN_TRITRANIUM

class IVidCommands
{
public: /* BEGIN Utilities */

	/**
	 * Creates a new shader program from the specified builder.
	 * If an shader stage program is empty will not compile the shader for that part.
	 */
	virtual PVidShaderProgram *CreateShaderProgram(PVidShaderProgramBuilder &builder) = 0;
	virtual void ReleaseShaderProgram(PVidShaderProgram *program) = 0;
	
	virtual PVidBuffer *Allocate(uint32 size) = 0;
	virtual PVidBuffer *Allocate(const void *data, uint32 size) = 0;
	virtual PVidBuffer *Allocate(const void *data, uint32 size, EBufferUsage usage) = 0;
	virtual void Free(PVidBuffer *buffer) = 0;
	virtual void Update(PVidBuffer *buffer, const void *data, uint32 size) = 0;

	/**
	 * Allocates a new vertex buffer with the provided video buffer.
	 */
	virtual PVidVertexBuffer *AllocateVertexBuffer(PVidBuffer *buffer) = 0;

	/**
	 * Texture operations
	 */
	virtual void FreeTexture(PVidTexture *inTexture) = 0;
	virtual PVidTexture *AllocateTexture(uint16 width, uint16 height, EVidPixelType format, void *pixels) = 0;

public: /* State */

	/**
	 * Binds the provided program to the current context.
	 */
	virtual void UseProgram(const PVidShaderProgram *program) = 0;
	virtual void UnbindProgram() = 0;

	/**
	 * Binds the provided buffer to the buffer type
	 */
	virtual void BindBuffer(EBufferType target, PVidBuffer *buffer) = 0;

	/**
	 * Bind the required position or anything else required by a shader parameter's backend (like the position in OpenGL)
	 */
	virtual void BindVideoParameter(const PVidShaderProgram *program, PVidShaderParameter *parameter) = 0;

	/**
	 * Sets the current viewport
	 */
	// virtual void Viewport(int width, int height) = 0;

	// TODO:
	virtual void ClearColor(float r, float g, float b, float a) = 0;
	virtual void EnableDepthTest(bool enable) = 0;
	virtual void EnableDepthWrite(bool write) = 0;
	virtual void EnableBlend(bool enable) = 0;
	virtual void BlendFunc(EBlendFunc src, EBlendFunc dst) = 0;
	virtual void BindFramebuffer(int framebuffer) = 0;
	virtual void BindRenderbuffer(int renderbuffer) = 0;

public: /* Misc will not explain */
	
	// TODO: make this a little more abstact, since we're kinda tied to OpenGL in this case. Make very high level binds

	// virtual void BindBuffer(EBufferType target, int buffer) = 0;

	virtual void EnableVertexAttribArray(PVidShaderParameter *index) = 0;
	virtual void DisableVertexAttribArray(PVidShaderParameter *index) = 0;
	virtual void DrawArrays(EDrawMode mode, int first, int drawCount) = 0;

	virtual void VertexAttribPointer(int indx, int size, EVecType type, bool normalized, int stride, const void *offset) = 0;

	virtual void ActiveTexture(EActiveTexture texture) = 0;
	virtual void BindTexture(ETextureBinding target, int texture) = 0;	

public: /* Draw data */

	virtual void DrawMesh(class PMaterial *material, class PMesh *mesh) = 0;
};

END_TRITRANIUM

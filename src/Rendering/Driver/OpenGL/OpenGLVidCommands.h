/** Copyright (c) 2016 Lazu Ioan-Bogdan */

#pragma once

#include "glinclude.h"

#include "Platform\Platform.h"
#include "Platform\PlatformAssertion.h"
#include "Platform\PlatformLog.h"

#include "Core\Math\Vector.h"
#include "Core\Math\Matrix.h"

#include "Rendering\VidCommands.h"

#include "OpenGLVidResources.h"
#include "OpenGLVidState.h"

BEGIN_TRITRANIUM

static const TCHAR *TAG = TXT("OpenGLVidCommands");

#ifndef TRITRANIUM_DEBUG
	#define CHECK_GL_ERROR_DEBUG() do { } while(0)
#else
	#define CHECK_GL_ERROR_DEBUG()			\
		do {									\
			GLenum err__ = glGetError();	\
			if(err__ != GL_NO_ERROR) {		\
				LogError("OpenGL error 0x%04X in %s %s %d\n", err__, __FILE__, __FUNCTION__, __LINE__); \
			}								\
		} while(0)
#endif

static FORCEINLINE GLint ToOpenGLType(const EBufferType &type)
{
	switch (type)
	{
	case EBufferType::BT_ARRAY_BUFFER:
		return GL_ARRAY_BUFFER;
	case EBufferType::BT_ELEMENT_BUFFER:
		return GL_ELEMENT_ARRAY_BUFFER;
	}

	CHK(0);
	// No Warn
	return -1;
}

static FORCEINLINE GLint ToOpenGLType(const EBufferUsage &type)
{
	switch (type)
	{
	case EBufferUsage::BU_STATIC_DRAW:
		return GL_STATIC_DRAW;
	case EBufferUsage::BU_DYNAMIC_DRAW:
		return GL_DYNAMIC_DRAW;
	case EBufferUsage::BU_STREAM_DRAW:
		return GL_STREAM_DRAW;
	}

	CHK(0);
	// No Warn
	return -1;
}

static FORCEINLINE GLint ToOpenGLType(const EBlendFunc &func) {
	switch (func) {
	case EBlendFunc::BF_ZERO:
		return GL_ZERO;
	case EBlendFunc::BF_ONE:
		return GL_ONE;
	case EBlendFunc::BF_SRC_ALPHA:
		return GL_SRC_ALPHA;
	case EBlendFunc::BF_ONE_MINUS_SRC_ALPHA:
		return GL_ONE_MINUS_SRC_ALPHA;
	case EBlendFunc::BF_ONE_MINUS_DST_ALPHA:
		return GL_ONE_MINUS_DST_ALPHA;
	case EBlendFunc::BF_SRC_COLOR:
		return GL_SRC_COLOR;
	case EBlendFunc::BF_DST_COLOR:
		return GL_DST_COLOR;
	case EBlendFunc::BF_ONE_MINUS_SRC_COLOR:
		return GL_ONE_MINUS_SRC_COLOR;
	case EBlendFunc::BF_ONE_MINUS_DST_COLOR:
		return GL_ONE_MINUS_DST_COLOR;
	case EBlendFunc::BF_CONSTANT_COLOR:
		return GL_CONSTANT_COLOR;
	}

	CHK(0);
	// No Warn
	return -1;
}

static FORCEINLINE GLint ToOpenGLType(const EDrawMode &mode)
{
	switch (mode)
	{
	case DM_POINTS:
		return GL_POINTS;
	case DM_LINES:
		return GL_LINES;
	case DM_TRIANGLES:
		return GL_TRIANGLES;
	case DM_TRIANGLE_STRIP:
		return GL_TRIANGLE_STRIP;
	}

	CHK(0);
	// No Warn
	return -1;
}

static FORCEINLINE GLint ToOpenGLType(const EActiveTexture &texture)
{
	switch (texture)
	{
	case AT_TEXTURE_0:
		return GL_TEXTURE0;
	case AT_TEXTURE_1:
		return GL_TEXTURE1;
	case AT_TEXTURE_2:
		return GL_TEXTURE2;
	case AT_TEXTURE_3:
		return GL_TEXTURE3;
	case AT_TEXTURE_4:
		return GL_TEXTURE4;
	case AT_TEXTURE_5:
		return GL_TEXTURE5;
	}

	CHK(0);
	// No Warn
	return -1;
}

static FORCEINLINE GLint ToOpenGLType(const EVecType &type)
{
	switch (type)
	{
	case VT_BYTE:
		return GL_BYTE;
	case VT_SHORT:
		return GL_SHORT;
	case VT_INT:
		return GL_INT;
	case VT_FLOAT:
		return GL_FLOAT;
	case VT_DOUBLE:
		return GL_DOUBLE;
	}

	CHK(0);
	// No Warn
	return -1;
}

static FORCEINLINE GLint ToOpenGLType(const ETextureBinding &binding)
{
	switch (binding)
	{
	case TB_TEXTURE_2D:
		return GL_TEXTURE_2D;
	case TB_TEXTURE_CUBE:
		return GL_TEXTURE_CUBE_MAP;
	}

	CHK(0);
	// No Warn
	return -1;
}

class OpenGLVidCommands : public IVidCommands
{
public: /** Utilities */
	PVidShaderProgram *CreateShaderProgram(PVidShaderProgramBuilder &builder) OVERRIDE
	{
		GLuint vs, fs, gs;
		
		bool hasVs = builder.mVertexShaderCode.Length() > 0;
		bool hasFs = builder.mFragmentShaderCode.Length() > 0;
		bool hasGs = builder.mGeometryShaderCode.Length() > 0;

		LogDebug(TXT("Compiling shader program with vs %d, fs: %d, gs: %d"), hasVs, hasFs, hasGs);

		if(hasVs) vs = CompileShaderStage(EShaderType::ST_VERTEX, builder.mVertexShaderCode);
		if(hasFs) fs = CompileShaderStage(EShaderType::ST_FRAGMENT, builder.mFragmentShaderCode);
		if(hasGs) gs = CompileShaderStage(EShaderType::ST_GEOMETRY, builder.mGeometryShaderCode);

		GLint program = glCreateProgram();
		CHECK_GL_ERROR_DEBUG();

		if (hasVs) glAttachShader(program, vs);
		if (hasFs) glAttachShader(program, fs);
		if (hasGs) glAttachShader(program, gs);

		CHECK_GL_ERROR_DEBUG();
		
		// Link program, checked later
		glLinkProgram(program);
		CHECK_GL_ERROR_DEBUG();

		// Get log and errors
		glValidateProgram(program);

		GLint status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		
		// Check for errors		
		if (status == 0) 
		{
			PString log;
			log.Reserve(4096);

			glGetProgramInfoLog(program, 4096, NULL, &log[0]);

			LogError(TXT("Program log: %s\n"), log.c_str());

			glDeleteProgram(program);
		}

		CHK(status != 0);

		// Clear shaders
		if (hasVs) glDeleteShader(vs);
		if (hasFs) glDeleteShader(fs);
		if (hasGs) glDeleteShader(gs);

		OpenGLVidShaderProgram *glProgram = new OpenGLVidShaderProgram();
		glProgram->mProgram = program;

		// Initialize the video resource if needed
		glProgram->InitVidResource();

		return glProgram;
	}

	virtual void ReleaseShaderProgram(PVidShaderProgram *program) OVERRIDE
	{
		OpenGLVidShaderProgram *glProgram = (OpenGLVidShaderProgram *)program;

		glDeleteProgram(glProgram->mProgram);
		CHECK_GL_ERROR_DEBUG();
	}

	virtual PVidBuffer *Allocate(uint32 size) OVERRIDE
	{
		return Allocate(NULL, size);
	}

	virtual PVidBuffer *Allocate(const void *data, uint32 size) OVERRIDE
	{
		return Allocate(data, size, EBufferUsage::BU_STATIC_DRAW);
	}

	virtual PVidBuffer *Allocate(const void *data, uint32 size, EBufferUsage usage) OVERRIDE
	{
		GLuint buffer;

		glGenBuffers(1, &buffer);
		CHECK_GL_ERROR_DEBUG();

		BindBuffer(EBufferType::BT_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, size, data, ToOpenGLType(usage));
		CHECK_GL_ERROR_DEBUG();

		OpenGLVidBuffer *glBuffer = new OpenGLVidBuffer(size, usage);
		glBuffer->mBuffer = buffer;

		glBuffer->InitVidResource();

		return glBuffer;
	}

	virtual PVidVertexBuffer *AllocateVertexBuffer(PVidBuffer *buffer) OVERRIDE
	{
		return new OpenGLVidVertexBuffer(buffer);
	}

	virtual void Free(PVidBuffer *buffer) OVERRIDE
	{
		OpenGLVidBuffer *glBuffer = (OpenGLVidBuffer *)buffer;

		glDeleteBuffers(1, &glBuffer->mBuffer);		
		CHECK_GL_ERROR_DEBUG();
	}

	virtual void Update(PVidBuffer *buffer, const void *data, uint32 size) OVERRIDE
	{
		OpenGLVidBuffer *glBuffer = (OpenGLVidBuffer *)buffer;

		BindBuffer(EBufferType::BT_ARRAY_BUFFER, glBuffer->mBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);		
		CHECK_GL_ERROR_DEBUG();
	}
	
	virtual void FreeTexture(PVidTexture *inTexture) OVERRIDE;
	virtual PVidTexture *AllocateTexture(uint16 width, uint16 height, EVidPixelType format, void *pixels) OVERRIDE;

public: /* State commands */

	void UnbindProgram()
	{
		if (mState.mProgram != 0)
		{			
			glUseProgram(mState.mProgram = 0);
			CHECK_GL_ERROR_DEBUG();
		}
	}

	void UseProgram(const PVidShaderProgram *program)
	{		
		OpenGLVidShaderProgram *glProgram = (OpenGLVidShaderProgram *)program;

		if (mState.mProgram != glProgram->mProgram) 
		{
			mState.mProgram = glProgram->mProgram;

			glUseProgram(glProgram->mProgram);
			CHECK_GL_ERROR_DEBUG();
		}
	}

	FORCEINLINE void BindBuffer(EBufferType target, PVidBuffer *buffer) 
	{
		OpenGLVidBuffer *glBuffer = (OpenGLVidBuffer *)buffer;
		BindBuffer(target, glBuffer->mBuffer);
	}

	void BindVideoParameter(const PVidShaderProgram *program, PVidShaderParameter *parameter)
	{
		OpenGLVidShaderProgram *glProgram = (OpenGLVidShaderProgram *)program;
		OpenGLVidShaderParameter *glParameter = (OpenGLVidShaderParameter *)parameter;

		// Bind the parameter's location
		switch (glParameter->GetBindingType())
		{
		case SBT_ATTRIBUTE: 
			glParameter->mPosition = glGetAttribLocation(glProgram->mProgram, glParameter->GetName().c_str()); 
			break;
		case SBT_UNIFORM: 
			glParameter->mPosition = glGetUniformLocation(glProgram->mProgram, glParameter->GetName().c_str());
			break;
		}
	}

private: /* Private utilities */
	GLuint CompileShaderStage(EShaderType type, const PString &source)
	{
		GLuint shader = -1;

		switch (type)
		{
		case EShaderType::ST_VERTEX:
			shader = glCreateShader(GL_VERTEX_SHADER);
			break;
		case EShaderType::ST_FRAGMENT:
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		case EShaderType::ST_GEOMETRY:
			shader = glCreateShader(GL_GEOMETRY_SHADER);
			break;
		default:
			CHK(0);
		}

		const char *ansiiSource = source.c_str();
		
		glShaderSource(shader, 1, &ansiiSource, NULL);
		glCompileShader(shader);

		CHECK_GL_ERROR_DEBUG();

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);		

		if (status == 0)
		{
			PString log;
			log.Reserve(4096);

			glGetShaderInfoLog(shader, 4096, NULL, &log[0]);			

			LogError(TXT("Shader type: %d log: %s \n"), type, log.c_str());

			glDeleteShader(shader);			
		}

		CHK(status != 0);
		CHECK_GL_ERROR_DEBUG();

		return shader;
	}

private: /* Private commands */
	void BindBuffer(EBufferType target, GLuint buffer)
	{		
		if (target == EBufferType::BT_ARRAY_BUFFER && mState.mBoundArrayBuffer != buffer)
		{
			mState.mBoundArrayBuffer = buffer;
			glBindBuffer(ToOpenGLType(target), buffer);
		}

		else if (target == EBufferType::BT_ELEMENT_BUFFER && mState.mBoundElementBuffer != buffer)
		{
			mState.mBoundElementBuffer = buffer;
			glBindBuffer(ToOpenGLType(target), buffer);
		}
	}

public: /* To cleanup here */

	virtual void ClearColor(float r, float g, float b, float a)
	{
		mState.mClearColor.Set(r, g, b, a);
		glClearColor(r, g, b, a);		
	}

	virtual void EnableDepthTest(bool enable)
	{
		if (mState.mDepthState.mZTestEnabled != enable) {
			mState.mDepthState.mZTestEnabled = enable;

			if (enable) 
			{
				glEnable(GL_DEPTH_TEST);
			}
			else
			{
				glDisable(GL_DEPTH_TEST);
			}
		}
	}

	virtual void EnableDepthWrite(bool write)
	{
		if (mState.mDepthState.mZWriteEnabled != write) {
			mState.mDepthState.mZWriteEnabled = write;

			glDepthMask(write);
		}
	}

	virtual void EnableBlend(bool enable)
	{
		if (mState.mBlendState.mBlend != enable) {
			mState.mBlendState.mBlend = enable;

			if (enable)
			{
				glEnable(GL_BLEND);
			}
			else
			{
				glDisable(GL_BLEND);
			}
		}
	}

	virtual void BlendFunc(EBlendFunc src, EBlendFunc dst)
	{
		GLint ssrc = ToOpenGLType(src);
		GLint ddst = ToOpenGLType(dst);

		if (mState.mBlendState.mColorSrc != ssrc || mState.mBlendState.mColorDst != ddst) {
			mState.mBlendState.mColorSrc = ssrc;
			mState.mBlendState.mColorDst = ddst;

			glBlendFunc(ssrc, ddst);
		}
	}

	virtual void BindFramebuffer(GLint framebuffer)
	{
		if (framebuffer != mState.mFramebuffer) {
			mState.mFramebuffer = framebuffer;
			
			// glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);			
		}
	}

	virtual void BindRenderbuffer(GLint renderbuffer)
	{
		if (renderbuffer != mState.mRenderbuffer) {
			mState.mRenderbuffer = renderbuffer;

			// glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
		}
	}

	virtual void EnableVertexAttribArray(PVidShaderParameter *index)
	{
		OpenGLVidShaderParameter *param = (OpenGLVidShaderParameter *)index;
		glEnableVertexAttribArray(param->mPosition);
	}

	virtual void DisableVertexAttribArray(PVidShaderParameter *index)
	{
		OpenGLVidShaderParameter *param = (OpenGLVidShaderParameter *)index;
		glDisableVertexAttribArray(param->mPosition);
	}

	virtual void DrawArrays(EDrawMode mode, int first, int drawCount)
	{
		glDrawArrays(ToOpenGLType(mode), first, drawCount);
	}

	virtual void VertexAttribPointer(int indx, int size, EVecType type, bool normalized, int stride, const void* offset)
	{
		glVertexAttribPointer(indx, size, ToOpenGLType(type), normalized, stride, offset);
	}

	virtual void ActiveTexture(EActiveTexture texture)
	{
		GLint tex = ToOpenGLType(texture);

		if (mState.mActiveTexture != tex) {
			mState.mActiveTexture = tex;

			glActiveTexture(tex);
		}
	}

	virtual void BindTexture(ETextureBinding target, GLint texture)
	{
		if (target == ETextureBinding::TB_TEXTURE_2D && mState.mBoundTexture2D != texture) {
			mState.mBoundTexture2D = texture;
			
			glBindTexture(ToOpenGLType(target), texture);
		}
		else if (target == ETextureBinding::TB_TEXTURE_CUBE && mState.mBoundTextureCube != texture) {
			mState.mBoundTextureCube = texture;

			glBindTexture(ToOpenGLType(target), texture);
		}
	}

	void BindMaterialUniform(const PVidShaderParameter *uniform);

private: /* Various utils */
	void BindVertexAttrib(const PVidVertexBuffer *vertexBuffer, const PVidShaderParameter *param);

	

	void SetShaderParam(GLint location, float v)
	{
		glUniform1f(location, v);
	}

	void SetShaderParam(GLint location, int v)
	{
		glUniform1i(location, v);
	}

	void SetShaderParam(GLint location, const PVec2 &v)
	{
		glUniform2f(location, v.x, v.y);
	}

	void SetShaderParam(GLint location, const PVec3 &v)
	{
		glUniform3f(location, v.x, v.y, v.z);
	}

	void SetShaderParam(GLint location, const PVec4 &v)
	{
		glUniform4f(location, v.x, v.y, v.z, v.w);
	}

	void SetShaderParam(GLint location, const PMat3x3 &v)
	{
		glUniformMatrix3fv(location, 1, false, v.ToPtr());
	}

	void SetShaderParam(GLint location, const PMat4x4 &v)
	{
		glUniformMatrix4fv(location, 1, false, v.ToPtr());
	}

	void SetShaderTexture(GLint location, uint8 textureIndex, const class PVidTexture *v);

public: /* Draw commands */

	
	virtual void DrawMesh(PMaterial *material, PMesh *mesh);
	

private:
	OpenGLVidState mState;
};

typedef OpenGLVidCommands PVidCommands;

END_TRITRANIUM
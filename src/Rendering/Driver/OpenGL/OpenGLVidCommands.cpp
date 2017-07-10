/** Copyright (c) 2016 Lazu Ioan-Bogdan */

#include "OpenGLVidCommands.h"

#include "OpenGLVidResources.h"


#include "Engine\Asset\Material.h"
#include "Engine\Asset\Mesh.h"
#include "Engine\Asset\Texture.h"

BEGIN_TRITRANIUM

void OpenGLVidCommands::FreeTexture(PVidTexture *inTexture)
{
	OpenGLVidTexture *tex = (OpenGLVidTexture *)inTexture;

	glDeleteTextures(1, &tex->mTexture);
	CHECK_GL_ERROR_DEBUG();
}

PVidTexture *OpenGLVidCommands::AllocateTexture(uint16 width, uint16 height, EVidPixelType format, void *pixels)
{
	GLuint tex;
	glGenTextures(1, &tex);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

	// TODO: Get from texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	CHECK_GL_ERROR_DEBUG();

	uint32 bytesPerPixel;

	switch (format)
	{
	case EVidPixelType::PT_R8G8B8:
		bytesPerPixel = 3;
		break;
	case EVidPixelType::PT_R8G8B8A8:
		bytesPerPixel = 4;
		break;
	default:
		LogError(TXT("Unsupported type: %d"), format);
		CHK(0);
	}

	uint32 bytesPerRow = width * bytesPerPixel;

	if (bytesPerRow % 8 == 0)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 8);
	}
	else if (bytesPerRow % 4 == 0)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	}
	else if (bytesPerRow % 2 == 0)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
	}
	else
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	}

	CHECK_GL_ERROR_DEBUG();

	switch (format)
	{
	case EVidPixelType::PT_R8G8B8:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
		break;
	case EVidPixelType::PT_R8G8B8A8:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		break;
	}

	CHECK_GL_ERROR_DEBUG();

	// Alocate texture and set it's data
	OpenGLVidTexture *texture = new OpenGLVidTexture(ETextureBinding::TB_TEXTURE_2D);
	texture->mTexture = tex;

	return texture;
}

void OpenGLVidCommands::BindVertexAttrib(const PVidVertexBuffer *vertexBuffer, const PVidShaderParameter *param)
{
	CHK(param->GetBindingType() == EVidShaderBindingType::SBT_ATTRIBUTE);

	BindBuffer(EBufferType::BT_ARRAY_BUFFER, vertexBuffer->mBuffer);

	// Set the vertex attrib pointer
	VertexAttribPointer(
		((OpenGLVidShaderParameter *)param)->mPosition,
		vertexBuffer->mCoordsPerVertex,
		EVecType::VT_FLOAT, false,
		vertexBuffer->mStride, (void *)vertexBuffer->mOffset
		);
}

void OpenGLVidCommands::SetShaderTexture(GLint location, uint8 textureIndex, const PVidTexture *v)
{
	// Currently supported indices
	CHK(textureIndex >= 0 && textureIndex <= 5);

	OpenGLVidTexture *tex = (OpenGLVidTexture *)v;

	// TODO: Simple for now
	EActiveTexture activeTexture = static_cast<EActiveTexture>(textureIndex);

	// Bind data
	ActiveTexture(activeTexture);
	BindTexture(ETextureBinding::TB_TEXTURE_2D, tex->mTexture);

	// Set the uniform to the binded texture
	glUniform1i(location, activeTexture);
}

void OpenGLVidCommands::BindMaterialUniform(const PVidShaderParameter *uniform)
{
	CHK(uniform->GetBindingType() == EVidShaderBindingType::SBT_UNIFORM);

	switch (uniform->GetParamType())
	{
	case EVidShaderParamType::PT_FLOAT:
	{
		PVidShaderParamResourceHolder<float, MatVidShaderParameter> *holder = ((PVidShaderParamResourceHolder<float, OpenGLVidShaderParameter> *)(uniform));
		SetShaderParam(holder->mPosition, holder->GetResource());		
		break;
	}
	case EVidShaderParamType::PT_INT:
	{
		PVidShaderParamResourceHolder<int32, MatVidShaderParameter> *holder = ((PVidShaderParamResourceHolder<int32, OpenGLVidShaderParameter> *)(uniform));
		SetShaderParam(holder->mPosition, holder->GetResource());
		break;
	}
	case EVidShaderParamType::PT_VEC2F: 
	{
		PVidShaderParamResourceHolder<PVec2, MatVidShaderParameter> *holder = ((PVidShaderParamResourceHolder<PVec2, OpenGLVidShaderParameter> *)(uniform));
		SetShaderParam(holder->mPosition, holder->GetResource());
		break;
	}
	case EVidShaderParamType::PT_VEC3F:
	{
		PVidShaderParamResourceHolder<PVec3, MatVidShaderParameter> *holder = ((PVidShaderParamResourceHolder<PVec3, OpenGLVidShaderParameter> *)(uniform));
		SetShaderParam(holder->mPosition, holder->GetResource());
		break;
	}
	case EVidShaderParamType::PT_VEC4F:
	{
		PVidShaderParamResourceHolder<PVec4, MatVidShaderParameter> *holder = ((PVidShaderParamResourceHolder<PVec4, OpenGLVidShaderParameter> *)(uniform));
		SetShaderParam(holder->mPosition, holder->GetResource());
		break;
	}
	case EVidShaderParamType::PT_MAT3x3F:
	{
		PVidShaderParamResourceHolder<PMat3x3, MatVidShaderParameter> *holder = ((PVidShaderParamResourceHolder<PMat3x3, OpenGLVidShaderParameter> *)(uniform));
		SetShaderParam(holder->mPosition, holder->GetResource());
		break;
	}
	case EVidShaderParamType::PT_MAT4x4F:
	{
		PVidShaderParamResourceHolder<PMat4x4, MatVidShaderParameter> *holder = ((PVidShaderParamResourceHolder<PMat4x4, OpenGLVidShaderParameter> *)(uniform));
		SetShaderParam(holder->mPosition, holder->GetResource());
		break;
	}
	case EVidShaderParamType::PT_TEXTURE_2D:			
	{
		PVidShaderParamResourceHolder<PTexture *, MatVidShaderParameterTexture> *holder = ((PVidShaderParamResourceHolder<PTexture *, OpenGLVidShaderParameterTexture> *)(uniform));
		SetShaderTexture(holder->mPosition, holder->mOrder, holder->GetResource()->GetVidTexture());
		break;
	}
	}
}


void OpenGLVidCommands::DrawMesh(PMaterial *material, PMesh *mesh)
{
	// Use the material's shader
	UseProgram(material->GetShader()->GetProgram());

	// Enable the attribute array
	const TList<PVidShaderParameter *> &attr = material->GetShader()->GetAttributeParams();
	for (uint32 i = 0; i < attr.Size(); i++)
	{
		EnableVertexAttribArray(attr[i]);
	}

	// TODO: Set the material's matrix data if we have it like camera/mv/mvp etc...


	// Bind the material's data
	const TList<PVidShaderParameter *> &uniforms = material->ForBind();

	for (uint32 i = 0; i < uniforms.Size(); i++)
	{		
		BindMaterialUniform(uniforms[i]);
	}

	// Bind the mesh's data
	if (mesh->HasBuffVertex() && material->HasVertexPos())
	{
		BindVertexAttrib(mesh->GetBuffVertex(), material->GetVertexPos());
	}

	if (mesh->HasBuffUv() && material->HasUv0Pos())
	{
		BindVertexAttrib(mesh->GetBuffUv(), material->GetUv0Pos());
	}

	if (mesh->HasBuffNormal() && material->HasNormalPos())
	{
		BindVertexAttrib(mesh->GetBuffNormal(), material->GetNormalPos());
	}

	if (mesh->HasBuffTangent() && material->HasTangentPos())
	{
		BindVertexAttrib(mesh->GetBuffTangent(), material->GetTangentPos());
	}

	// Issue the draw command
	DrawArrays(EDrawMode::DM_TRIANGLES, 0, mesh->GetDrawCount());

	// Disable the attribute array
	for (uint32 i = 0; i < attr.Size(); i++)
	{
		DisableVertexAttribArray(attr[i]);
	}

}


END_TRITRANIUM
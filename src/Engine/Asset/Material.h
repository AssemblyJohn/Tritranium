/** Copyright (c) 2016 Lazu Ioan-Bogdan */

#ifndef __Y_VID_MATERIAL__
#define __Y_VID_MATERIAL__

#include "Platform\Platform.h"
#include "Platform\PlatformVideo.h"

#include "Core\CoreLite.h"
#include "Engine\Engine.h"

#include "Rendering\VidResources.h"

#include "ShaderProgram.h"
#include "Texture.h"

BEGIN_TRITRANIUM

/**
 * TODO: proxy this somehow that it does not hold raw positions for attributes but handler. (like if we want to write for DX too)
 *
 * A material is build out of a shader. It contains the shader's parameters
 * and the resources that will be bound to those parameters.
 *
 * @author Lazu Ioan-Bogdan
 */
class PMaterial {	

public:
	/**
	* Builds a material from the provided shader program.
	*
	* @param shader
	*/
	PMaterial(PEngine *engine, PShaderProgram *shader);	
	~PMaterial();

	PShaderProgram *GetShader()
	{
		return mShader;
	}

	bool HasVertexPos()
	{
		return mVertexPosition != NULL;
	}

	bool HasNormalPos()
	{
		return mNormalPosition != NULL;
	}

	bool HasUv0Pos()
	{
		return mUv0Position != NULL;
	}

	bool HasTangentPos()
	{
		return mTangentPosition != NULL;
	}

	bool HasTextureDiffuse()
	{
		return mTextureDiffuse != NULL;
	}

	PVidShaderParameter *GetVertexPos()
	{
		return mVertexPosition;
	}

	PVidShaderParameter *GetNormalPos()
	{
		return mNormalPosition;
	}

	PVidShaderParameter *GetUv0Pos()
	{
		return mUv0Position;
	}

	PVidShaderParameter *GetTangentPos()
	{
		return mTangentPosition;
	}

	PVidShaderParameter *GetTextureDiffuse()
	{
		return mTextureDiffuse;
	}

	FORCEINLINE bool HasParameter(const PString &name)
	{
		return mShader->HasParameter(name);;
	}

	void SetFloat(const PString &name, const float v) 
	{
		// Check that it has the parameter and that it is of the correct type
		CHK(HasParameter(name));
		CHK(((PVidShaderParamResourceHolder<PVec2, MatVidShaderParameter> *)(mResources[name]))->GetParamType() == EVidShaderParamType::PT_FLOAT);

		((PVidShaderParamResourceHolder<float, MatVidShaderParameter> *)(mResources[name]))->SetResource(v);
	}
	
	void SetInt(const PString &name, const int32 v) 
	{
		CHK(HasParameter(name));
		CHK(((PVidShaderParamResourceHolder<PVec2, MatVidShaderParameter> *)(mResources[name]))->GetParamType() == EVidShaderParamType::PT_INT);

		((PVidShaderParamResourceHolder<int32, MatVidShaderParameter> *)(mResources[name]))->SetResource(v);
	}

	void SetVec2(const PString &name, const PVec2 &v) 
	{	
		CHK(HasParameter(name));
		CHK(((PVidShaderParamResourceHolder<PVec2, MatVidShaderParameter> *)(mResources[name]))->GetParamType() == EVidShaderParamType::PT_VEC2F);

		((PVidShaderParamResourceHolder<PVec2, MatVidShaderParameter> *)(mResources[name]))->SetResource(v);
	}

	void SetVec3(const PString &name, const PVec3 &v) 
	{
		CHK(HasParameter(name));
		CHK(((PVidShaderParamResourceHolder<PVec2, MatVidShaderParameter> *)(mResources[name]))->GetParamType() == EVidShaderParamType::PT_VEC3F);

		((PVidShaderParamResourceHolder<PVec3, MatVidShaderParameter> *)(mResources[name]))->SetResource(v);
	}

	void SetVec4(const PString &name, const PVec4 &v) 
	{
		CHK(HasParameter(name));
		CHK(((PVidShaderParamResourceHolder<PVec2, MatVidShaderParameter> *)(mResources[name]))->GetParamType() == EVidShaderParamType::PT_VEC4F);

		((PVidShaderParamResourceHolder<PVec4, MatVidShaderParameter> *)(mResources[name]))->SetResource(v);
	}

	void SetMat3(const PString &name, const PMat3x3 &v) 
	{
		CHK(HasParameter(name));
		CHK(((PVidShaderParamResourceHolder<PVec2, MatVidShaderParameter> *)(mResources[name]))->GetParamType() == EVidShaderParamType::PT_MAT3x3F);

		((PVidShaderParamResourceHolder<PMat3x3, MatVidShaderParameter> *)(mResources[name]))->SetResource(v);
	}

	void SetMat4(const PString &name, const PMat4x4 &v) 
	{
		CHK(HasParameter(name));
		CHK(((PVidShaderParamResourceHolder<PMat4x4, MatVidShaderParameter> *)(mResources[name]))->GetParamType() == EVidShaderParamType::PT_MAT4x4F);

		((PVidShaderParamResourceHolder<PMat4x4, MatVidShaderParameter> *)(mResources[name]))->SetResource(v);
	}

	
	void SetTexture(const PString &name, PTexture *v) {
		CHK(HasParameter(name));
		CHK(((PVidShaderParamResourceHolder<PTexture *, MatVidShaderParameterTexture> *)(mResources[name]))->GetParamType() == EVidShaderParamType::PT_TEXTURE_2D);

		((PVidShaderParamResourceHolder<PTexture *, MatVidShaderParameterTexture> *)(mResources[name]))->SetResource(v);
	}

	/*
	void SetTexture(PString name, int texture, int byteSize) {
		VidTexture res = (VidTexture)mResources.get(name).resource;

		res.setVidName(texture);
		res.setBytSize(byteSize);
	}
	*/

	/**
	 * Uniform for bind. It can be retrieved from a script and used to bind certain data to a material. Alternatively
	 * we can use the associated 'set' methods.
	 *
	 * @param name
	 *              Uniform's name
	 * @return The video resource with that name
	 */
	template<typename T> 
	T GetUniformResource(PString &name) 
	{
		CHK(HasParameter(name));

		return ((PVidShaderParamResourceHolder<PVec2, PVidShaderParameter> *)(mResources[name]))->GetResource();
	}
	
	/** Performs the uniform bind for the shader */
	const TList<PVidShaderParameter *> &ForBind() const
	{
		return mForBind;
	}

private:
	// Populates all the material's required data
	void Populate();

	// Utils, private
	void PopulateDefaultPositions();
	void PopulateDefaultMatrices();
	void PopulateDefaultTextures();

private: /* Engine related fields */
	PEngine *mEngine;
	PVidCommands *mVidCommands;

private: /* Resources */
	TMap<PString, PVidShaderParameter *> mResources;
	TList<PVidShaderParameter *> mForBind;

	// Shader resource
	PShaderProgram *mShader;

private: /* Default positions */
	// Default positions for attributes, if we have
	PVidShaderParameter *mVertexPosition;
	PVidShaderParameter *mNormalPosition;
	PVidShaderParameter *mUv0Position;
	PVidShaderParameter *mTangentPosition;

	// Default positions for uniforms, if we have
	PVidShaderParameter *mMatrixModel;
	PVidShaderParameter *mMatrixView;
	PVidShaderParameter *mMatrixProjection;
	PVidShaderParameter *mMatrixMv;
	PVidShaderParameter *mMatrixMvp;

	// Default positions for textures
	PVidShaderParameter *mTextureDiffuse;	

	// TODO: add blend mode
};

END_TRITRANIUM

#endif

/** Copyright (c) 2016 Lazu Ioan-Bogdan */

#include "Material.h"

BEGIN_TRITRANIUM

PMaterial::PMaterial(PEngine *engine, PShaderProgram *shader) :
	mVertexPosition(NULL),
	mUv0Position(NULL),
	mNormalPosition(NULL),
	mTangentPosition(NULL),
	mMatrixModel(NULL),
	mMatrixView(NULL),
	mMatrixProjection(NULL),
	mMatrixMv(NULL),
	mMatrixMvp(NULL),
	mTextureDiffuse(NULL)
{
	mEngine = engine;
	mVidCommands = engine->GetVidCommands();

	mShader = shader;

	Populate();
}

PMaterial::~PMaterial()
{
	for (uint32 i = 0; i < mForBind.Size(); i++)
	{
		delete mForBind[i];
	}

	mForBind.Clear();
	mResources.Clear();
}

// Populates all the material's required data
void PMaterial::Populate()
{	
	int foundTextures = 0;

	for (uint32 i = 0; i < mShader->GetUniformParams().Size(); i++)
	{
		MatVidShaderParameter *param = (MatVidShaderParameter *)mShader->GetUniformParams()[i];

		// Resource
		PVidShaderParameter *res;

		switch (param->GetParamType()) {
		case EVidShaderParamType::PT_FLOAT:
			res = new PVidShaderParamResourceHolder<float, MatVidShaderParameter>(param);
			break;
		case EVidShaderParamType::PT_INT:
			res = new PVidShaderParamResourceHolder<int32, MatVidShaderParameter>(param);
			break;
		case EVidShaderParamType::PT_VEC2F:
			res = new PVidShaderParamResourceHolder<PVec2, MatVidShaderParameter>(param);
			break;
		case EVidShaderParamType::PT_VEC3F:
			res = new PVidShaderParamResourceHolder<PVec3, MatVidShaderParameter>(param);
			break;
		case EVidShaderParamType::PT_VEC4F:
			res = new PVidShaderParamResourceHolder<PVec4, MatVidShaderParameter>(param);
			break;
		case EVidShaderParamType::PT_MAT3x3F:
			res = new PVidShaderParamResourceHolder<PMat3x3, MatVidShaderParameter>(param);
			break;
		case EVidShaderParamType::PT_MAT4x4F:
			res = new PVidShaderParamResourceHolder<PMat4x4, MatVidShaderParameter>(param);
			break;
		case PT_TEXTURE_2D:
			res = new PVidShaderParamResourceHolder<PTexture *, MatVidShaderParameterTexture>((MatVidShaderParameterTexture *)param);
			break;
			/*
		case PT_TEXTURE_CUBE:
			res = handleTextureParam(++foundTextures, ETextureBinding.TEXTURE_CUBE, param);
			break;
			*/
		default:
			LogError(TAG, "Invalid type: %d", param->GetParamType());
			CHK(0);
			break;
		}

		// Add the resource to the resource holder
		mResources[param->GetName()] = res;
		mForBind.Add(res);
	}

	// Get some default positions
	PopulateDefaultPositions();
	PopulateDefaultMatrices();
	PopulateDefaultTextures();
}

void PMaterial::PopulateDefaultPositions() 
{	
	// We need at least a vertex pointer
	if (HasParameter(VID_ATTR_VERTEX)) mVertexPosition = mShader->GetParameter(VID_ATTR_VERTEX);

	// TODO: automate and make a list from that so that we don't have to always iterate through it

	// Optional positions
	if (HasParameter(VID_ATTR_NORMAL)) mNormalPosition = mShader->GetParameter(VID_ATTR_NORMAL);
	if (HasParameter(VID_ATTR_UV0)) mUv0Position = mShader->GetParameter(VID_ATTR_UV0);
	if (HasParameter(VID_ATTR_TANGENT)) mTangentPosition = mShader->GetParameter(VID_ATTR_TANGENT);

	// Texture positions

}

void PMaterial::PopulateDefaultMatrices()
{
	if (HasParameter(VID_UNI_MTX_MODEL)) mMatrixModel = mShader->GetParameter(VID_UNI_MTX_MODEL);
	if (HasParameter(VID_UNI_MTX_VIEW)) mMatrixView = mShader->GetParameter(VID_UNI_MTX_VIEW);
	if (HasParameter(VID_UNI_MTX_PROJECTION)) mMatrixProjection = mShader->GetParameter(VID_UNI_MTX_PROJECTION);
	if (HasParameter(VID_UNI_MTX_MV)) mMatrixMv = mShader->GetParameter(VID_UNI_MTX_MV);
	if (HasParameter(VID_UNI_MTX_MVP)) mMatrixMvp = mShader->GetParameter(VID_UNI_MTX_MVP);
}

void PMaterial::PopulateDefaultTextures()
{
	if (HasParameter(VID_UNI_TEX_DIFFUSE)) mTextureDiffuse = mShader->GetParameter(VID_UNI_TEX_DIFFUSE);
}

END_TRITRANIUM
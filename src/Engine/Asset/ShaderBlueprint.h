#pragma once

#include "Core\CoreLite.h"

#include "Engine\Engine.h"
#include "Rendering\VidCommands.h"

#include "AssetBlueprint.h"
#include "ShaderProgram.h"

BEGIN_TRITRANIUM

/**
 * Preprocess directive for shader in case we need.
 */ 
struct PShaderPreprocDirective 
{
	EShaderType mStage;
	PString mTokenReplace;
	PString mTokenReplacement;

	PShaderPreprocDirective() { }

	PShaderPreprocDirective(EShaderType mStage, PString mTokenReplace, PString mTokenReplacement) 
	{
		this->mStage = mStage;
		this->mTokenReplace = mTokenReplace;
		this->mTokenReplacement = mTokenReplacement;
	}
	
	PString ToString() 
	{
		PString string;
		
		string = string + "ShaderPreprocDirective{" +
			"mStage=" + mStage +
			", mTokenReplace='" + mTokenReplace + "'" +
			", mTokenReplacement='" + mTokenReplacement + "'" +
		'}';

		return string;
	}
};

/**
 * Shader asset blueprint. Will build a shader program.
 */
class PShaderBlueprint : public PAssetBlueprint
{
public:	
	PShaderBlueprint(PEngine *engine, const PString &name, const TCHAR *inVs, const TCHAR *inFs, bool inRawData = false) :
		PAssetBlueprint(engine, name),		
		mRawData(inRawData)
	{ 
		if (mRawData)
		{
			mVertexCode = (inVs);
			mPixelCode = (inFs);
		}
		else
		{
			mVsFilePath = (inVs);
			mFsFilePath = (inFs);
		}		
	}

	PShaderBlueprint(PEngine *engine, const PString &name, const PString &vsFile, const PString &fsFile, const TList<PShaderPreprocDirective> &directives) :
		PAssetBlueprint(engine, name),
		mVsFilePath(vsFile),
		mFsFilePath(fsFile),
		mPreprocessDirectives(directives),
		mRawData(false)
	{ }

	bool RequireAsyncLoad() OVERRIDE 
	{
		return true;
	}
	
	void AsyncLoad() OVERRIDE 
	{
		// Read the code if the data is not raw and we need to load it from the file
		if (mRawData == false)
		{
			mVertexCode = PFileUtils::ReadEntireFile(mVsFilePath);
			mPixelCode = PFileUtils::ReadEntireFile(mFsFilePath);
		}
		
		//Replace the preprocess directives
		if (mPreprocessDirectives.Size() > 0) 
		{
			for (uint32 i = 0; i < mPreprocessDirectives.Size(); i++)
			{
				const PShaderPreprocDirective &directive = mPreprocessDirectives[i];

				switch (directive.mStage)
				{
				case EShaderType::ST_VERTEX:
					mVertexCode.Replace(directive.mTokenReplace, directive.mTokenReplacement);
					break;
				case EShaderType::ST_FRAGMENT:
					mPixelCode.Replace(directive.mTokenReplace, directive.mTokenReplacement);
					break;
				}
			}

			LogDebug("Preprocessed shader code: ");
			LogDebug("Vert: %s", mVertexCode.c_str());
			LogDebug("Frag: %s", mPixelCode.c_str());
		}

		// Get the required params
		PShaderDependencyParser::ExtractParameters(mRequiredParams, mVertexCode, mPixelCode);
	}
	
	void VidInit() OVERRIDE
	{
		PVidShaderProgramBuilder builder;

		builder.mVertexShaderCode = mVertexCode;
		builder.mFragmentShaderCode = mPixelCode;
		
		// Create the video shader
		mVidShader = mVidCommands->CreateShaderProgram(builder);

		// Use the program, getting things prepared for the binding
		mVidCommands->UseProgram(mVidShader);

		// Resolve shader parameter bindings
		ResolveBindings();
	}
	
	PShaderProgram *Build() OVERRIDE
	{		
		// Set params for the builder
		PShaderProgramBuilder builder;

		builder.mShader = mVidShader;
		builder.mParameters = mRequiredParams;

		// Return a new shader program asset
		return new PShaderProgram(mEngine, builder);
	}

	void ResolveBindings() 
	{
		for (int i = (mRequiredParams.Size() - 1); i >= 0; i--) 
		{
			// Bind it's location
			mVidCommands->BindVideoParameter(mVidShader, mRequiredParams[i]);
		}
	}

private:
	PString mVsFilePath;
	PString mFsFilePath;

	// Code
	PString mVertexCode;
	PString mPixelCode;

	// Program
	PVidShaderProgram *mVidShader;

	// Params and program
	TList<PVidShaderParameter *> mRequiredParams;

	// Preprocess directives, to apply before compiling a shader
	TList<PShaderPreprocDirective> mPreprocessDirectives;

	// If the data was raw
	bool mRawData;

};

END_TRITRANIUM
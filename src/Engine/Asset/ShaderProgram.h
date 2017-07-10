#ifndef __TRITRANIUM_SHADER__
#define __TRITRANIUM_SHADER__

#include "Core\CoreLite.h"

#include "Platform\PlatformAssertion.h"
#include "Platform\PlatformLog.h"

#include "Rendering\VidResources.h"

#include "Engine\Engine.h"

#include "Asset.h"

BEGIN_TRITRANIUM

/**
 * Shader program built by a ShaderProgramBlueprint.
 *
 * Contains the real video data to the underlying video shader program.
 */
class PShaderProgram : public PAsset
{	
public:
	PShaderProgram(PEngine *engine, PShaderProgramBuilder &builder) : 
		PAsset(engine) 
	{		
		mVidCommands = engine->GetVidCommands();

		mProgram = builder.mShader;
		mParameters = builder.mParameters;

		// Build data from the parameters, should be very lightweight
		for (uint32 i = 0; i < mParameters.Size(); i++)
		{	
			// For name quick access
			mNamedParameters.Put(mParameters[i]->GetName(), mParameters[i]);

			// By type
			switch (mParameters[i]->GetBindingType())
			{
			case SBT_ATTRIBUTE:
				mAttributeParameters.Add(mParameters[i]);
				break;
			case SBT_UNIFORM:
				mUniformParameters.Add(mParameters[i]);
				break;
			}
		}
	}

	~PShaderProgram()
	{
		// Delete all parameters
		for (uint32 i = 0; i < mParameters.Size(); i++)
		{
			delete mParameters[i];
		}

		// Delete program
		delete mProgram;
	}

	/**
	 * Used to dispose the shader when we don't need it any more.
	 */
	void ReleaseGPU() 
	{
		LogDebug(TXT("Releasing shader: %s"), mName.c_str());

		mVidCommands->ReleaseShaderProgram(mProgram);
	}

	const TList<PVidShaderParameter *> &GetParameterList() const
	{
		return mParameters;
	}

	const TMap<PString, PVidShaderParameter *> &GetParamMap() const
	{
		return mNamedParameters;
	}

	const TList<PVidShaderParameter *> &GetAttributeParams() const
	{
		return mAttributeParameters;
	}

	const TList<PVidShaderParameter *> &GetUniformParams() const
	{
		return mUniformParameters;
	}

	PVidShaderParameter *GetParameter(const PString &name) const
	{		
		CHK(HasParameter(name) == true);

		return mNamedParameters[name];
	}

	bool HasParameter(const PString &name) const
	{
		return mNamedParameters.Contains(name);
	}

	const PVidShaderProgram *GetProgram() const
	{
		return mProgram;
	}

	// TODO: see if this is required for global binds that take place once
	void Bind() 
	{
		
	}

private:

	// Parameters this shader can receive. Contains global ones too. The material will not use this one..
	TList<PVidShaderParameter *> mParameters;

	// Lists for quick search
	TMap<PString, PVidShaderParameter *> mNamedParameters;

	// Params for quick binding
	TList<PVidShaderParameter *> mAttributeParameters;
	TList<PVidShaderParameter *> mUniformParameters;

	// Shader program video resource, instead of a plain 'integer'
	PVidShaderProgram *mProgram;
};

END_TRITRANIUM

#endif
/** Copyright (c) 2016 Lazu Ioan-Bogdan */

#include "OpenGLVidDependencyParser.h"
#include "OpenGLVidResources.h"

#include "Platform\PlatformLog.h"
#include "Core\CoreLite.h"

BEGIN_TRITRANIUM

// Split token, it's the '\n' from the file utils reader
static char* TOK_SPLIT = "\n";

static char* TOK_ATTRIBUTE = "attribute";
static char* TOK_UNIFORM = "uniform";

// Token stop symbol. When we reach a line containing 'main' we stop
static char* TOK_STOP_PARSE = "main";

// Primitive types
static char* TYPE_FLOAT = "float";
static char* TYPE_INT = "int";

// Vector types
static char* TYPE_VEC2 = "vec2";
static char* TYPE_VEC3 = "vec3";
static char* TYPE_VEC4 = "vec4";

// Matrix types
static char* TYPE_MAT2 = "mat2";
static char* TYPE_MAT3 = "mat3";
static char* TYPE_MAT4 = "mat4";

// Texture types
static char* TYPE_TEX2D = "sampler2D";
static char* TYPE_TEX3D = "samplerCube";

static EVidShaderParamType GetType(const PString &type) {
	EVidShaderParamType t;

	if (type == TYPE_INT)
	{
		t = EVidShaderParamType::PT_INT;
	}
	else if (type == TYPE_FLOAT)
	{
		t = EVidShaderParamType::PT_FLOAT;
	}
	else if (type == TYPE_VEC2)
	{
		t = EVidShaderParamType::PT_VEC2F;
	}
	else if (type == TYPE_VEC3)
	{
		t = EVidShaderParamType::PT_VEC3F;
	}
	else if (type == TYPE_VEC4)
	{
		t = EVidShaderParamType::PT_VEC4F;
	}
	else if (type == TYPE_MAT2)
	{
		t = EVidShaderParamType::PT_MAT2x2F;
	}
	else if (type == TYPE_MAT3)
	{
		t = EVidShaderParamType::PT_MAT3x3F;
	}
	else if (type == TYPE_MAT4)
	{
		t = EVidShaderParamType::PT_MAT4x4F;
	}
	else if (type == TYPE_TEX2D)
	{
		t = EVidShaderParamType::PT_TEXTURE_2D;
	}
	else if (type == TYPE_TEX3D)
	{
		t = EVidShaderParamType::PT_TEXTURE_CUBE;
	}
	else {
		LogError("No token for type: %s", type);
		CHK(0);

		/*
		throw new IllegalArgumentException("No type for token: " + type +
		" Check that in the code nobody defines a type as another. (for example '#define float2 vec2' or something like this)."
		*/
	}

	return t;
}

/**
* Extracts a parameter or null if no parameter could be found.
*/
static PVidShaderParameter *ExtractFromLine(PString &line) {
	TList<PString> subtok;
	PString::Split(subtok, line, "(\\s+|/)");

	if (subtok.Size() == 0)
	{
		LogDebug("No subtokens found!");
		return nullptr;
	}

	EVidShaderBindingType shaderParam = EVidShaderBindingType::SBT_ATTRIBUTE;
	EVidShaderParamType type = EVidShaderParamType::PT_FLOAT;
	PString name;

	bool hasVal = false;

	if (subtok[0] == TOK_ATTRIBUTE)
	{
		LogDebug("Attribute found.");
		shaderParam = EVidShaderBindingType::SBT_ATTRIBUTE;

		type = GetType(subtok[1]);
		name = subtok[2];

		hasVal = true;
	}
	else if (subtok[0] == TOK_UNIFORM)
	{
		LogDebug("Uniform found.");
		shaderParam = EVidShaderBindingType::SBT_UNIFORM;

		type = GetType(subtok[1]);
		name = subtok[2];

		hasVal = true;
	}
	else
	{
		LogDebug("Nothing found.");
	}
	if (hasVal)
	{
		OpenGLVidShaderParameter *param;

		// OpenGL param
		if (type == EVidShaderParamType::PT_TEXTURE_2D)
		{
			param = new OpenGLVidShaderParameterTexture(name, shaderParam, type);
		}
		else
		{
			param = new OpenGLVidShaderParameter(name, shaderParam, type);
		}

		// Data about the parameter
		LogDebug(TXT("Name: %s, binding type: %d, param type: %d"), name.c_str(), shaderParam, type);

		return param;
	}
	else
	{
		return nullptr;
	}
}

static void ParseLines(const TList<PString> tokens, TList<PVidShaderParameter *> &out) {
	uint8 texturePos = 0;

	for (uint32 i = 0; i < tokens.Size(); i++) 
	{
		// Remove the ";" since it might cause trouble to us for the name, also lowp, highp, mediump
		PString token = tokens[i];

		// Replace all data and trim
		token.Replace(";", "");
		token.Replace("lowp", "");
		token.Replace("highp", "");
		token.Replace("mediump", "");
		token.Trim();

		if (token.Contains(TOK_STOP_PARSE)) 
		{
			LogDebug(TXT("Found 'main', stopping parsing..."));
			break;
		}

		PVidShaderParameter *param = ExtractFromLine(token);

		if (param != nullptr)
		{
			if (param->GetParamType() == EVidShaderParamType::PT_TEXTURE_2D)
			{
				LogDebug(TXT("Found texture at index: %d"), texturePos);
				((OpenGLVidShaderParameterTexture *)param)->mOrder = texturePos++;
			}

			out.Add(param);
		}
	}
}

void PShaderDependencyParser::ExtractParameters(TList<PVidShaderParameter *> &out, PString &vsShader, PString &fsShader)
{
	TList<PString> vsSplit;
	PString::Split(vsSplit, vsShader, TOK_SPLIT);
	TList<PString> fsSplit;
	PString::Split(fsSplit, fsShader, TOK_SPLIT);

	ParseLines(vsSplit, out);
	ParseLines(fsSplit, out);

	// Some data
	LogDebug(TXT("Extracted param count for shader [vs]: %s [fs]: %s [count]: %d"), vsShader.c_str(), fsShader.c_str(), out.Size());
}

END_TRITRANIUM
/** Copyright (c) 2016 Lazu Ioan-Bogdan */

#pragma once

#include "Platform\Platform.h"
#include "Core\CoreLite.h"

#include "Rendering\VidResources.h"

BEGIN_TRITRANIUM

/**
 * Extracts required uniforms and attributes from a GLSL shaders source code, along with their name and type.
 * Declaring them somewhere and forcing people have the names right is really tedious.
 */
class PShaderDependencyParser 
{
public:
	/**
	* Extracts all the parameters of the provided shaders to the list.
	*
	* @return	The number of parameters written to the list.
	*/
	static void ExtractParameters(TList<PVidShaderParameter *> &out, PString &vsShader, PString &fsShader);
};

END_TRITRANIUM
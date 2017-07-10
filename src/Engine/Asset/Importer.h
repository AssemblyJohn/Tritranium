/** Copyright (c) 2016 Lazu Ioan-Bogdan */

#ifndef __TRITRANIUM_IMPORTER_H__
#define __TRITRANIUM_IMPORTER_H__

#include "Platform\Platform.h"
#include "Core\Core.h"
#include "Rendering\VidDefines.h"

BEGIN_TRITRANIUM

struct PMeshImportedData
{
	PString name;
	TList<PVec3> vertex;
	TList<PVec3> normal;
	TList<PVec2> uv;
};

struct PTextureImportedData
{
	EVidPixelType mType;
	uint16 mWidth;
	uint16 mHeight;
	PData mData;
};

/**
 * Simple importer for data.
 */
class PImporter
{
public:	
	static void ParseObjFile(const PString &, PMeshImportedData &);

	/**
	 * @return True upon successful import, false otherwise
	 */
	static bool ParseTexture(const PString &, PTextureImportedData &);
};

END_TRITRANIUM

#endif
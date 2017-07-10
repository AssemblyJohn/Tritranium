/** Copyright (c) Lazu Ioan-Bogdan */

#ifndef __TRITRANIUM_COLOR_H__
#define __TRITRANIUM_COLOR_H__

#include "Platform\Platform.h"

BEGIN_TRITRANIUM

// TODO: PColor4B and PColor4F for float color and byte color

class PColor
{
public:
	float R, G, B, A;

	PColor();
	PColor(uint32 color);
	PColor(float r, float g, float b, float a);
	PColor(float r, float g, float b);
	
	uint32 GetRed();
	uint32 GetGreen();
	uint32 GetBlue();
	uint32 GetAlpha();

	void Clamp();
	uint32 ToUint32() const;

	PColor operator+(const PColor &) const;
	PColor operator-(const PColor &) const;
	PColor operator*(float f) const;
};

END_TRITRANIUM

#endif
/** Copyright (c) Lazu Ioan-Bogdan */

#include "Color.h"

BEGIN_TRITRANIUM

PColor::PColor()
{
	R = G = B = A = 1.0f;
}

PColor::PColor(uint32 color)
{
	A = (float)(color >> 24 & 0xFF);
	R = (float)(color >> 16 & 0xFF);
	G = (float)(color >> 8 & 0xFF);
	B = (float)(color >> 0 & 0xFF);

	A /= 255.0f;
	R /= 255.0f;
	G /= 255.0f;
	B /= 255.0f;
}

PColor::PColor(float r, float g, float b, float a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}

PColor::PColor(float r, float g, float b)
{
	R = r;
	G = g;
	B = b;
	A = 1.0f;
}

uint32 PColor::GetRed()
{
	return (uint32)(R * 255);
}

uint32 PColor::GetGreen()
{
	return (uint32)(G * 255);
}

uint32 PColor::GetBlue()
{
	return (uint32)(B * 255);
}

uint32 PColor::GetAlpha()
{
	return (uint32)(A * 255);
}

void PColor::Clamp()
{
	R = (R < 1) ? R : 1;
	G = (G < 1) ? G : 1;
	B = (B < 1) ? B : 1;
}

uint32 PColor::ToUint32() const
{
	uint32 r = (uint32)(R * 255.0f);
	uint32 g = (uint32)(G * 255.0f);
	uint32 b = (uint32)(B * 255.0f);
	uint32 a = (uint32)(A * 255.0f);

	return (a << 24) | (r << 16) | (g << 8) | b;
}

PColor PColor::operator+(const PColor &c) const
{
	return PColor(
		R + c.R, 
		G + c.G, 
		B + c.B, 
		A + c.A
	);
}

PColor PColor::operator-(const PColor &c) const
{
	return PColor(
		R - c.R, 
		G - c.G, 
		B - c.B, 
		A - c.A
	);
}

PColor PColor::operator*(float f) const
{
	return PColor(
		R * f, 
		G * f, 
		B * f, 
		A * f
	);
}

END_TRITRANIUM
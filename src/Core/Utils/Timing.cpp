/** Copyright (c) Lazu Ioan-Bogdan */

#include "Timing.h"

BEGIN_TRITRANIUM

void PMarkTimer::Mark()
{
	mark = std::chrono::high_resolution_clock::now();
}

float PMarkTimer::Elapsed()
{	
	std::chrono::high_resolution_clock::duration elapsed = std::chrono::high_resolution_clock::now() - mark;
	// TODO: try seconds directly here
	float seconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();

	return (seconds / 1000000000.0f);
}

/*
PMarkTimer::PMarkTimer()
{
	LARGE_INTEGER temp;
	QueryPerformanceFrequency(&temp);

	frequency = (float) temp.QuadPart;

	
}

float PMarkTimer::TimeNow()
{
	return ToSeconds(Time());
}

void PMarkTimer::Mark()
{
	mark = TimeNow();
}

float PMarkTimer::Elapsed()
{
	return (TimeNow() - mark);
}

float PMarkTimer::Time()
{
	LARGE_INTEGER temp;
	QueryPerformanceCounter(&temp);
	
	return (float) temp.QuadPart;
}

float PMarkTimer::ToSeconds(float time)
{
	return (time / frequency);
}

uint64 PMarkTimer::Ticks()
{
	return GetTickCount64();
}
*/

END_TRITRANIUM
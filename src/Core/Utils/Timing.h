/** Copyright (c) Lazu Ioan-Bogdan */

#ifndef EN_TIMING_H
#define EN_TIMING_H

#include "Platform\Platform.h"

#include <chrono>

BEGIN_TRITRANIUM

class PTime
{
public:
	PTime()
	{ }

public:
	static uint64 Ticks()
	{		
		return ::std::chrono::system_clock::now().time_since_epoch().count();
	}
};

/**
 * A timer to which we mark a time and then we use 'Elapsed'
 * in order to see how much time has elapsed since that perion in which
 * we have marked.
 *
 * All the time used is returned in seconds.
 */
class PMarkTimer
{
public:
	PMarkTimer()
	{ }
	
public:
	/**
	 * Marks a point in time. Use Elapsed() after to see how much time passed.
	 */
	void Mark();

	/**
	 * @return How much time has elapsed since we called Mark(). Undefined result if we didn't called Mark(). Returned time is in seconds.
	 */
	float Elapsed();
private:	
	::std::chrono::high_resolution_clock::time_point mark;
};

END_TRITRANIUM

#endif
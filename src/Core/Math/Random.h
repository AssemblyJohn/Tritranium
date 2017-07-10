/** Copyright (c) Lazu Ioan-Bogdan */

#ifndef __TRITRANIUM_MT_RANDOM_H__
#define __TRITRANIUM_MT_RANDOM_H__

#include "Platform\Platform.h"
#include "Core\Utils\Timing.h"

BEGIN_TRITRANIUM

static const uint16 EN_MT_LENGTH = 624;

static const uint32 bitMask_32 = 0xffffffff;
static const uint32 bitPow_31 = 1 << 31;

/**
 * Mersene Twister implmentation
 */
class PRandom
{
public:
	/**
	 * Will seed the random generator so carefull when alocing these
	 */
	PRandom() 
	{
		idx = 0;
		Seed(PTime::Ticks());
	}

	/**
	 * Seeds the random generator with the provided seed.
	 */
	void Seed(uint32 seed)
	{
		mt[0] = seed;
		int i;

		for (i = 1; i < EN_MT_LENGTH; i++)
		{
			mt[i] = (1812433253 * (mt[i - 1] ^ (mt[i - 1] >> 30)) + i) & bitMask_32;
		}
	}

	/**
	 * Returns a 'random' unsigned integer number.
	 */
	uint32 Rand()
	{
		if (idx == 0)
		{
			InnerGeneration();
		}

		unsigned int y = mt[idx];

		y ^= y >> 11;
		y ^= (y << 7) & 2636928640;
		y ^= (y << 15) & 4022730752;
		y ^= y >> 18;
		idx = (idx + 1) % EN_MT_LENGTH;

		return y;
	}

	/**
	 * Same as 'Rand' but it returns the number within (0, range)
	 */
	uint32 Rand(uint32 range)
	{
		return (Rand() % range);
	}	

private:
	void InnerGeneration()
	{
		int i;
		unsigned int y;

		for (i = 0; i < EN_MT_LENGTH; i++)
		{
			y = (mt[i] & bitPow_31) + (mt[(i + 1) % EN_MT_LENGTH] & (bitPow_31 - 1));

			mt[i] = mt[(i + 397) % EN_MT_LENGTH] ^ (y >> 1);

			if (y % 2)
			{
				mt[i] ^= 2567483615;
			}
		}
	}

	uint32 mt[EN_MT_LENGTH];
	uint32 idx;
};

END_TRITRANIUM

#endif